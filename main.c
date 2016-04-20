/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:05:26 by amathias          #+#    #+#             */
/*   Updated: 2016/04/18 17:21:24 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cam(t_map *map)
{
	cl_float4 tmp;

	tmp.x = 0;
	tmp.y = 1;
	tmp.z = 0;
	map->free_cam.aspect_ratio = map->width / map->height;
	normalize_vec(&map->free_cam.dir);
	map->free_cam.left = cross_vec(tmp, map->free_cam.dir);
	normalize_vec(&map->free_cam.left);
	map->free_cam.down = cross_vec(map->free_cam.dir, map->free_cam.left);
}

void	draw_pixel_to_image(t_map *map, int x, int y, cl_uchar4 c)
{
	if (x < 0 || x > map->width - 1 || y < 0 || y > map->height - 1)
		return ;
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8] = c.s[2];
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 1] = c.s[1];
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 2] = c.s[0];
}

cl_mem output;
cl_mem mem_camera;
cl_mem mem_shape;
cl_mem mem_img;
cl_mem mem_tex;

void	update(t_map *map)
{
	t_env env;
	size_t work_size;
	cl_event event;
	cl_ulong time_start;
	cl_ulong time_end;
	double total_time;
	int i;

	i = 0;
	env = map->env;
	work_size = map->width * map->height;
	init_cam(map);
	map->scene.cam->ray = map->free_cam.dir;
	map->scene.cam->origin = map->free_cam.pos;
	map->scene.cam->down = map->free_cam.down;
	map->scene.cam->right = map->free_cam.left;
	map->scene.cam->ratio = map->free_cam.aspect_ratio;
	clEnqueueWriteBuffer(env.cmds, mem_camera, CL_TRUE, 0, sizeof(t_ray),
			map->scene.cam, 0, NULL, NULL);
	clEnqueueNDRangeKernel(env.cmds, env.kernel, 1, NULL,
			&work_size, NULL, 0, NULL, &event);
	char *ptr = (char*)clEnqueueMapBuffer(env.cmds, output,
			CL_TRUE, CL_MAP_READ, 0,
			map->width * map->height * (sizeof(char) * 4), 0, NULL, NULL, NULL);
	clWaitForEvents(1, &event);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
			sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
			sizeof(time_end), &time_end, NULL);
	total_time = time_end - time_start;
	printf("\nExecution time = %0.3f ms\n",
			(total_time / 1000000.0));
	ft_memcpy(map->img.data, ptr,
			map->width * map->height * (sizeof(char) * 4));
}

void	raytracer(t_map *map)
{
	size_t	work_size;
	int		i;
	int		err;
	t_env	env;

	i = 0;
	env = map->env;
	work_size = map->width * map->height;
	mem_shape = clCreateBuffer(env.context, CL_MEM_READ_ONLY
		| CL_MEM_COPY_HOST_PTR, map->scene.nb_shape * sizeof(t_shape),
		map->scene.shape, &err);
	mem_tex = clCreateBuffer(env.context, CL_MEM_READ_ONLY
		| CL_MEM_COPY_HOST_PTR, sizeof(int) * map->tex[0] * map->tex[1],
		map->tex, &err);
	mem_camera = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			sizeof(t_ray), NULL, &err);
	mem_img = clCreateBuffer(env.context, CL_MEM_READ_ONLY
		| CL_MEM_COPY_HOST_PTR, sizeof(t_img),
		&map->img, &err);
	output = clCreateBuffer(env.context, CL_MEM_WRITE_ONLY,
			map->width * map->height * (sizeof(char) * 4) , NULL, &err);
	err = clSetKernelArg(env.kernel, 0, sizeof(cl_mem), &output);
	err |= clSetKernelArg(env.kernel, 1, sizeof(cl_uint), &map->height);
	err |= clSetKernelArg(env.kernel, 2, sizeof(cl_uint), &map->width);
	err |= clSetKernelArg(env.kernel, 3, sizeof(cl_mem), &mem_camera);
	err |= clSetKernelArg(env.kernel, 4, sizeof(cl_mem), &mem_shape);
	err |= clSetKernelArg(env.kernel, 5, sizeof(cl_uint),&map->scene.nb_shape);
	err |= clSetKernelArg(env.kernel, 6, sizeof(cl_mem),&mem_img);
	err |= clSetKernelArg(env.kernel, 7, sizeof(cl_mem), &mem_tex);
	if (err < 0)
		ft_putstr("Failed to create kernel argument");
}

void	draw(t_map *map)
{
	struct timeval sub;
	map->fps.frames++;
	gettimeofday(&map->fps.end, NULL);
	update(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	timersub(&map->fps.end, &map->fps.start, &sub);
	if (sub.tv_sec >= 1.0)
	{
		printf ("\033[32;1m\nfps: %.3f\n\033[0m", map->fps.frames);
		map->fps.frames = 0;
		gettimeofday(&map->fps.start, NULL);
	}
}

void	vec_normalize(cl_float4 *vec)
{
	float tmp;

	tmp = 1.0f / sqrt((vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
	vec->x *= tmp;
	vec->y *= tmp;
	vec->z *= tmp;
}

int		main(int argc, char **argv)
{
	t_map		map;
	t_prog		prog;
	t_shape		*shape;
	t_ray		cam;

	if (argc != 2)
		return (1);
	map.scene.nb_shape = get_nb_shape(argv[1]);
	shape = parse(argv[1]);

	map.width = 1080.0f;
	map.height = 720.0f;

	map.free_cam.pos.x = 0;
	map.free_cam.pos.y = 50;
	map.free_cam.pos.z = 500;
	map.scene.shape = shape;
	map.scene.cam = &cam;
	map.tex = get_texture("greystone.cboyer", 64, 64);
	map.mlx = mlx_init();
	init_key(&map);
	map.win = mlx_new_window(map.mlx, map.width, map.height, "RT IN RT");
	map.img.img = mlx_new_image(map.mlx, map.width, map.height);
	map.img.data = mlx_get_data_addr(map.img.img, &(map.img.bpp),
			&(map.img.size_line), &(map.img.endian));
	prog = get_prog("generate_ray.cl");
	ocl_init(&map.env, prog);
	raytracer(&map);
	gettimeofday(&map.fps.start, NULL);
	draw(&map);
	update(&map);
	mlx_key_hook(map.win, key_hook, &map);
	mlx_hook(map.win, 2, (1L << 0), key_press, &map);
	mlx_hook(map.win, 6, (1L << 6), motion_notify, &map);
	mlx_loop_hook(map.mlx, loop_hook, &map);
	mlx_loop(map.mlx);
}
