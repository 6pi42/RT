/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_call_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 02:48:16 by apaget            #+#    #+#             */
/*   Updated: 2016/06/28 16:26:24 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	max_depth_bar(GtkWidget *widget, t_map *map)
{
	gdouble value;

	value = gtk_range_get_value(GTK_RANGE(widget));
	map->scene.max_depth = value;
	raytrace(map);
}

void	color_bare(GtkWidget *widget, t_map *map)
{
	if (ft_strsearch("R :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->color.z = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("G :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->color.y = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("B :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->color.x = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("ka :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->mat.ka = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("Ks :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->mat.ks = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("kd :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->mat.kd = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("kd :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->mat.kd = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("kre :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->mat.kreflec = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("kra :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->mat.krefrac = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("indice :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->mat.indice = gtk_range_get_value(GTK_RANGE(widget)) / 2;
	draw(map);
}

void	sampling_bar(GtkWidget *widget, t_map *map)
{
	gdouble value;

	value = gtk_range_get_value(GTK_RANGE(widget));
	if (value < 4 && value > 2)
		value = 4;
	else if (value < 8 && value > 4)
		value = 8;
	map->multi_sampling = value;
	gtk_range_set_value(GTK_RANGE(widget), value);
	clSetKernelArg(map->env.kernel, 7, sizeof(cl_short), &map->multi_sampling);
	raytrace(map);
}
