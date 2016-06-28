/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_call_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 02:46:46 by apaget            #+#    #+#             */
/*   Updated: 2016/06/28 14:41:47 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	switch_focus(GtkWidget *widget, GdkEventButton *event, t_map *map)
{
	(void)widget;
	int		id;
	t_ray	*prim;
	t_inter	*tmp;

	prim = get_primary(map);
	tmp = get_inter(map, (int)(map->height * map->width), prim);
	id = tmp[(int)(event->y * map->width + event->x)].id;
	printf("le normal de cette obj vaut %f %f %f\n", 
			tmp[(int)(event->y * map->height + event->x)].normal.x , tmp[(int)(event->y * map->height + event->x)].normal.y ,tmp[(int)(event->y * map->height + event->x)].normal.z);
	if (id != -1)
	{
	
		set_obj_box(map);
		gtk_widget_show(GTK_WIDGET(map->obj_box));
		map->obj_selected = &map->scene.shape[id];
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
