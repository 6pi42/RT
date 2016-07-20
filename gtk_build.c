/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 14:20:37 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 14:22:03 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_css_style(t_map *map, char *css_file)
{
	GtkCssProvider	*provider;
	GdkDisplay		*display;
	GdkScreen		*screen;

	(void)map;
	(void)css_file;
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);
	provider = gtk_css_provider_new();
	provider = gtk_css_provider_get_named("Adwaita", "dark");
	gtk_style_context_add_provider_for_screen(screen,
									GTK_STYLE_PROVIDER(provider),
									GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	g_object_unref(provider);
}

void	create_label(GtkWidget *interface, char *label_str)
{
	GtkWidget	*label;

	label = gtk_label_new(label_str);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(label), FALSE, TRUE, 2);
}

void	set_event(GtkWidget *event_box, t_map *map)
{
	gtk_widget_add_events(event_box, GDK_POINTER_MOTION_MASK |
			GDK_KEY_RELEASE_MASK | GDK_BUTTON_PRESS_MASK |
				GDK_BUTTON_RELEASE_MASK);
	g_signal_connect(event_box, "motion-notify-event",
													(void*)motion_notify, map);
	g_signal_connect(event_box, "enter-notify-event",
													(void*)update_old_pos, map);
	g_signal_connect(event_box, "leave-notify-event",
													(void*)leave_event, map);
	g_signal_connect(event_box, "button_press_event",
													(void*)switch_focus, map);
	g_signal_connect(G_OBJECT(map->window), "destroy",
													G_CALLBACK(exit_rt), map);
}
