/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <amathias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:05:26 by amathias          #+#    #+#             */
/*   Updated: 2016/07/15 14:28:11 by emontagn         ###   ########.fr       */
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

void	init_config(t_conf *conf)
{
	conf->fix = 0;
	conf->refraction = 1;
	conf->reflection = 1;
	conf->filtre = 0;
	conf->transparence = 1;
	conf->ombre = 1;
	conf->print_neg = 0;
	conf->texture = 1;
}

void	draw(t_map *map)
{
	struct timeval sub;

	map->fps.frames++;
	gettimeofday(&map->fps.end, NULL);
	raytrace(map);
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

	if (argc != 2)
		return (1);
	map.scene.nb_shape = get_nb_shape(argv[1]);
	shape = parse(&map, argv[1]);
	int *tex = get_perl_tex(512, 512, 100);

	(void)tex;
	map.free_cam.pos.x = 20.0f;
	map.free_cam.pos.y = 20.0f;
	map.free_cam.pos.z = -20.0f;
	map.scene.max_depth = 0;
	map.scene.shape = shape;
	map.scene.cam = &cam;
	map.scene.nb_spot = 1;
	map.obj_selected = shape;
	map.scene.nb_mat = 1;
	map.fix = 0;

	gtk_init(&argc, &argv);
	init_config(&map.config);
	create_interface(&map);
	connect_signal_gtk(&map);
	set_css_style(&map, "style.css");
	prog = get_prog("intersect.cl");
	ocl_init(&map.env, prog);
	init_inter(&map, (size_t)(map.width * map.height));
	gettimeofday(&map.fps.start, NULL);
	draw(&map);
	gtk_main();
}
