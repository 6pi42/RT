/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_build_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 03:37:42 by apaget            #+#    #+#             */
/*   Updated: 2016/07/14 05:22:08 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_world_conf(t_map *map, GtkWidget *onglet)
{
	GtkWidget	*slct_file;
	GtkWidget *interface;

	interface = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	slct_file = gtk_button_new_with_label("Choose scene file");
	g_signal_connect(slct_file, "clicked", G_CALLBACK(choose_file), map);
	map->obj_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(slct_file), FALSE,
																	TRUE, 10);
	create_label(interface, "Multisampling");
	create_multi_sampling_bar(interface, map);
	create_label(interface, "Max depth");
	create_max_depth_bar(interface, map);
	manip_conf(map, interface);
	gtk_notebook_append_page(GTK_NOTEBOOK(onglet), GTK_WIDGET(interface), gtk_label_new("World"));
}

void	create_mat_conf(t_map *map, GtkWidget *onglet)
{

	map->interface = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	GtkWidget	*label;

	label = gtk_label_new("Couleurs :");
	gtk_box_pack_start(GTK_BOX(map->interface), GTK_WIDGET(label), FALSE, FALSE, 5);
	add_sep(map->interface);
	add_color_scroll_bar(map->interface, "R :", map);
	add_color_scroll_bar(map->interface, "G :", map);
	add_color_scroll_bar(map->interface, "B :", map);
	add_sep(map->interface);
	add_coef_scroll_bar(map->interface, "Ka :", map);
	add_coef_scroll_bar(map->interface, "Ks :", map);
	add_coef_scroll_bar(map->interface, "Kd :", map);
	add_sep(map->interface);
	add_coef_scroll_bar(map->interface, "kre :", map);
	add_coef_scroll_bar(map->interface, "kra :", map);
	add_coef_scroll_bar(map->interface, "indice :", map);
	gtk_notebook_append_page(GTK_NOTEBOOK(onglet), GTK_WIDGET(map->interface), gtk_label_new("Mat"));
}


void	add_rotate_bar(GtkWidget *interface, t_map *map)
{
	GtkWidget *box;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	add_rotate_scroll_bar(box, "x", map);
	add_rotate_scroll_bar(box, "y", map);
	add_rotate_scroll_bar(box, "z", map);
	
	(void)map;
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), FALSE, FALSE, 5);
}

void	add_dep_bar(GtkWidget *interface, t_map *map)
{
	(void)interface;
	(void)map;
	GtkWidget *box;
	//GtkWidget *apply;

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	add_moove_scroll_bar(box, "x :", map, "x :");
	add_moove_scroll_bar(box, "y :", map, "y :");
	add_moove_scroll_bar(box, "z :", map, "z :");
	//apply = gtk_button_new_with_label("Apply");

	//gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(apply), TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), TRUE, TRUE, 5);
}

void	add_dep_light_bar(GtkWidget *interface, t_map *map)
{
	(void)interface;
	(void)map;
	GtkWidget *box;
	//GtkWidget *apply;

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	add_moove_scroll_bar(box, "x :", map, "x_l");
	add_moove_scroll_bar(box, "y :", map, "y_l");
	add_moove_scroll_bar(box, "z :", map, "z_l");
	//apply = gtk_button_new_with_label("Apply");

	//gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(apply), TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), TRUE, TRUE, 5);
}

void	create_transform_bar(t_map *map, GtkWidget *onglet)
{
	GtkWidget *interface;

	interface = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(gtk_label_new("ROTATE MOTHER FUCKER")), FALSE, TRUE, 10);
	add_rotate_bar(interface, map);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(gtk_label_new("MOOVE MOTHER FUCKER")), FALSE, TRUE, 10);
	add_dep_bar(interface, map);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(gtk_label_new("MOOVE LIGHT MOTHER FUCKER")), FALSE, TRUE, 10);
	add_dep_light_bar(interface, map);
	gtk_notebook_append_page(GTK_NOTEBOOK(onglet), GTK_WIDGET(interface), gtk_label_new("Transform"));
}


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

void	create_interface(t_map *map)
{
	GtkWidget	*scree_box;
	GtkWidget	*event_box;
	GtkWidget	*frame_buffer;
	GtkWidget	*onglet;
	GtkWidget	*interface;

	onglet = gtk_notebook_new();
	map->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	map->render = gtk_image_new_from_pixbuf(NULL);
	scree_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	frame_buffer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	interface = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	event_box = gtk_event_box_new();
	set_event(event_box, map);
	gtk_box_pack_start(GTK_BOX(scree_box), GTK_WIDGET(event_box), FALSE,
			FALSE, 10);
	gtk_container_add(GTK_CONTAINER(event_box), map->render);
	gtk_box_pack_end(GTK_BOX(scree_box), GTK_WIDGET(interface), TRUE,
				TRUE, 5);

	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(onglet), FALSE,
				FALSE, 10);

	create_menu(frame_buffer, map);
	gtk_box_pack_start(GTK_BOX(frame_buffer), GTK_WIDGET(scree_box), FALSE,
			FALSE, 0);
	create_left_bar(interface, map, onglet);
	gtk_window_set_title(GTK_WINDOW(map->window), "Raytracer");
	gtk_window_set_default_size (GTK_WINDOW(map->window), map->width,
			map->height);
	gtk_window_set_resizable(GTK_WINDOW(map->window), FALSE);
	gtk_container_add(GTK_CONTAINER(map->window), GTK_WIDGET(frame_buffer));
	gtk_widget_show_all(map->window);
	if (map->obj_selected == NULL)
		gtk_widget_hide(GTK_WIDGET(map->obj_box));
}

void	create_sub_menu(GtkWidget *menu, t_map *map, char *label)
{
	GtkWidget	*menu_item;

	menu_item = gtk_menu_item_new_with_label(label);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
	gtk_widget_set_name(GTK_WIDGET(menu_item), label);
	g_signal_connect(G_OBJECT(menu_item), "activate",
			G_CALLBACK(menu_connect), map);
}

void	create_menu(GtkWidget *interface, t_map *map)
{
	GtkWidget	*menu_bar;
	GtkWidget	*root_menu;
	GtkWidget	*menu;

	menu = gtk_menu_new();
	menu_bar = gtk_menu_bar_new();
	root_menu = gtk_menu_item_new_with_label("Menu");
	create_sub_menu(menu, map, "Open scene");
	create_sub_menu(menu, map, "Save picture");
	create_sub_menu(menu, map, "Ouvrir generateur de scene");
	create_sub_menu(menu, map, "Quitter");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM (root_menu), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), root_menu);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(menu_bar), TRUE, TRUE,
			0);
}
