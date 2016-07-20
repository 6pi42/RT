/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_build_menu3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 14:39:56 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 14:48:47 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_rotate_bar(GtkWidget *interface, t_map *map)
{
	GtkWidget *box;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	add_rotate_scroll_bar(box, "x", map);
	add_rotate_scroll_bar(box, "y", map);
	add_rotate_scroll_bar(box, "z", map);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), FALSE, FALSE, 5);
}

void	add_dep_bar(GtkWidget *interface, t_map *map)
{
	GtkWidget *box;

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	add_moove_scroll_bar(box, "x :", map, "x :");
	add_moove_scroll_bar(box, "y :", map, "y :");
	add_moove_scroll_bar(box, "z :", map, "z :");
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), TRUE, TRUE, 5);
}

void	add_dep_light_bar(GtkWidget *interface, t_map *map)
{
	GtkWidget *box;

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	add_moove_scroll_bar(box, "x :", map, "x_l");
	add_moove_scroll_bar(box, "y :", map, "y_l");
	add_moove_scroll_bar(box, "z :", map, "z_l");
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), TRUE, TRUE, 5);
}

void	create_transform_bar(t_map *map, GtkWidget *onglet)
{
	GtkWidget *interface;

	interface = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_box_pack_start(GTK_BOX(interface),
		GTK_WIDGET(gtk_label_new("ROTATE MOTHER FUCKER")), FALSE, TRUE, 10);
	add_rotate_bar(interface, map);
	gtk_box_pack_start(GTK_BOX(interface),
		GTK_WIDGET(gtk_label_new("MOOVE MOTHER FUCKER")), FALSE, TRUE, 10);
	add_dep_bar(interface, map);
	gtk_box_pack_start(GTK_BOX(interface),
	GTK_WIDGET(gtk_label_new("MOOVE LIGHT MOTHER FUCKER")), FALSE, TRUE, 10);
	add_dep_light_bar(interface, map);
	gtk_notebook_append_page(GTK_NOTEBOOK(onglet),
		GTK_WIDGET(interface), gtk_label_new("Transform"));
}
