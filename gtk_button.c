/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 14:57:10 by apaget            #+#    #+#             */
/*   Updated: 2016/07/17 16:48:14 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	changed(GtkWidget *wid, GtkAllocation *alloc, t_map *map)
{

	(void)map;
	(void)alloc;	
	(void)wid;
	printf("ntmi %d\n", alloc->width);
	map->width = alloc->width;
	map->height = alloc->height;
	init_inter(map, (size_t)(map->width * map->height));
	raytrace(map);
}

void	resized(GtkWidget *wid, t_map *map)
{
	(void)map;
	(void)wid;
	
	GtkAllocation alloc;

	gtk_widget_get_allocation(map->event_box, &alloc);
	printf("ntm2: %d\n", alloc.width);
	map->width = alloc.width;
	map->height = alloc.height;
	//changed(map->event_box, &alloc, map);
	init_inter(map, (size_t)(map->width * map->height));
	raytrace(map);
	
	//map->width = ;
	//map->height = 0;	
}

void	connect_signal_gtk(t_map *map)
{
	g_signal_connect(GTK_WINDOW(map->window), "key_press_event",
													(void*)key_press, map);
	//g_signal_connect(GTK_WINDOW(map->window), "check-resize",
	//												(void*)resized, map);
	//g_signal_connect(GTK_WIDGET(map->event_box), "size_allocate",
	//												(void*)changed, map);

}
