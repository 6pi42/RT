/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/02 15:34:48 by amathias          #+#    #+#             */
/*   Updated: 2016/05/29 15:00:56 by apaget           ###   ########.fr       */
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

void		motion_notify(GtkWidget *widget, GdkEventMotion *event, t_map *map)
{
	(void)widget;

	if (!map->fix)
	{
		map->free_cam.sensitivity = 1.0f;
		map->free_cam.phi +=
		(map->free_cam.old_mouse_pos.y - event->y) * map->free_cam.sensitivity;
		map->free_cam.theta -=
		(map->free_cam.old_mouse_pos.x - event->x) * map->free_cam.sensitivity;
		map->free_cam.old_mouse_pos.y = event->y;
		map->free_cam.old_mouse_pos.x = event->x;
		vector_from_angle(&map->free_cam);
		if (!map->key.mright &&!map->key.mleft && !map->key.up && !map->key.down)
			draw(map);
	}
}

void		redraw(GtkWidget *widget, GdkEvent *event, t_map *map)
{
	(void)widget;
	(void)event;
	draw(map);
}

int		key_press(GtkWidget *widget, GdkEventKey *event, t_map *map)
{
	(void)widget;
	if (!map->fix)
	{
		if (event->keyval == 'a')
			map->key.mright = 1;
		if (event->keyval == 'd')
			map->key.mleft = 1;
		if (event->keyval == 'w')
			map->key.up = 1;
		if (event->keyval == 's')
			map->key.down = 1;
		update_cam(&map->free_cam, &map->key, map);
	}
	if (event->keyval == 32)
		map->fix ^= 1;
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
