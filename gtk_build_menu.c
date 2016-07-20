/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_build_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 03:37:42 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 14:48:41 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_left_bar(GtkWidget *interface, t_map *map, GtkWidget *onglet)
{
	(void)interface;
	create_world_conf(map, onglet);
	create_mat_conf(map, onglet);
	create_obj_interface(map->obj_box, map);
	create_transform_bar(map, onglet);
}

void	create_obj_interface(GtkWidget *interface, t_map *map)
{
	GtkWidget	*label;

	label = gtk_label_new("Couleurs :");
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(label), FALSE, TRUE, 0);
	add_sep(interface);
	add_color_scroll_bar(interface, "R :", map);
	add_color_scroll_bar(interface, "G :", map);
	add_color_scroll_bar(interface, "B :", map);
	add_sep(interface);
	add_coef_scroll_bar(interface, "Ka :", map);
	add_coef_scroll_bar(interface, "Ks :", map);
	add_coef_scroll_bar(interface, "Kd :", map);
	add_coef_scroll_bar(interface, "kre :", map);
	add_coef_scroll_bar(interface, "kra :", map);
	add_coef_scroll_bar(interface, "indice :", map);
}

void	init_map_widget(t_map *map)
{
	map->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	map->render = gtk_image_new_from_pixbuf(NULL);
	map->event_box = gtk_event_box_new();
	set_event(map->event_box, map);
	gtk_container_add(GTK_CONTAINER(map->event_box), map->render);
}

void	set_conf_wind(t_map *map)
{
	gtk_window_set_resizable(GTK_WINDOW(map->window), TRUE);
	gtk_widget_show_all(map->window);
}

void	create_interface(t_map *map)
{
	GtkWidget	*scree_box;
	GtkWidget	*frame_buffer;
	GtkWidget	*onglet;
	GtkWidget	*interface;

	onglet = gtk_notebook_new();
	init_map_widget(map);
	scree_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	frame_buffer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	interface = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(scree_box), GTK_WIDGET(map->event_box), TRUE,
		TRUE, 10);
	gtk_box_pack_end(GTK_BOX(scree_box), GTK_WIDGET(interface), FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(onglet), FALSE,
		FALSE, 10);
	create_menu(frame_buffer, map);
	gtk_box_pack_start(GTK_BOX(frame_buffer), GTK_WIDGET(scree_box), TRUE,
			FALSE, 0);
	map->world_interface = onglet;
	create_left_bar(interface, map, onglet);
	gtk_window_set_title(GTK_WINDOW(map->window), "Raytracer");
	gtk_window_set_default_size(GTK_WINDOW(map->window), map->width,
		map->height);
	gtk_container_add(GTK_CONTAINER(map->window), GTK_WIDGET(frame_buffer));
	set_conf_wind(map);
}
