/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 17:05:07 by apaget            #+#    #+#             */
/*   Updated: 2016/06/30 18:01:21 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate_obj(GtkWidget *widget, t_map *map)
{
	(void)widget;
	(void)map;
	rotate_cone_cyl(widget, map);
}


void	rotate_cone_cyl(GtkWidget *widget, t_map *map)
{
	gdouble value;
	cl_float4 new;
	cl_float4 save;


	value = gtk_range_get_value(GTK_RANGE(widget));
	save = map->obj_selected->axis;
	new = map->obj_selected->axis;
	if (ft_strsearch("x :", (char*)gtk_widget_get_name(widget)) != -1)
	{
		new.x = map->obj_selected->axis.x;
		new.y = map->obj_selected->axis.y * cos(value * M_PI / 180) + map->obj_selected->axis.z * sin(value * M_PI / 180);
		new.z = map->obj_selected->axis.y * sin(value * M_PI / 180) + map->obj_selected->axis.z * cos(value * M_PI / 180);
	}
	else if (ft_strsearch("y :", (char*)gtk_widget_get_name(widget)) != -1)
	{
		printf("wesh alors\n");
		new.x = map->obj_selected->axis.x * cos(value * M_PI / 180) +  map->obj_selected->axis.z * sin(value * M_PI / 180);
		new.y = map->obj_selected->axis.y;
		new.z = -map->obj_selected->axis.x * sin(value * M_PI / 180) + map->obj_selected->axis.z * cos(value * M_PI / 180);
	}
	else if (ft_strsearch("z :", (char*)gtk_widget_get_name(widget)) != -1)
	{
		new.x = map->obj_selected->axis.x * cos(value * M_PI / 180) +  map->obj_selected->axis.y * sin(value * M_PI / 180);
		new.y = map->obj_selected->axis.x * sin (value * M_PI / 180) +  map->obj_selected->axis.y * cos(value * M_PI / 180);
		new.z = -map->obj_selected->axis.z;
	}
	map->obj_selected->axis = new;
	normalize_vec(&map->obj_selected->axis);
	init_inter(map, map->height * map->width);
	map->obj_selected->axis = save;
	draw(map);
}
