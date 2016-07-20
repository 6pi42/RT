/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_build_bar2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 14:27:16 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 14:29:34 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_moove_scroll_bar(GtkWidget *interface, char *label_str, t_map *map,
		char *name)
{
	GtkWidget	*box;
	GtkWidget	*scroll;
	GtkWidget	*label;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	label = gtk_label_new(label_str);
	scroll = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -500, 500, 2);
	gtk_range_set_value(GTK_RANGE(scroll), 0);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(label), FALSE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(scroll), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), FALSE, TRUE, 0);
	gtk_widget_set_name(GTK_WIDGET(box), name);
	gtk_widget_set_name(GTK_WIDGET(scroll), name);
	g_signal_connect(G_OBJECT(scroll), "value-changed",
											G_CALLBACK(moove_obj), map);
	(void)map;
}

void	add_fleche(GtkWidget *interface, t_map *map, char *cote,
		char *label_str)
{
	char		*label;
	GtkWidget	*but;
	char		*name;

	but = gtk_button_new();
	g_signal_connect(G_OBJECT(but), "pressed",
											G_CALLBACK(rotate_obj), map);
	if (*cote == 'l')
		label = " ← ";
	else
		label = " → ";
	gtk_button_set_label(GTK_BUTTON(but), label);
	name = ft_strjoin(label_str, cote);
	gtk_widget_set_name(GTK_WIDGET(but), name);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(but), TRUE, TRUE, 0);
	free(name);
}

void	add_rotate_scroll_bar(GtkWidget *interface, char *label_str,
		t_map *map)
{
	GtkWidget	*box;
	GtkWidget	*box_h;

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(gtk_label_new(label_str)),
			TRUE, TRUE, 5);
	box_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	add_fleche(box_h, map, "l", label_str);
	add_fleche(box_h, map, "r", label_str);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(box_h), TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), TRUE, TRUE, 5);
}
