/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:05:26 by amathias          #+#    #+#             */
/*   Updated: 2016/04/07 13:54:27 by amathias         ###   ########.fr       */
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

void	draw_pixel_to_image(t_map *map, int x, int y, cl_float4 c)
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

void	update(t_map *map)
{
	t_env env;
	size_t work_size;
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
			&work_size, NULL, 0, NULL, NULL);
	cl_float4 *ptr = (cl_float4*)clEnqueueMapBuffer(env.cmds, output,
			CL_TRUE, CL_MAP_READ, 0,
			map->width * map->height * sizeof(cl_float4), 0, NULL, NULL, NULL);
	while (i < map->width * map->height)
	{
		draw_pixel_to_image(map, i % map->width, i / map->width, ptr[i]);
		i++;
	}
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
	mem_camera = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			sizeof(t_ray), NULL, &err);
	output = clCreateBuffer(env.context, CL_MEM_WRITE_ONLY,
			map->width * map->height * sizeof(cl_float4), NULL, &err);
	err = clSetKernelArg(env.kernel, 0, sizeof(cl_mem), &output);
	err |= clSetKernelArg(env.kernel, 1, sizeof(cl_uint), &map->height);
	err |= clSetKernelArg(env.kernel, 2, sizeof(cl_uint), &map->width);
	err |= clSetKernelArg(env.kernel, 3, sizeof(cl_mem), &mem_camera);
	err |= clSetKernelArg(env.kernel, 4, sizeof(cl_mem), &mem_shape);
	err |= clSetKernelArg(env.kernel, 5, sizeof(cl_uint),&map->scene.nb_shape);
	if (err < 0)
		ft_putstr("Failed to create kernel argument");
}

void	draw(t_map *map)
{
	map->fps.frames++;
	map->fps.end = clock();

	map->img.img = mlx_new_image(map->mlx, map->width, map->height);
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
			&(map->img.size_line), &(map->img.endian));
	update(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	mlx_destroy_image(map->mlx, map->img.img);
	if ((map->fps.end - map->fps.start) / CLOCKS_PER_SEC >= 1.0)
	{
		printf("fps: %f\n", map->fps.frames);
		map->fps.frames = 0;
		map->fps.start = clock();
	}

}

void	vec_normalize(cl_float4 *vec)
{
	double tmp;

	tmp = 1.0 / sqrt((vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
	vec->x *= tmp;
	vec->y *= tmp;
	vec->z *= tmp;

}
int		main(void)
{
	t_map		map;
	t_prog		prog;
	t_shape		*shape;
	t_ray		cam;

	map.scene.nb_shape = 6;
	shape = (t_shape*)malloc(sizeof(t_shape) * map.scene.nb_shape);
	shape[0].pos.x = 20.0;
	shape[0].pos.y = 20.0;
	shape[0].pos.z = 20.0;
	shape[0].pos.w = 0.0;
	shape[0].color.x = 255;
	shape[0].color.y = 255;
	shape[0].color.z = 0;
	shape[0].color.w = 0;
	shape[0].radius.x = 25.0;
	shape[0].type.x = 1;

	shape[1].pos.x = 60.0;
	shape[1].pos.y = 20.0;
	shape[1].pos.z = 60.0;
	shape[1].pos.w = 4.0;
	shape[1].color.x = 0;
	shape[1].color.y = 0;
	shape[1].color.z = 255;
	shape[1].color.w = 0;
	shape[1].radius.x = 35.0;
	shape[1].type.x = 1;


	shape[2].pos.x = 40.0;
	shape[2].pos.y = -50.0;
	shape[2].pos.z = 20.0;
	shape[2].pos.w = 0.0;
	shape[2].color.x = 255;
	shape[2].color.y = 255;
	shape[2].color.z = 0;
	shape[2].color.w = 0;
	shape[2].radius.x = 0.0;
	shape[2].radius.y = 1.0;
	shape[2].radius.z = 0.0;
	shape[2].radius.w = 0.0;
	shape[2].type.x = 2;

	shape[3].pos.x = 40.0;
	shape[3].pos.y = 0.0;
	shape[3].pos.z = -190;
	shape[3].pos.w = 0.0;
	shape[3].color.x = 0;
	shape[3].color.y = 255;
	shape[3].color.z = 0;
	shape[3].color.w = 0;
	shape[3].radius.x = 0.0;
	shape[3].radius.y = 0.0;
	shape[3].radius.z = 1.0;
	shape[3].radius.w = 0.0;
	shape[3].type.x = 2;

	shape[4].pos.x = 300.0;
	shape[4].pos.y = 40.0;
	shape[4].pos.z = 0.0;
	shape[4].pos.w = 0.0;
	shape[4].color.x = 0;
	shape[4].color.y = 255;
	shape[4].color.z = 255;
	shape[4].color.w = 0;
	shape[4].radius.x = 15.0;
	shape[4].type.x = 3;
	shape[4].axis.x = -0.5;
	shape[4].axis.y = 1.0;
	shape[4].axis.z = 0.0;
	shape[4].axis.w = 0.0;
	vec_normalize(&(shape[4].axis));

	shape[5].pos.x = -50.0;
	shape[5].pos.y = 20.0;
	shape[5].pos.z = 0.0;
	shape[5].pos.w = 0.0;
	shape[5].color.x = 255;
	shape[5].color.y = 0;
	shape[5].color.z = 255;
	shape[5].color.w = 0;
	shape[5].radius.x = 0.5;
	shape[5].type.x = 4;
	shape[5].axis.x = 1.0;
	shape[5].axis.y = 1.0;
	shape[5].axis.z = 0.0;
	shape[5].axis.w = 0.0;
	vec_normalize(&(shape[5].axis));

	map.width = 900;
	map.height = 720;

	map.free_cam.dir.x = -1;
	map.free_cam.dir.y = -1;
	map.free_cam.dir.z = -1;
	map.free_cam.pos.x = 100;
	map.free_cam.pos.y = 100;
	map.free_cam.pos.z = 200;
	map.free_cam.old_mouse_pos.x = map.width / 2;
	map.free_cam.old_mouse_pos.y = map.height / 2;
	map.scene.shape = shape;
	map.scene.cam = &cam;
	map.mlx = mlx_init();
	init_key(&map);
	map.win = mlx_new_window(map.mlx, map.width, map.height, "RT IN RT");
	prog = get_prog("generate_ray.cl");
	ocl_init(&map.env, prog);
	raytracer(&map);
	map.fps.start = clock();
	draw(&map);
	update(&map);
	mlx_key_hook(map.win, key_hook, &map);
	mlx_hook(map.win, 2, (1L << 0), key_press, &map);
	mlx_hook(map.win, 6, (1L << 6), motion_notify, &map);
	mlx_loop_hook(map.mlx, loop_hook, &map);
	mlx_loop(map.mlx);
}
