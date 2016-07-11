/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 17:14:53 by amathias          #+#    #+#             */
/*   Updated: 2016/07/11 13:22:00 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void	update_inter(t_map *map, size_t work_size)
{
	int err;

	if (map->env.clbuf.ray)
		clReleaseMemObject(map->env.clbuf.ray);
	if (map->env.clbuf.output)
		clReleaseMemObject(map->env.clbuf.output);
	map->env.clbuf.ray = clCreateBuffer(map->env.context, CL_MEM_READ_ONLY,
	work_size * sizeof(t_ray), NULL, &err);
	map->env.clbuf.output = clCreateBuffer(map->env.context, CL_MEM_WRITE_ONLY,
	work_size * sizeof(t_inter), NULL, &err);
	if (err < 0)
		ft_putstr("Failed to update kernel with new work_size");
}

void	init_inter(t_map *map, size_t work_size)
{
	int		i;
	int		err;
	t_env	env;

	i = 0;
	env = map->env;
	update_inter(map, work_size);
	map->env.clbuf.shape = clCreateBuffer(env.context, CL_MEM_READ_ONLY
			| CL_MEM_COPY_HOST_PTR, map->scene.nb_shape * sizeof(t_shape),
			map->scene.shape, &err);
	map->env.clbuf.ray = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			work_size * sizeof(t_ray), NULL, &err);
	map->env.clbuf.output = clCreateBuffer(env.context, CL_MEM_WRITE_ONLY,
			work_size * sizeof(t_inter) , NULL, &err);
	err = clSetKernelArg(env.kernel, 0, sizeof(cl_mem), &map->env.clbuf.output);
	err |= clSetKernelArg(env.kernel, 1, sizeof(cl_mem), &map->env.clbuf.ray);
	err |= clSetKernelArg(env.kernel, 2, sizeof(cl_mem), &map->env.clbuf.shape);
	err |= clSetKernelArg(env.kernel, 3, sizeof(cl_int), &map->scene.nb_shape);
	if (err < 0)
		ft_putstr("Failed to create kernel argument");
}

t_inter	*get_inter(t_map *map, size_t work_size, t_ray *ray)
{
	t_inter		*ptr;
	cl_event	event;
	cl_ulong	time_start;
	cl_ulong	time_end;
	double		total_time;

	ptr = (t_inter*)malloc(sizeof(t_inter) * work_size);
	init_cam(map);
	map->scene.cam->ray = map->free_cam.dir;
	map->scene.cam->origin = map->free_cam.pos;
	map->scene.cam->down = map->free_cam.down;
	map->scene.cam->right = map->free_cam.left;
	map->scene.cam->ratio = map->free_cam.aspect_ratio;
	clFinish(map->env.cmds);
	clEnqueueWriteBuffer(map->env.cmds, map->env.clbuf.ray, CL_FALSE, 0,
			work_size * sizeof(t_ray), ray, 0, NULL, NULL);
	clEnqueueNDRangeKernel(map->env.cmds, map->env.kernel, 1, NULL,
			&work_size, NULL, 0, NULL, &event);
	clEnqueueReadBuffer(map->env.cmds, map->env.clbuf.output,
			CL_TRUE, 0, work_size * sizeof(t_inter), ptr, 0, NULL, NULL);
	//ptr = (t_inter*)clEnqueueMapBuffer(env.cmds,
	//		map->env.clbuf.output, CL_TRUE, CL_MAP_READ, 0,
	//		work_size * sizeof(t_inter), 0, NULL, NULL, NULL);
	//PROFILING
	//clWaitForEvents(1, &event);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
			sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
			sizeof(time_end), &time_end, NULL);
	total_time = time_end - time_start;
	printf("\nExecution time = %0.3f ms\n", (total_time / 1000000.0));
	//END PROFILING
	return (ptr);
}
