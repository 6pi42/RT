/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:05:26 by amathias          #+#    #+#             */
/*   Updated: 2016/04/03 15:50:40 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_pixel_to_image(t_map *map, int x, int y, cl_float4 color)
{
	if (x < 0 || x > map->width - 1 || y < 0 || y > map->height - 1)
		return ;
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8] = color.s[2];
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 1] = color.s[1];
	map->img.data[y * map->img.size_line + (x * map->img.bpp) / 8 + 2] = color.s[0];
}

cl_mem output;
cl_mem input;

void	update(t_map *map)
{
	t_env env;
	size_t work_size;
	int i;

	i = 0;
	env = map->env;
	work_size = map->width * map->height;
	clEnqueueWriteBuffer(env.cmds, input, CL_TRUE, 0,
			map->scene.nb_sphere *sizeof(t_sphere),
			map->scene.sphere, 0, NULL, NULL);
	clEnqueueNDRangeKernel(env.cmds, env.kernel, 1, NULL, &work_size, NULL,
			0, NULL, NULL);
	//clEnqueueWriteBuffer(env.cmds, input, CL_TRUE, 0,
//			map->scene.nb_sphere * sizeof(t_sphere),
//			map->scene.sphere, 0, NULL, NULL);
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
	//t_env	env;
	//t_prog	prog;
	//cl_mem	output;
	//cl_mem	input;
	size_t	work_size;
	int		i;
	int		err;
	t_env	env;

	i = 0;
	env = map->env;
	work_size = map->width * map->height;
	//prog = get_prog("generate_ray.cl");
	//ocl_init(&env, prog);
	input = clCreateBuffer(env.context, CL_MEM_READ_ONLY,
			map->scene.nb_sphere * sizeof(t_sphere), NULL, &err);
	output = clCreateBuffer(env.context, CL_MEM_WRITE_ONLY,
			map->width * map->height * sizeof(cl_float4), NULL, &err);
	//clEnqueueWriteBuffer(env.cmds, input, CL_TRUE, 0,
	//		map->scene.nb_sphere *sizeof(t_sphere),
	//		map->scene.sphere, 0, NULL, NULL);
	err = clSetKernelArg(env.kernel, 0, sizeof(cl_mem), &output);
	err |= clSetKernelArg(env.kernel, 1, sizeof(cl_uint), &map->height);
	err |= clSetKernelArg(env.kernel, 2, sizeof(cl_uint), &map->width);
	err |= clSetKernelArg(env.kernel, 3, sizeof(cl_mem), &input);
	err |= clSetKernelArg(env.kernel, 4, sizeof(cl_uint),
			&map->scene.nb_sphere);
	if (err < 0)
		ft_putstr("Failed to create kernel argument");
	/*clEnqueueNDRangeKernel(env.cmds, env.kernel, 1, NULL, &work_size, NULL,
			0, NULL, NULL);
	cl_float4 *ptr = (cl_float4*)clEnqueueMapBuffer(env.cmds, output,
			CL_TRUE, CL_MAP_READ, 0, map->width * map->height * sizeof(cl_float4), 0, NULL, NULL, NULL);

*/
/*	while (i < map->width * map->height)
	{
		draw_pixel_to_image(map, i % map->width, i / map->width, ptr[i]);
		i++;
	} */
	//i = 0;
	/*	while (i < width * height)
		{
		printf("%#08x\n", pixel[i * 3]);
		printf("%#08x\n", pixel[i * 3 + 1]);
		printf("%#08x\n", pixel[i * 3 + 2]);
		i++;
		} */
	//update(map);
}

void	draw(t_map *map)
{
	map->img.img = mlx_new_image(map->mlx, map->width, map->height);
	map->img.data = mlx_get_data_addr(map->img.img, &(map->img.bpp),
			&(map->img.size_line), &(map->img.endian));
	update(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	mlx_destroy_image(map->mlx, map->img.img);
}

int		main(void)
{
	t_map map;
	t_prog prog;
	t_sphere *sphere;

	sphere = (t_sphere*)malloc(sizeof(t_sphere) * 2);
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


	map.scene.nb_sphere = 2;
	map.scene.sphere = sphere;
	map.mlx = mlx_init();
	init_key(&map);
	map.height = 800;
	map.width = 1000;
	map.win = mlx_new_window(map.mlx, map.width, map.height, "RT IN RT");
	prog = get_prog("generate_ray.cl");
	ocl_init(&map.env, prog);
	raytracer(&map);
	draw(&map);
	mlx_key_hook(map.win, key_hook, &map);
	mlx_hook(map.win, 2, (1L << 0), key_press, &map);
	mlx_loop_hook(map.mlx, loop_hook, &map);
	mlx_loop(map.mlx);
}
