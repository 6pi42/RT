/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:05:26 by amathias          #+#    #+#             */
/*   Updated: 2016/04/21 16:11:51 by amathias         ###   ########.fr       */
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
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8] = c.z;
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 1] = c.y;
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 2] = c.x;
}

cl_mem output;
cl_mem mem_camera;
cl_mem mem_shape;
cl_mem inter_output;
cl_mem inter_ray;
cl_mem inter_shape;
cl_mem shade_output;
cl_mem shade_inter;
cl_mem shade_ray;

void	ocl_init_shading(t_map *map)
{
	int		err;
	t_env	env;

	env = map->env;
	shade_inter = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			map->width * map->height * sizeof(cl_float3), NULL, &err);
	shade_ray = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			map->width * map->height * sizeof(cl_float4), NULL, &err);	
	shade_output = clCreateBuffer(env.context, CL_MEM_WRITE_ONLY,
			map->width * map->height * sizeof(cl_float4), NULL, &err);
	err = clSetKernelArg(env.get_shading, 0, sizeof(cl_mem), &shade_output);
	err |= clSetKernelArg(env.get_shading, 1, sizeof(cl_uint), &map->height);
	err |= clSetKernelArg(env.get_shading, 2, sizeof(cl_uint), &map->width);
	err |= clSetKernelArg(env.get_shading, 3, sizeof(cl_mem), &shade_inter);
	err |= clSetKernelArg(env.get_shading, 4, sizeof(cl_mem), &shade_ray);
	err |= clSetKernelArg(env.get_shading, 5, sizeof(cl_float4),
			&map->scene.cam->origin);
	err |= clSetKernelArg(env.get_shading, 6, sizeof(cl_mem), &inter_shape);
	err |= clSetKernelArg(env.get_shading, 7, sizeof(cl_int),
			&map->scene.nb_shape);
	if (err < 0)
		ft_putstr("Failed to create kernel argument");

}

void	ocl_init_inter(t_map *map)
{
	int		err;
	t_env	env;

	env = map->env;
	inter_ray = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			map->width * map->height * sizeof(cl_float4), NULL, &err);
	inter_output = clCreateBuffer(env.context, CL_MEM_WRITE_ONLY,
			map->width * map->height * sizeof(cl_float3), NULL, &err);
	inter_shape = clCreateBuffer(env.context, CL_MEM_READ_ONLY
				| CL_MEM_COPY_HOST_PTR, map->scene.nb_shape * sizeof(t_shape),
				map->scene.shape, &err);
	err = clSetKernelArg(env.get_inter, 0, sizeof(cl_mem), &inter_output);
	err |= clSetKernelArg(env.get_inter, 1, sizeof(cl_uint), &map->height);
	err |= clSetKernelArg(env.get_inter, 2, sizeof(cl_uint), &map->width);
	err |= clSetKernelArg(env.get_inter, 3, sizeof(cl_mem), &inter_ray);
	err |= clSetKernelArg(env.get_inter, 4, sizeof(cl_float4),
			&map->scene.cam->origin);
	err |= clSetKernelArg(env.get_inter, 5, sizeof(cl_mem), &inter_shape);
	err |= clSetKernelArg(env.get_inter, 6, sizeof(cl_int),
			&map->scene.nb_shape);
	if (err < 0)
		ft_putstr("Failed to create kernel argument");

}

void	ocl_init_ray(t_map *map)
{
	int		err;
	t_env	env;

	env = map->env;
	mem_camera = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
		sizeof(t_ray), NULL, &err);
	output = clCreateBuffer(env.context, CL_MEM_READ_WRITE,
			map->width * map->height * sizeof(cl_float4), NULL, &err);
	err = clSetKernelArg(env.get_ray, 0, sizeof(cl_mem), &output);
	err |= clSetKernelArg(env.get_ray, 1, sizeof(cl_uint), &map->height);
	err |= clSetKernelArg(env.get_ray, 2, sizeof(cl_uint), &map->width);
	err |= clSetKernelArg(env.get_ray, 3, sizeof(cl_mem), &mem_camera);
	if (err < 0)
		ft_putstr("Failed to create kernel argument");
}

size_t compact_inter(cl_float3 *inter, cl_float4 *ray, size_t work_size)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < work_size)
	{
		if (inter[i].y != -1.0f)
		{
			inter[(int)j] = inter[(int)i];
			ray[(int)j] = ray[(int)i];
			j++;
		}
		i++;
	}
	printf("j: %lu\n", j);
	return (j);
}

