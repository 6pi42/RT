/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/02 15:34:48 by amathias          #+#    #+#             */
/*   Updated: 2016/07/18 14:29:06 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_key(t_map *map)
{
	map->key.up = 0;
	map->key.down = 0;
	map->key.left = 0;
	map->key.right = 0;
	map->key.mleft = 0;
	map->key.mright = 0;
	map->key.mx = 0;
	map->key.my = 0;
	map->key.phi = 0.0f;
	map->key.theta = 0.0f;
}

void	motion_notify(GtkWidget *widget, GdkEventMotion *event, t_map *map)
{
	(void)widget;
	if (!map->config.fix)
	{
		map->free_cam.sensitivity = 1.0f;
		map->free_cam.phi +=
		(map->free_cam.old_mouse_pos.y - event->y) * map->free_cam.sensitivity;
		map->free_cam.theta -=
		(map->free_cam.old_mouse_pos.x - event->x) * map->free_cam.sensitivity;
		map->free_cam.old_mouse_pos.y = event->y;
		map->free_cam.old_mouse_pos.x = event->x;
		vector_from_angle(&map->free_cam);
		draw(map);
	}
}

void	redraw(GtkWidget *widget, GdkEvent *event, t_map *map)
{
	(void)widget;
	(void)event;
	draw(map);
}

int		key_press(GtkWidget *widget, GdkEventKey *event, t_map *map)
{
	(void)widget;
	if (!map->config.fix)
	{
		if (event->keyval == 'a')
			map->free_cam.pos = sub_vec(map->free_cam.pos,
				scale_vec(10.0f, map->free_cam.left));
		if (event->keyval == 'd')
			map->free_cam.pos = add_vec(map->free_cam.pos,
			scale_vec(10.0f, map->free_cam.left));
		if (event->keyval == 'w')
			map->free_cam.pos = add_vec(map->free_cam.pos,
				scale_vec(10.0f, map->free_cam.forward));
		if (event->keyval == 's')
			map->free_cam.pos = sub_vec(map->free_cam.pos,
				scale_vec(10.0f, map->free_cam.forward));
		draw(map);
	}
	if (event->keyval == 'c')
		print_scene(map);
	if (event->keyval == 102)
		map->config.fix ^= 1;
	if (event->keyval == 65307)
		gtk_main_quit();
	return (0);
}

int		key_release(GtkWidget *widget, GdkEventKey *event, t_map *map)
{
	(void)widget;
	if (event->keyval == 'd')
		map->key.mleft = 0;
	if (event->keyval == 'a')
		map->key.mright = 0;
	if (event->keyval == 'w')
		map->key.up = 0;
	if (event->keyval == 's')
		map->key.down = 0;
	return (0);
}
