/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_conect_interface.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 02:40:29 by apaget            #+#    #+#             */
/*   Updated: 2016/06/10 15:03:19 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GtkWidget	*find_widget_with_name(char *name, t_map *map)
{
	GList	*list;
	char	*name2;

	list = gtk_container_get_children(GTK_CONTAINER(map->obj_box));
	while (list)
	{
		name2 = (char*)gtk_widget_get_name((GtkWidget*)list->data);
		if (ft_strsearch(name2, name) != -1)
			return (list->data);
		list = list->next;
	}
	return (NULL);
}

void		connect_scroll_bar(t_map *map, char *name, float value)
{
	GtkWidget	*tmp;
	GList		*list;

	if (!(tmp = find_widget_with_name(name, map)))
		return ;
	list = gtk_container_get_children(GTK_CONTAINER(tmp));
	if (!list || !list->next)
		return ;
	tmp = (GtkWidget*)list->next->data;
	gtk_range_set_value(GTK_RANGE(tmp), value);
}

void		set_obj_box(t_map *map)
{
	if (map->obj_selected != NULL)
	{
		connect_scroll_bar(map, "R :", map->obj_selected->color.x);
		connect_scroll_bar(map, "G :", map->obj_selected->color.y);
		connect_scroll_bar(map, "B :", map->obj_selected->color.z);
		connect_scroll_bar(map, "Ka :", map->obj_selected->mat.ka);
		connect_scroll_bar(map, "Ks :", map->obj_selected->mat.ks);
		connect_scroll_bar(map, "Kd :", map->obj_selected->mat.kd);
	}
}
