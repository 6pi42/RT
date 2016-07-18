/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 17:05:07 by apaget            #+#    #+#             */
/*   Updated: 2016/07/17 14:12:54 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate_obj(GtkWidget *widget, t_map *map)
{
	if (map->obj_selected != NULL)
		rotate_cone_cyl(widget, map);
}


void	rotate_cone_cyl(GtkWidget *widget, t_map *map)
{
	gdouble value;
	cl_float4 new;
	const gchar		*wid_name;

	wid_name = gtk_widget_get_name(widget);
	if (wid_name[1] == 'r')
		value = -10;
	else 
		value = 10;
	new = map->obj_selected->axis;
	if (wid_name[0] == 'x')
	{
		new.x = map->obj_selected->axis.x;
		new.y = map->obj_selected->axis.y * cos(value * M_PI / 180) - map->obj_selected->axis.z * sin(value * M_PI / 180);
		new.z = map->obj_selected->axis.y * sin(value * M_PI / 180) + map->obj_selected->axis.z * cos(value * M_PI / 180);
	}
	else if (wid_name[0] =='y')
	{
		new.x = map->obj_selected->axis.z * sin(value * M_PI / 180) +  map->obj_selected->axis.x * cos(value * M_PI / 180);
		new.y = map->obj_selected->axis.y;
		new.z = map->obj_selected->axis.z * cos(value * M_PI / 180) - map->obj_selected->axis.x * sin(value * M_PI / 180);
	}
	else if (wid_name[0] == 'z')
	{
		new.x = map->obj_selected->axis.x * cos(value * M_PI / 180) - map->obj_selected->axis.y * sin(value * M_PI / 180);
		new.y = map->obj_selected->axis.x * sin (value * M_PI / 180) +  map->obj_selected->axis.y * cos(value * M_PI / 180);
		new.z = map->obj_selected->axis.z;
	}
	map->obj_selected->axis = new;
	normalize_vec(&map->obj_selected->axis);
	init_inter(map, map->height * map->width);
	draw(map);
}
