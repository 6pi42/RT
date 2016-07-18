/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_build_bar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 03:35:19 by apaget            #+#    #+#             */
/*   Updated: 2016/07/17 13:16:00 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_color_scroll_bar(GtkWidget *interface, char *label_str, t_map *map)
{
	GtkWidget	*box;
	GtkWidget	*scroll;
	GtkWidget	*label;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	label = gtk_label_new(label_str);
	scroll = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
	g_object_set(scroll, "digits", 0, NULL);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(label), FALSE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(scroll), TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(scroll), "value-changed",
											G_CALLBACK(color_bare), map);
	gtk_widget_set_name(GTK_WIDGET(box), label_str);
	gtk_widget_set_name(GTK_WIDGET(scroll), label_str);
}

void	add_coef_scroll_bar(GtkWidget *interface, char *label_str, t_map *map)
{
	GtkWidget	*box;
	GtkWidget	*scroll;
	GtkWidget	*label;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	label = gtk_label_new(label_str);
	if (ft_strsearch(label_str, "Ka :") != -1)
		scroll = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.2, 1, 0.05);
	else
		scroll = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 1, 0.05);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(label), FALSE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(scroll), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), FALSE, TRUE, 0);
	g_signal_connect(G_OBJECT(scroll), "value-changed",
											G_CALLBACK(color_bare), map);
	gtk_widget_set_name(GTK_WIDGET(box), label_str);
	gtk_widget_set_name(GTK_WIDGET(scroll), label_str);
}


void	add_moove_scroll_bar(GtkWidget *interface, char *label_str, t_map *map, char *name)
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

void	add_fleche(GtkWidget *interface, t_map *map, char *cote, char *label_str)
{
	char	*label;
	GtkWidget	*but;
	char *name;

	but = gtk_button_new();
	(void)map;
	(void)cote;
	(void)label_str;
	(void)interface;
	g_signal_connect(G_OBJECT(but), "pressed",
											G_CALLBACK(rotate_obj), map);
	if (*cote == 'l')
		label = " ← ";
	else
		label =  " → ";
	gtk_button_set_label(GTK_BUTTON(but), label);
	name = ft_strjoin(label_str, cote);
	gtk_widget_set_name(GTK_WIDGET(but), name);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(but), TRUE, TRUE, 0);
	free(name);
}

void	add_rotate_scroll_bar(GtkWidget *interface, char *label_str, t_map *map)
{
	GtkWidget	*box;
	GtkWidget	*box_h;

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(gtk_label_new(label_str)), TRUE, TRUE, 5);
	box_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	add_fleche(box_h, map, "l", label_str);
	add_fleche(box_h, map, "r", label_str);
	(void)map;
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(box_h), TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), TRUE, TRUE, 5);
}

void	add_sep(GtkWidget *interface)
{
	GtkWidget	*sep;

	sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(sep), FALSE, TRUE, 0);
}

void	create_multi_sampling_bar(GtkWidget *interface, t_map *map)
{
	GtkWidget	*multisampling;

	multisampling = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
			0, 8, 1);
	g_signal_connect(G_OBJECT(multisampling), "value-changed",
											G_CALLBACK(sampling_bar), map);
	gtk_scale_set_digits(GTK_SCALE(multisampling), 0);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(multisampling), FALSE,
			TRUE, 0);
}

void	create_max_depth_bar(GtkWidget *interface, t_map *map)
{
	GtkWidget	*max_deep;

	max_deep = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 5, 1);
	g_signal_connect(G_OBJECT(max_deep), "value-changed",
											G_CALLBACK(max_depth_bar), map);
	gtk_scale_set_digits(GTK_SCALE(max_deep), 0);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(max_deep), FALSE,
			TRUE, 0);
}