cl_float4 *ocl_get_shading(t_map *map, cl_float4 *ray,
					cl_float3 *inter, size_t work_size, size_t *shading_size)
{
	t_env env;
	int err;
	cl_float4 *ptr;
	cl_event event;
	cl_ulong time_start;
	cl_ulong time_end;
	size_t array_size;
	double total_time;

	env = map->env;
	err = clSetKernelArg(env.get_shading, 5, sizeof(cl_float4),
			&map->scene.cam->origin);
	if (err < 0)
		printf("Failed to create kernel argument");
	ptr = (cl_float4*)malloc(sizeof(cl_float4) * work_size);
	clFinish(env.cmds);
	array_size = compact_inter(inter, ray, work_size);
	*shading_size = array_size;
	if (array_size)
	{
		clEnqueueWriteBuffer(env.cmds, shade_ray, CL_TRUE, 0,
			array_size * sizeof(cl_float4), ray, 0, NULL, NULL);
		clEnqueueWriteBuffer(env.cmds, shade_inter, CL_TRUE, 0,
			array_size * sizeof(cl_float3), inter, 0, NULL, NULL);
		clEnqueueNDRangeKernel(env.cmds, env.get_shading, 1, NULL,
			&array_size, NULL, 0, NULL, &event);
		clEnqueueReadBuffer(env.cmds, shade_output,
			CL_TRUE, 0, work_size * sizeof(cl_float4),
			ptr, 0, NULL, NULL);
		clWaitForEvents(1 , &event);
		clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
			sizeof(time_start),	&time_start, NULL);
		clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
			sizeof(time_end),
		&time_end, NULL);
		total_time = time_end - time_start;
		printf("\nkernel shading: %0.3f ms\n", (total_time / 1000000.0) );
	}
	return (ptr);

}


cl_float3 *ocl_get_inter(t_map *map, cl_float4 *ray, size_t work_size)
{
	t_env env;
	int	err;
	cl_float3 *ptr;
	cl_event event;
	cl_ulong time_start;
	cl_ulong time_end;
	double total_time;

	env = map->env;
	err = clSetKernelArg(env.get_inter, 4, sizeof(cl_float4),
			&map->scene.cam->origin);
	if (err < 0)
		printf("Failed to create kernel argument");
	ptr = (cl_float3*)malloc(sizeof(cl_float3) * work_size);
	clFinish(env.cmds);
	clEnqueueWriteBuffer(env.cmds, inter_ray, CL_TRUE, 0,
			work_size * sizeof(cl_float4), ray, 0, NULL, NULL);
	clEnqueueNDRangeKernel(env.cmds, env.get_inter, 1, NULL,
			&work_size, NULL, 0, NULL, &event);
	clEnqueueReadBuffer(env.cmds, inter_output,
			CL_TRUE, 0, work_size * sizeof(cl_float3),
			ptr, 0, NULL, NULL);
	clWaitForEvents(1 , &event);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
			sizeof(time_start),	&time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end),
		&time_end, NULL);
	total_time = time_end - time_start;
	printf("\nkernel inter: %0.3f ms\n", (total_time / 1000000.0) );
	return (ptr);

}

cl_float4	*ocl_get_ray(t_map *map, size_t work_size)
{
	t_env env;
	cl_float4 *ptr;
	cl_event event;
	cl_ulong time_start;
	cl_ulong time_end;
	double total_time;

	env = map->env;
	ptr = (cl_float4*)malloc(sizeof(cl_float4) * work_size);
	clFinish(env.cmds);
	clEnqueueWriteBuffer(env.cmds, mem_camera, CL_TRUE, 0, sizeof(t_ray),
	 		map->scene.cam, 0, NULL, NULL);
	clEnqueueNDRangeKernel(env.cmds, env.get_ray, 1, NULL,
			&work_size, NULL, 0, NULL, &event);
	clEnqueueReadBuffer(env.cmds, output,
			CL_TRUE, 0, work_size * sizeof(cl_float4),
			ptr, 0, NULL, NULL);
	clWaitForEvents(1 , &event);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
			sizeof(time_start),	&time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end),
		&time_end, NULL);
	total_time = time_end - time_start;
	printf("\nkernel ray: %0.3f ms\n", (total_time / 1000000.0));
	return (ptr);
}

