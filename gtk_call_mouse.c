/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_call_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 02:46:46 by apaget            #+#    #+#             */
/*   Updated: 2016/07/16 16:00:52 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	switch_focus(GtkWidget *widget, GdkEventButton *event, t_map *map)
{
	t_ray	*prim;
	t_inter	*tmp;
	int		id = -1;

	int i;
	for (i = 0; i < map->scene.nb_shape; i++) {
		printf("color : %f %f %f\n", map->scene.shape[i].color.x, map->scene.shape[i].color.y, map->scene.shape[i].color.z);
	}

	if (event->y * map->width + event->x > map->width * map->height)
		return;
	(void)widget;
	prim = get_primary(map);
	tmp = get_inter(map, (int)(map->height * map->width), prim);
	id = tmp[(int)((int)event->y * map->width + (int)event->x)].id;
	if (id != -1)
	{
		printf("set\n");
		map->obj_selected = &map->scene.shape[id];
		set_obj_box(map);
	}
	else
		map->obj_selected = &map->scene.shape[0];
	free(prim);
	free(tmp);
}

void	update_old_pos(GtkWidget *widget, GdkEventCrossing *event, t_map *map)
{
	(void)widget;
	map->free_cam.old_mouse_pos.y = event->y;
	map->free_cam.old_mouse_pos.x = event->x;
	gtk_widget_set_sensitive(GTK_WIDGET(map->interface), FALSE);
}
