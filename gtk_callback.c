/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 07:29:15 by apaget            #+#    #+#             */
/*   Updated: 2016/05/29 14:56:41 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
void	exit_rt(t_map *map)
{
	//free tout biem comme il faut
	(void)map;
	gtk_main_quit();

}

void	sampling_bar(GtkWidget *widget, t_map *map)
{
	gdouble value;

	value = gtk_range_get_value(GTK_RANGE(widget));
	if (value < 4 && value > 2)
		value = 4;
	else if (value < 8 && value > 4)
		value = 8;
	map->multi_sampling = value;
	gtk_range_set_value(GTK_RANGE(widget), value);
	clSetKernelArg(map->env.kernel, 7, sizeof(cl_short), &map->multi_sampling);
	draw(map);
}

void	max_depth_bar(GtkWidget *widget, t_map *map)
{
	gdouble value;
	(void)map;

	value = gtk_range_get_value(GTK_RANGE(widget));
	printf("max deep vaut %f\n", value);
}

void	color_bare(GtkWidget *widget, t_map *map)
{
	if (ft_strsearch("R :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->color.z = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("G :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->color.y = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("B :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->color.x = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("ka :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->color.y = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("Ks :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->color.y = gtk_range_get_value(GTK_RANGE(widget));
	else if (ft_strsearch("kd :", (char*)gtk_widget_get_name(widget)) != -1)
		map->obj_selected->color.y = gtk_range_get_value(GTK_RANGE(widget));
	printf("Type %f %.0f %.0f %.0f\n",map->obj_selected->type.x, map->obj_selected->color.x, map->obj_selected->color.y, map->obj_selected->color.z);
	draw(map);
}

void	menu_connect(GtkWidget *widget, t_map *map)
{
	if (ft_strsearch("Open scene", (char*)gtk_widget_get_name(widget)) != -1)
		choose_file(widget, map);
	else if (ft_strsearch("Quitter", (char*)gtk_widget_get_name(widget)) != -1)
		exit_rt(map);
	else if (ft_strsearch("Save picture", (char*)gtk_widget_get_name(widget)) != -1)
		write_bitmap(map);
	else if (ft_strsearch("Ouvrir generateur de scene", (char*)gtk_widget_get_name(widget)) != -1)
		open_generateur_scene(map);
}

void	update_old_pos(GtkWidget *widget, GdkEventCrossing *event, t_map *map)
{
	(void)widget;
	map->free_cam.old_mouse_pos.y = event->y;
	map->free_cam.old_mouse_pos.x = event->x;
	gtk_widget_set_sensitive(GTK_WIDGET(map->interface), FALSE);
}

void	switch_focus(GtkWidget *widget, GdkEventCrossing *event, t_map *map)
{
	(void)event;
	(void)widget;
	(void)map;
	if (!map->obj_selected)
	{
		gtk_widget_hide(GTK_WIDGET(map->obj_box));
		return;
	}
	else
		gtk_widget_show(GTK_WIDGET(map->obj_box));
	set_obj_box(map);
}

void	open_generateur_scene(t_map *map)
{
	char	*file_name;
	int fd;

	system("python main.py > .jesuiscacher");
	if((fd = open("tmp.tmp", O_RDONLY)) == -1)
		return ;
	get_next_line(fd, &file_name);
	if (ft_strsearch("Erreur :", file_name) != -1)
	{
		ft_putstr("Erreur :\n");
		while (get_next_line(fd, &file_name))
			ft_putstr(file_name);
		return;
	}
	if (ft_strlen(file_name) > 50)
	{
		ft_putstr("erreur lors du l'execution du generateur de scene\n");
		return;
	}
	system("/bin/rm -f .jesuiscacher");
	load_new_scene(map, file_name);
}

void	load_new_scene(t_map *map, char *file_name)
{
	printf("le fichier charger : %s\n", file_name);
	free_scene(&map->scene);
	parse(map, file_name);
	map->obj_selected = NULL;//&map->scene.shape[0];
	//raytracer(map);
	scene_update(map);
	draw(map);
}

void	choose_file(GtkWidget *widget, t_map *map)
{
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	char *filename;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

	(void)widget;
	gint res;
	dialog = gtk_file_chooser_dialog_new ("Open File",
										  GTK_WINDOW(map->window),
										  action,
										  "_Cancel",
										  GTK_RESPONSE_CANCEL,
										  "_Open",
										  GTK_RESPONSE_ACCEPT,
										  NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	  {
		chooser = GTK_FILE_CHOOSER (dialog);
		filename =  gtk_file_chooser_get_filename (chooser);
		printf("%s\n\n",filename);
		load_new_scene(map, filename);
		//g_free(filename);
	  }
	gtk_widget_destroy (dialog);
}
