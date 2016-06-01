/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:05:26 by amathias          #+#    #+#             */
/*   Updated: 2016/05/27 12:22:01 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_mem output;
cl_mem mem_camera;
cl_mem mem_shape;
cl_mem mem_img;
cl_mem mem_spot;

void	update(t_map *map)
{
	t_env env;
	size_t work_size;
	cl_event event;
	cl_ulong time_start;
	cl_ulong time_end;
	double total_time;
	GdkPixbuf	*pixel_buf;

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
	clEnqueueWriteBuffer(env.cmds, mem_shape, CL_TRUE, 0, sizeof(t_shape) * map->scene.nb_shape,
			map->scene.shape, 0, NULL, NULL);
	clEnqueueWriteBuffer(env.cmds, mem_spot, CL_TRUE, 0, sizeof(cl_float4) * map->scene.nb_spot,
			map->scene.spot, 0, NULL, NULL);
	clEnqueueNDRangeKernel(env.cmds, env.kernel, 1, NULL,
			&work_size, NULL, 0, NULL, &event);
	unsigned char *ptr = (unsigned char*)clEnqueueMapBuffer(env.cmds, output,
			CL_TRUE, CL_MAP_READ, 0,
			map->width * map->height * (sizeof(char) * 3), 0, NULL, NULL, NULL);
	clWaitForEvents(1, &event);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
			sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
			sizeof(time_end), &time_end, NULL);
	total_time = time_end - time_start;
	printf("\nExecution time = %0.3f ms\n", (total_time / 1000000.0));
	pixel_buf = gdk_pixbuf_new_from_data((guchar*)ptr, GDK_COLORSPACE_RGB, FALSE, 8, map->width, map->height, map->width * 3, NULL, NULL);
	gtk_image_set_from_pixbuf(GTK_IMAGE(map->render), pixel_buf);
	g_object_unref(G_OBJECT(pixel_buf));
}

void	scene_update(t_map *map)
{
	size_t	work_size;

	work_size = map->width * map->height;
	clReleaseMemObject(mem_shape);
	clReleaseMemObject(mem_spot);
	mem_shape = clCreateBuffer(map->env.context, CL_MEM_READ_ONLY
		| CL_MEM_COPY_HOST_PTR, map->scene.nb_shape * sizeof(t_shape),
		map->scene.shape, NULL);
	mem_spot = clCreateBuffer(map->env.context, CL_MEM_READ_ONLY
		| CL_MEM_COPY_HOST_PTR, map->scene.nb_spot * sizeof(cl_float4),
		map->scene.spot, NULL);
	clSetKernelArg(map->env.kernel, 4, sizeof(cl_mem), &mem_shape);
	clSetKernelArg(map->env.kernel, 1, sizeof(cl_float), &map->height);
	clSetKernelArg(map->env.kernel, 2, sizeof(cl_float), &map->width);
	clSetKernelArg(map->env.kernel, 4, sizeof(cl_mem), &mem_shape);
	clSetKernelArg(map->env.kernel, 5, sizeof(cl_uint),&map->scene.nb_shape);
	clSetKernelArg(map->env.kernel, 7, sizeof(cl_short), &map->multi_sampling);
	clSetKernelArg(map->env.kernel, 9, sizeof(cl_uint), &map->scene.nb_spot);
	clSetKernelArg(map->env.kernel, 8, sizeof(cl_mem), &mem_spot);
	printf("coucou\n");
}


void	raytracer(t_map *map)
{
	printf("raytracer start\n");
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
	mem_spot = clCreateBuffer(env.context, CL_MEM_READ_ONLY
		| CL_MEM_COPY_HOST_PTR, map->scene.nb_spot * sizeof(cl_float4),
		map->scene.spot, &err);
	mem_camera = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			sizeof(t_ray), NULL, &err);
	mem_img = clCreateBuffer(env.context, CL_MEM_READ_ONLY
		| CL_MEM_COPY_HOST_PTR, sizeof(t_img),
		&map->img, &err);
	output = clCreateBuffer(env.context, CL_MEM_WRITE_ONLY,
			map->width * map->height * (sizeof(char) * 3) , NULL, &err);
	err = clSetKernelArg(env.kernel, 0, sizeof(cl_mem), &output);
	err |= clSetKernelArg(env.kernel, 1, sizeof(cl_float), &map->height);
	err |= clSetKernelArg(env.kernel, 2, sizeof(cl_float), &map->width);
	err |= clSetKernelArg(env.kernel, 3, sizeof(cl_mem), &mem_camera);
	err |= clSetKernelArg(env.kernel, 4, sizeof(cl_mem), &mem_shape);
	err |= clSetKernelArg(env.kernel, 5, sizeof(cl_uint),&map->scene.nb_shape);
	err |= clSetKernelArg(env.kernel, 6, sizeof(cl_mem),&mem_img);
	err |= clSetKernelArg(env.kernel, 7, sizeof(cl_short), &map->multi_sampling);
	err |= clSetKernelArg(env.kernel, 8, sizeof(cl_mem), &mem_spot);
	err |= clSetKernelArg(env.kernel, 9, sizeof(cl_uint), &map->scene.nb_spot);
	if (err < 0)
		ft_putstr("Failed to create kernel argument");
	printf("fin raytracer\n");
}

void	draw(t_map *map)
{
	struct timeval sub;
	map->fps.frames++;
	gettimeofday(&map->fps.end, NULL);
	update(map);

	timersub(&map->fps.end, &map->fps.start, &sub);
	if (sub.tv_sec >= 1.0f)
	{
		printf ("\033[32;1m\nfps: %.3f\n\033[0m", map->fps.frames);
		map->fps.frames = 0;
		gettimeofday(&map->fps.start, NULL);
	}
}

int main (int argc, char **argv)
{
	t_map		map;
	t_prog		prog;
	t_ray		cam;

	if (argc == 2)
		parse(&map, argv[1]);
	map.obj_selected = NULL;//&map.scene.shape[1];

	init_cam2(&map);
	map.scene.cam = &cam;
	map.fix = 0;

	gtk_init(&argc, &argv);
	create_interface(&map);
	connect_signal_gtk(&map);
	set_css_style(&map, "style.css");
	prog = get_prog("generate_ray.cl");
	ocl_init(&map.env, prog);
	raytracer(&map);

	gettimeofday(&map.fps.start, NULL);
	draw(&map);
	gtk_main();

	return 1;
}
