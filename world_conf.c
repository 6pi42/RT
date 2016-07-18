/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_conf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 06:51:11 by apaget            #+#    #+#             */
/*   Updated: 2016/07/17 13:27:45 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void	connect_check_button(GtkWidget *widget, t_map *map)
{
	if (ft_strsearch("texture", (char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), map->config.texture);
	else if (ft_strsearch("refraction", (char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), map->config.refraction);
	else if (ft_strsearch("reflection", (char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), map->config.reflection);
	else if (ft_strsearch("filtre noir et blanc", (char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), map->config.filtre_n);
	else if (ft_strsearch("filtre sepia", (char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), map->config.filtre_s);
	else if (ft_strsearch("transparence", (char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), map->config.transparence);
	else if (ft_strsearch("ombre", (char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), map->config.ombre);
	else if (ft_strsearch("print_neg", (char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), map->config.print_neg);
}

void	create_check_button(GtkWidget *interface, char *label, t_map *map)
{

	GtkWidget *check;
	check = gtk_check_button_new_with_label(label);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(check), FALSE, TRUE, 1);
	gtk_widget_set_name(GTK_WIDGET(check), label);
	connect_check_button(check, map);
	g_signal_connect(G_OBJECT(check), "toggled",
											G_CALLBACK(check_bar), map);
}

void	check_bar(GtkWidget *widget, t_map *map)
{
	if (ft_strsearch("texture", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.texture = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("refraction", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.refraction = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("reflection", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.reflection = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("filtre noir et blanc", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.filtre_n = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("filtre sepia", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.filtre_s = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("transparence", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.transparence = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("ombre", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.ombre = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("print_neg", (char*)gtk_widget_get_name(widget)) != -1)
	{
		map->config.print_neg = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		clSetKernelArg(map->env.kernel, 4, sizeof(cl_int), &map->config.print_neg);
	}
	draw(map);
}

void	manip_conf(t_map *map, GtkWidget *interface)
{
	GtkWidget *box;
	GtkWidget *global_box;


	(void)map;
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	global_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	create_check_button(box, "texture", map);
	create_check_button(box, "refraction", map);
	create_check_button(box, "reflection", map);
	create_check_button(box, "print_neg", map);
	gtk_box_pack_start(GTK_BOX(global_box), GTK_WIDGET(box), FALSE, TRUE, 10);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	create_check_button(box, "filtre noir et blanc", map);
	create_check_button(box, "filtre sepia", map);
	create_check_button(box, "transparence", map);
	create_check_button(box, "ombre", map);
	gtk_box_pack_start(GTK_BOX(global_box), GTK_WIDGET(box), FALSE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(global_box), FALSE, TRUE, 10);
}