void	update(t_map *map)
{
	t_env env;
	size_t work_size;
	size_t shading_size;
	cl_float4 *ray;
	cl_float3 *inter;
	cl_float4 *shade;
	cl_float4 init;
	int i;

	i = 0;
	init.x = 0.0f;
	init.y = 0.0f;
	init.z = 0.0f;
	env = map->env;
	work_size = map->width * map->height;
	init_cam(map);
	map->scene.cam->ray = map->free_cam.dir;
	map->scene.cam->origin = map->free_cam.pos;
	map->scene.cam->down = map->free_cam.down;
	map->scene.cam->right = map->free_cam.left;
	map->scene.cam->ratio = map->free_cam.aspect_ratio;
	ray = ocl_get_ray(map, work_size);
	inter = ocl_get_inter(map, ray, work_size);
	shade = ocl_get_shading(map, ray, inter, work_size, &shading_size);
	while (i < (int)shading_size)
	{	
		draw_pixel_to_image(map, (int)shade[i].w % (int)map->width,
				(int)shade[i].w / (int)map->width, shade[i]);
		i++;
	}
	free(inter);
	free(ray);
	free(shade);
}

void	raytracer(t_map *map)
{
	size_t	work_size;
	int		i;
	t_env	env;

	i = 0;
	env = map->env;
	work_size = (map->width * map->height);
	ocl_init_ray(map);
	ocl_init_inter(map);
	ocl_init_shading(map);
}

void	draw(t_map *map)
{
	//struct timeval sub;
	size_t i;
	cl_float4 init;

	init.x = 0.0f;
	init.y = 0.0f;
	init.z = 0.0f;
	i = 0;
	map->fps.frames++;
	gettimeofday(&map->fps.end, NULL);
	map->img.img = mlx_new_image(map->mlx, map->width, map->height);
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
			&(map->img.size_line), &(map->img.endian));
	/*while (i < (size_t)(map->width * map->height))
	{
		draw_pixel_to_image(map, i % (int)map->width, i / map->width, init);
		i++;
	} */
	update(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	mlx_destroy_image(map->mlx, map->img.img);
	//timersub(&map->fps.end, &map->fps.start, &sub);
	/*if (sub.tv_sec == 1.0)
	{
		//printf("fps: %f\n", map->fps.frames);
		map->fps.frames = 0;
		gettimeofday(&map->fps.start, NULL);
	} */
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

	map.scene.nb_shape = 5;
	shape = (t_shape*)malloc(sizeof(t_shape) * map.scene.nb_shape);
	shape[0].pos.x = 0.0;
	shape[0].pos.y = 0.0;
	shape[0].pos.z = 0.0;
	shape[0].pos.w = 0.0;
	shape[0].color.x = 255;
	shape[0].color.y = 0;
	shape[0].color.z = 0;
	shape[0].color.w = 0;
	shape[0].radius.x = 25.0;
	shape[0].type.x = 1;

	shape[1].pos.x = 30.0;
	shape[1].pos.y = 0.0;
	shape[1].pos.z = 0.0;
	shape[1].pos.w = 0.0;
	shape[1].color.x = 255;
	shape[1].color.y = 255;
	shape[1].color.z = 0;
	shape[1].color.w = 0;
	shape[1].radius.x = 25.0;
	shape[1].type.x = 1;

	shape[2].pos.x = -10.0;
	shape[2].pos.y = 0.0;
	shape[2].pos.z = 10.0;
	shape[2].pos.w = 0.0;
	shape[2].color.x = 255;
	shape[2].color.y = 0;
	shape[2].color.z = 0;
	shape[2].color.w = 0;
	shape[2].radius.x = 25.0;
	shape[2].type.x = 1;

	shape[3].pos.x = 0.0;
	shape[3].pos.y = 30.0;
	shape[3].pos.z = 0.0;
	shape[3].pos.w = 0.0;
	shape[3].color.x = 255;
	shape[3].color.y = 0;
	shape[3].color.z = 255;
	shape[3].color.w = 0;
	shape[3].radius.x = 25.0;
	shape[3].type.x = 1;

	shape[4].pos.x = 50.0;
	shape[4].pos.y = -300.0;
	shape[4].pos.z = 40.0;
	shape[4].pos.w = 0.0;
	shape[4].color.x = 255;
	shape[4].color.y = 255;
	shape[4].color.z = 255;
	shape[4].color.w = 0;
	shape[4].radius.x = 25.0;
	shape[4].type.x = 1;

	map.width = 1080;
	map.height = 720;

	map.free_cam.dir.x = 0.0;
	map.free_cam.dir.y = 0.0;
	map.free_cam.dir.z = -1.0;
	map.free_cam.pos.x = 100;
	map.free_cam.pos.y = 100;
	map.free_cam.pos.z = 200;
	map.free_cam.old_mouse_pos.x = map.width / 2;
	map.free_cam.old_mouse_pos.y = map.height / 2;
	map.scene.shape = shape;
	map.scene.cam = &cam;
	map.mlx = mlx_init();
	init_key(&map);
	map.win = mlx_new_window(map.mlx, map.width, map.height, "RT");
	prog = get_prog("get_ray.cl");
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
