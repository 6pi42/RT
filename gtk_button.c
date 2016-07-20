/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 14:57:10 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 14:23:34 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	changed(GtkWidget *wid, GtkAllocation *alloc, t_map *map)
{
	(void)wid;
	map->width = alloc->width;
	map->height = alloc->height;
	init_inter(map, (size_t)(map->width * map->height));
	raytrace(map);
}

void	resized(GtkWidget *wid, t_map *map)
{
	GtkAllocation alloc;

	(void)wid;
	gtk_widget_get_allocation(map->event_box, &alloc);
	map->width = alloc.width;
	map->height = alloc.height;
	init_inter(map, (size_t)(map->width * map->height));
	raytrace(map);
}

void	connect_signal_gtk(t_map *map)
{
	g_signal_connect(GTK_WINDOW(map->window), "key_press_event",
													(void*)key_press, map);
}
