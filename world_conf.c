/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_conf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 06:51:11 by apaget            #+#    #+#             */
/*   Updated: 2016/07/13 07:54:24 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_check_button(GtkWidget *interface, char *label, t_map *map)
{

	GtkWidget *check;
	check = gtk_check_button_new_with_label(label);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(check), FALSE, TRUE, 1);
	gtk_widget_set_name(GTK_WIDGET(check), label);
	g_signal_connect(G_OBJECT(check), "toggled",
											G_CALLBACK(check_bar), map);
}

void	check_bar(GtkWidget *widget, t_map *map)
{
	(void)map;
	//printf("coucou %d\n", gtk_toggle_button_get_mode(GTK_TOGGLE_BUTTON(widget)));
	if (ft_strsearch("texture", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.texture = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("refraction", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.refraction = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("reflection", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.reflection = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("filtre", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.filtre = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("transparence", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.transparence = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("ombre", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.ombre = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	else if (ft_strsearch("print_neg", (char*)gtk_widget_get_name(widget)) != -1)
		map->config.print_neg = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
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
	create_check_button(box, "filtre", map);
	create_check_button(box, "transparence", map);
	create_check_button(box, "ombre", map);
	gtk_box_pack_start(GTK_BOX(global_box), GTK_WIDGET(box), FALSE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(global_box), FALSE, TRUE, 10);
}
