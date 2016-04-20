/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:22:57 by amathias          #+#    #+#             */
/*   Updated: 2016/04/19 16:20:07 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ocl_init(t_env *env, t_prog prog)
{
	int err;
	cl_platform_id platform;
	char *prog_log;
	size_t log_size;

	clGetPlatformIDs(1, &platform, NULL);
	if(clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &env->id, NULL) !=
			CL_SUCCESS)
		ft_putstr("Error: Failed to create a device group\n");	
	if (!(env->context = clCreateContext(NULL, 1, &env->id, NULL, NULL, &err)))
		ft_putstr("Error: Failed to create a compute context\n");
	if (!(env->cmds = clCreateCommandQueue(env->context, env->id,
					CL_QUEUE_PROFILING_ENABLE, &err)))
		ft_putstr("Error: Failed to create a command commands\n");
	if (!(env->program = clCreateProgramWithSource(env->context, 1,
					(const char**)&prog.buffer, NULL, &err)))
		ft_putstr("Error: Failed to create program\n");
	if ((err =
		clBuildProgram(env->program, 0, NULL, "-cl-fast-relaxed-math",
			NULL, NULL)) != CL_SUCCESS)
		ft_putstr("Error: Failed to build program executable\n");
	if (err < 0)
	{
		clGetProgramBuildInfo(env->program, env->id,
				CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		prog_log = (char*)malloc(sizeof(char) * log_size + 1);
		prog_log[log_size] = '\0';
		clGetProgramBuildInfo(env->program, env->id,
				CL_PROGRAM_BUILD_LOG, log_size + 1, prog_log, NULL);
		printf("%s\n",prog_log);
		free(prog_log);
		exit(0);
	}
	if (!(env->get_ray = clCreateKernel(env->program, "get_ray", &err)))
		ft_putstr("Error: Failed to create kernel\n");
	if (!(env->get_inter =
				clCreateKernel(env->program, "get_intersection", &err)))
		ft_putstr("Error: Failed to create kernel\n");
	if (!(env->get_shading =
				clCreateKernel(env->program, "get_shading", &err)))
		ft_putstr("Error: Failed to create kernel\n");
	free(prog.buffer);
}

t_prog	get_prog(char *file_name)
{
	t_prog	prog;
	char	*buffer;
	char	*line;
	char	*back;
	int		fd;	

	prog.file_name = file_name;
	prog.len = -1;
	buffer = (char*)malloc(sizeof(char) + 1);
	buffer[0] = '\0';
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (prog);
	while (get_next_line(fd, &line))
	{
		buffer = ft_strjoinfree(buffer, line);
		back = (char*)malloc(sizeof(char) + 1);
		back[0] = '\n';
		back[1] = '\0';
		buffer = ft_strjoinfree(buffer, back);
	}
	prog.len = ft_strlen(buffer);
	prog.buffer = buffer;
	if (close(fd) == -1)
		return (prog);
	return (prog);
}


