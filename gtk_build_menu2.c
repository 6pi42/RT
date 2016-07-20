/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_build_menu2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 14:39:00 by apaget            #+#    #+#             */
/*   Updated: 2016/07/19 15:36:26 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	create_sub_menu(menu, map, "Save picture");
	create_sub_menu(menu, map, "Quitter");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), root_menu);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(menu_bar), TRUE, TRUE,
		0);
}

void	create_world_conf(t_map *map, GtkWidget *onglet)
{
	GtkWidget	*interface;

	interface = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	map->obj_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	create_label(interface, "Multisampling");
	create_multi_sampling_bar(interface, map);
	create_label(interface, "Max depth");
	create_max_depth_bar(interface, map);
	manip_conf(map, interface);
	gtk_notebook_append_page(GTK_NOTEBOOK(onglet), GTK_WIDGET(interface),
		gtk_label_new("World"));
}

void	create_mat_conf(t_map *map, GtkWidget *onglet)
{
	GtkWidget	*label;

	map->interface = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	label = gtk_label_new("Couleurs :");
	gtk_box_pack_start(GTK_BOX(map->interface),
		GTK_WIDGET(label), FALSE, FALSE, 5);
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
	gtk_notebook_append_page(GTK_NOTEBOOK(onglet),
		GTK_WIDGET(map->interface), gtk_label_new("Mat"));
}
