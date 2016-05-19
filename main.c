/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:05:26 by amathias          #+#    #+#             */
/*   Updated: 2016/05/19 14:30:03 by amathias         ###   ########.fr       */
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

void	draw(t_map *map)
{
	struct timeval sub;

	map->fps.frames++;
	gettimeofday(&map->fps.end, NULL);
	raytrace(map);
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
	t_camera	cam;
	cl_float4	spot;

	if (argc != 2)
		return (1);
	map.scene.nb_shape = get_nb_shape(argv[1]);
	shape = parse(&map, argv[1]);
	spot.x = 50.0f;
	spot.y = 200.0f;
	spot.z = 0.0f;
	spot.w = 0.0f;
	map.free_cam.pos.x = 0;
	map.free_cam.pos.y = 50;
	map.free_cam.pos.z = 500;
	map.scene.shape = shape;
	map.scene.cam = &cam;
	map.scene.spot = &spot;
	map.scene.nb_spot = 1;
	map.mlx = mlx_init();
	init_key(&map);
	map.win = mlx_new_window(map.mlx, map.width, map.height, "RT");
	map.img.img = mlx_new_image(map.mlx, map.width, map.height);
	map.img.data = mlx_get_data_addr(map.img.img, &(map.img.bpp),
			&(map.img.size_line), &(map.img.endian));
	prog = get_prog("intersect.cl");
	ocl_init(&map.env, prog);
	init_inter(&map);
	gettimeofday(&map.fps.start, NULL);
	draw(&map);
	mlx_key_hook(map.win, key_hook, &map);
	mlx_hook(map.win, 2, (1L << 0), key_press, &map);
	mlx_hook(map.win, 6, (1L << 6), motion_notify, &map);
	mlx_loop_hook(map.mlx, loop_hook, &map);
	mlx_loop(map.mlx);
}
