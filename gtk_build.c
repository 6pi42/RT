/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 23:13:36 by apaget            #+#    #+#             */
/*   Updated: 2016/05/19 12:57:38 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_css_style(t_map *map, char *css_file)
{
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;
	GError *error;

	(void)map;
	(void)error;
	(void)css_file;
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);
	provider = gtk_css_provider_new();
	provider = gtk_css_provider_get_named("Adwaita", "dark");
	//gtk_css_provider_load_from_path(provider, css_file, &error);
	gtk_style_context_add_provider_for_screen(screen,
									GTK_STYLE_PROVIDER (provider),
									GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	g_object_unref(provider);
}

void	add_color_scroll_bar(GtkWidget *interface, char *label_str, t_map *map)
{
	GtkWidget	*box;
	GtkWidget	*scroll;
	GtkWidget	*label;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	label = gtk_label_new(label_str);
	scroll = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
	g_object_set(scroll, "digits", 0, NULL);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(label), FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(scroll), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), FALSE, TRUE, 0);
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

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	label = gtk_label_new(label_str);
	scroll = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 1, 0.05);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(label), FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(scroll), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(box), FALSE, TRUE, 0);
	g_signal_connect(G_OBJECT(scroll), "value-changed",
											G_CALLBACK(color_bare), map);
	gtk_widget_set_name(GTK_WIDGET(box), label_str);
	gtk_widget_set_name(GTK_WIDGET(scroll), label_str);
}

void	add_sep(GtkWidget *interface)
{
	GtkWidget	*sep;

	sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(sep), FALSE, TRUE, 0);

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
	add_coef_scroll_bar(interface, "Kr :", map);
	add_coef_scroll_bar(interface, "Krr :", map);
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

	max_deep = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 10, 1);
	g_signal_connect(G_OBJECT(max_deep), "value-changed",
											G_CALLBACK(max_depth_bar), map);
	gtk_scale_set_digits(GTK_SCALE(max_deep), 0);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(max_deep), FALSE,
			TRUE, 0);

}

void	create_label(GtkWidget *interface, char *label_str)
{
	GtkWidget	*label;

	label = gtk_label_new(label_str);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(label), FALSE, TRUE, 2);
	
}

void	create_left_bar(GtkWidget *interface, t_map *map)
{
	GtkWidget	*slct_file;

	slct_file = gtk_button_new_with_label("Choose scene file");
	g_signal_connect(slct_file, "clicked", G_CALLBACK(choose_file), map);
	map->obj_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(slct_file), FALSE,
																	TRUE, 10);
	create_label(interface, "Multisampling");
	create_multi_sampling_bar(interface, map);
	create_label(interface, "Max depth");
	create_max_depth_bar(interface, map);
	create_obj_interface(map->obj_box, map);
	gtk_box_pack_start(GTK_BOX(interface), GTK_WIDGET(map->obj_box), FALSE,
																	TRUE, 2);
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

void	create_interface(t_map *map)
{
	GtkWidget	*scree_box;
	GtkWidget	*event_box;
	GtkWidget	*frame_buffer;

	map->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	map->render = gtk_image_new_from_pixbuf(NULL);
	scree_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	frame_buffer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	map->interface = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	event_box = gtk_event_box_new();
	set_event(event_box, map);
	gtk_box_pack_start(GTK_BOX(scree_box), GTK_WIDGET(event_box), TRUE,
			FALSE, 0);
	gtk_container_add(GTK_CONTAINER(event_box), map->render);
	gtk_box_pack_end(GTK_BOX(scree_box), GTK_WIDGET(map->interface), TRUE,
				TRUE, 30);
	create_menu(frame_buffer, map);
	gtk_box_pack_start(GTK_BOX(frame_buffer), GTK_WIDGET(scree_box), FALSE,
			FALSE, 0);
	create_left_bar(map->interface, map);
	gtk_window_set_title(GTK_WINDOW(map->window), "Raytracer");
	//gtk_window_set_default_size (GTK_WINDOW(map->window), map->width,
	//		map->height);
	gtk_window_set_resizable(GTK_WINDOW(map->window), TRUE);
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
