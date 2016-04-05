/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:05:26 by amathias          #+#    #+#             */
/*   Updated: 2016/04/05 14:35:17 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
cl_mem mem_sphere;
cl_mem mem_plane;
cl_mem mem_cyl;
cl_mem mem_cone;
cl_mem mem_ellips;

void	update(t_map *map)
{
	t_env env;
	size_t work_size;
	int i;

	i = 0;
	env = map->env;
	work_size = map->width * map->height;
	clEnqueueWriteBuffer(env.cmds, mem_sphere, CL_TRUE, 0,
			map->scene.nb_sphere *sizeof(t_shape),
			map->scene.sphere, 0, NULL, NULL);
	clEnqueueWriteBuffer(env.cmds, mem_plane, CL_TRUE, 0,
			map->scene.nb_plan * sizeof(t_shape),
			map->scene.plan, 0, NULL, NULL);	
	clEnqueueWriteBuffer(env.cmds, mem_cyl, CL_TRUE, 0,
			map->scene.nb_cyl * sizeof(t_shape),
			map->scene.cyl, 0, NULL, NULL);	
	clEnqueueWriteBuffer(env.cmds, mem_cone, CL_TRUE, 0,
			map->scene.nb_cone * sizeof(t_shape),
			map->scene.cone, 0, NULL, NULL);
	clEnqueueWriteBuffer(env.cmds, mem_ellips, CL_TRUE, 0,
			map->scene.nb_ellips * sizeof(t_shape),
			map->scene.ellips, 0, NULL, NULL);	
	clEnqueueWriteBuffer(env.cmds, mem_camera, CL_TRUE, 0, sizeof(t_ray),
			map->scene.cam, 0, NULL, NULL);		
	clEnqueueNDRangeKernel(env.cmds, env.kernel, 1, NULL, &work_size, NULL,
			0, NULL, NULL);
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
	mem_sphere = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			map->scene.nb_sphere * sizeof(t_shape), NULL, &err);
	mem_plane = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			map->scene.nb_plan * sizeof(t_shape), NULL, &err);
	mem_cyl = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			map->scene.nb_cyl * sizeof(t_shape), NULL, &err);
	mem_cone = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			map->scene.nb_cone * sizeof(t_shape), NULL, &err);
	mem_ellips = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			map->scene.nb_ellips * sizeof(t_shape), NULL, &err);
	mem_camera = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			sizeof(t_ray), NULL, &err);
	output = clCreateBuffer(env.context, CL_MEM_WRITE_ONLY,
			map->width * map->height * sizeof(cl_float4), NULL, &err);
	err = clSetKernelArg(env.kernel, 0, sizeof(cl_mem), &output);
	err |= clSetKernelArg(env.kernel, 1, sizeof(cl_uint), &map->height);
	err |= clSetKernelArg(env.kernel, 2, sizeof(cl_uint), &map->width);
	err |= clSetKernelArg(env.kernel, 3, sizeof(cl_mem), &mem_camera);
	err |= clSetKernelArg(env.kernel, 4, sizeof(cl_mem), &mem_sphere);
	err |= clSetKernelArg(env.kernel, 5, sizeof(cl_uint),&map->scene.nb_sphere);
	err |= clSetKernelArg(env.kernel, 6, sizeof(cl_mem),&mem_plane);
	err |= clSetKernelArg(env.kernel, 7, sizeof(cl_uint),&map->scene.nb_plan);
	err |= clSetKernelArg(env.kernel, 8, sizeof(cl_mem),&mem_cyl);
	err |= clSetKernelArg(env.kernel, 9, sizeof(cl_uint),&map->scene.nb_cyl);
	err |= clSetKernelArg(env.kernel, 10, sizeof(cl_mem),&mem_cone);
	err |= clSetKernelArg(env.kernel, 11, sizeof(cl_uint),&map->scene.nb_cone);
	err |= clSetKernelArg(env.kernel, 12, sizeof(cl_mem),&mem_ellips);
	err |= clSetKernelArg(env.kernel, 13, sizeof(cl_uint),&map->scene.nb_ellips);
	if (err < 0)
		ft_putstr("Failed to create kernel argument");
}

void	draw(t_map *map)
{
	map->fps.frames++;
	time(&map->fps.end);

	map->img.img = mlx_new_image(map->mlx, map->width, map->height);
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
			&(map->img.size_line), &(map->img.endian));
	update(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	mlx_destroy_image(map->mlx, map->img.img);
	if (difftime(map->fps.end, map->fps.start) >= 1.0)
	{
		printf("fps: %f\n", map->fps.frames);
		map->fps.frames = 0;
		time(&map->fps.start);
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
	t_shape		*sphere;
	t_shape		*plan;
	t_shape		*cyl;
	t_shape		*cone;
	t_shape		*ellips;
	t_ray		cam;

	map.scene.nb_sphere = 2;
	sphere = (t_shape*)malloc(sizeof(t_shape) * map.scene.nb_sphere);
	sphere[0].pos.x = 0.0;
	sphere[0].pos.y = 0.0;
	sphere[0].pos.z = 0.0;
	sphere[0].pos.w = 4.0;
	sphere[0].color.x = 255;
	sphere[0].color.y = 0;
	sphere[0].color.z = 0;
	sphere[0].color.w = 0;
	sphere[0].radius.x = 25.0;
	sphere[0].type.x = 1;

	sphere[1].pos.x = 40.0;
	sphere[1].pos.y = 0.0;
	sphere[1].pos.z = 0.0;
	sphere[1].pos.w = 4.0;
	sphere[1].color.x = 0;
	sphere[1].color.y = 0;
	sphere[1].color.z = 255;
	sphere[1].color.w = 0;
	sphere[1].radius.x = 35.0;
	sphere[1].type.x = 1;


	map.scene.nb_plan = 2;
	plan = (t_shape*)malloc(sizeof(t_shape) * map.scene.nb_plan);
	plan[0].pos.x = 0.0;
	plan[0].pos.y = 0.0;
	plan[0].pos.z = 0.0;
	plan[0].pos.w = 0.0;
	plan[0].color.x = 255;	
	plan[0].color.y = 255;	
	plan[0].color.z = 0;	
	plan[0].color.w = 0;	
	plan[0].radius.x = 0.0;
	plan[0].radius.y = 1.0;
	plan[0].radius.z = 0.0;
	plan[0].radius.w = 0.0;
	plan[0].type.x = 2;

	plan[1].pos.x = 0.0;
	plan[1].pos.y = 0.0;
	plan[1].pos.z = -190;
	plan[1].pos.w = 0.0;
	plan[1].color.x = 0;	
	plan[1].color.y = 255;	
	plan[1].color.z = 0;	
	plan[1].color.w = 0;	
	plan[1].radius.x = 0.0;
	plan[1].radius.y = 0.0;
	plan[1].radius.z = 1.0;
	plan[1].radius.w = 0.0;
	plan[1].type.x = 2;

	map.scene.nb_cyl = 1;
	cyl = (t_shape*)malloc(sizeof(t_shape) * map.scene.nb_cyl);
	cyl[0].pos.x = 0.0;
	cyl[0].pos.y = 0.0;
	cyl[0].pos.z = 0.0;
	cyl[0].pos.w = 0.0;
	cyl[0].color.x = 0;
	cyl[0].color.y = 255;
	cyl[0].color.z = 255;
	cyl[0].color.w = 0;
	cyl[0].radius.x = 15.0;
	cyl[0].type.x = 3;
	cyl[0].axis.x = -0.5;
	cyl[0].axis.y = 1.0;
	cyl[0].axis.z = 0.0;
	cyl[0].axis.w = 0.0;
	vec_normalize(&(cyl[0].axis));

	map.scene.nb_cone = 1;
	cone = (t_shape*)malloc(sizeof(t_shape) * map.scene.nb_cone);
	cone[0].pos.x = -50.0;
	cone[0].pos.y = 20.0;
	cone[0].pos.z = 0.0;
	cone[0].pos.w = 0.0;
	cone[0].color.x = 255;
	cone[0].color.y = 0;
	cone[0].color.z = 255;
	cone[0].color.w = 0;
	cone[0].radius.x = 0.5;
	cone[0].type.x = 4;
	cone[0].axis.x = 1.0;
	cone[0].axis.y = 1.0;
	cone[0].axis.z = 0.0;
	cone[0].axis.w = 0.0;
	vec_normalize(&(cone[0].axis));
	ellips = (t_shape*)malloc(sizeof(t_shape) * 1);
/*
	map.scene.nb_ellips = 1;

	ellips = (t_shape*)malloc(sizeof(t_shape) * map.scene.nb_ellips);
	ellips[0].pos.x = -50.0;
	ellips[0].pos.y = 20.0;
	ellips[0].pos.z = 0.0;
	ellips[0].pos.w = 0.0;
	ellips[0].color.x = 255;
	ellips[0].color.y = 0;
	ellips[0].color.z = 255;
	ellips[0].color.w = 0;
	ellips[0].radius.x = 10.0;
	ellips[0].radius.y = 30.0;
	ellips[0].radius.z = 15.0;
	ellips[0].type.x = 5;
	ellips[0].axis.x = 1.0;
	ellips[0].axis.y = 1.0;
	ellips[0].axis.z = 0.0;
	ellips[0].axis.w = 0.0;
	vec_normalize(&(ellips[0].axis));
*/

	cam.origin.x = 0.0;
	cam.origin.y = 30.0;
	cam.origin.z = 200.0;
	cam.ray.x = 0.0;
	cam.ray.y = 0.0;
	cam.ray.z = 0.0;

	map.scene.sphere = sphere;
	map.scene.plan = plan;
	map.scene.cyl = cyl;
	map.scene.cone = cone;
	map.scene.ellips = ellips;
	map.scene.cam = &cam;
	map.mlx = mlx_init();
	init_key(&map);
	map.height = 720;
	map.width = 900;
	map.win = mlx_new_window(map.mlx, map.width, map.height, "RT IN RT");
	prog = get_prog("generate_ray.cl");
	ocl_init(&map.env, prog);
	raytracer(&map);
	time(&map.fps.start);
	draw(&map);
	mlx_key_hook(map.win, key_hook, &map);
	mlx_hook(map.win, 2, (1L << 0), key_press, &map);
	mlx_hook(map.win, 6, (1L << 6), motion_notify, &map);
	mlx_loop_hook(map.mlx, loop_hook, &map);
	mlx_loop(map.mlx);
}
