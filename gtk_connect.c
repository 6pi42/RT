/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_conect_interface.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 02:40:29 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 14:33:49 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GtkWidget	*find_widget_with_name(char *name, t_map *map, GtkWidget *interface)
{
	GList		*list;
	char		*name2;
	GtkWidget	*tmp;

	list = gtk_container_get_children(GTK_CONTAINER(interface));
	while (list)
	{
		name2 = (char*)gtk_widget_get_name((GtkWidget*)list->data);
		if (ft_strsearch(name2, name) != -1)
			return (list->data);
		if (ft_strsearch(name2, "GtkBox") != -1)
		{
			tmp = find_widget_with_name(name, map, list->data);
			if (tmp != NULL)
				return (tmp);
		}
		list = list->next;
	}
	return (NULL);
}

void		connect_scroll_bar(t_map *map, char *name, float value,
		GtkWidget *interface)
{
	GtkWidget	*tmp;
	GList		*list;

	if (!(tmp = find_widget_with_name(name, map, interface)))
		return ;
	list = gtk_container_get_children(GTK_CONTAINER(tmp));
	if (!list || !list->next)
		return ;
	tmp = (GtkWidget*)list->next->data;
	gtk_range_set_value(GTK_RANGE(tmp), value);
}

void		connect_light(t_map *map)
{
	connect_scroll_bar(map, "x_l", map->scene.spot[0].pos.x,
			map->world_interface);
	connect_scroll_bar(map, "y_l", map->scene.spot[0].pos.y,
			map->world_interface);
	connect_scroll_bar(map, "z_l", map->scene.spot[0].pos.z,
			map->world_interface);
}

void		set_obj_box(t_map *map)
{
	t_mat *mat;

	if (map->obj_selected != NULL)
	{
		mat = &map->scene.mat[map->obj_selected->mat_id];
		connect_scroll_bar(map, "R :", map->obj_selected->color.x,
				map->interface);
		connect_scroll_bar(map, "G :", map->obj_selected->color.y,
				map->interface);
		connect_scroll_bar(map, "B :", map->obj_selected->color.z,
				map->interface);
		connect_scroll_bar(map, "Ka :", mat->ka, map->interface);
		connect_scroll_bar(map, "Ks :", mat->ks, map->interface);
		connect_scroll_bar(map, "Kd :", mat->kd, map->interface);
		connect_scroll_bar(map, "kre :", mat->kreflec, map->interface);
		connect_scroll_bar(map, "kra :", mat->krefrac, map->interface);
		connect_scroll_bar(map, "indice :", mat->indice, map->interface);
		connect_scroll_bar(map, "x :", map->obj_selected->pos.x,
				map->world_interface);
		connect_scroll_bar(map, "y :", map->obj_selected->pos.y,
				map->world_interface);
		connect_scroll_bar(map, "z :", map->obj_selected->pos.z,
				map->world_interface);
	}
	connect_light(map);
}
