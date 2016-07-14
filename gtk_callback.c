/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 07:29:15 by apaget            #+#    #+#             */
/*   Updated: 2016/07/14 04:50:33 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	exit_rt(t_map *map)
{
	(void)map;
	gtk_main_quit();
}

void	menu_connect(GtkWidget *widget, t_map *map)
{
	if (ft_strsearch("Open scene",
									(char*)gtk_widget_get_name(widget)) != -1)
		choose_file(widget, map);
	else if (ft_strsearch("Quitter",
									(char*)gtk_widget_get_name(widget)) != -1)
		exit_rt(map);
	else if (ft_strsearch("Save picture",
									(char*)gtk_widget_get_name(widget)) != -1)
		write_bitmap(map);
	else if (ft_strsearch("Ouvrir generateur de scene",
									(char*)gtk_widget_get_name(widget)) != -1)
		open_generateur_scene(map);
}

void	open_generateur_scene(t_map *map)
{
	char	*file_name;
	int		fd;

	system("python main.py > .jesuiscacher");
	if ((fd = open(".jesuiscacher", O_RDONLY)) == -1)
		return ;
	get_next_line(fd, &file_name);
	if (ft_strsearch("Erreur :", file_name) != -1)
	{
		ft_putstr("Erreur :\n");
		while (get_next_line(fd, &file_name))
			ft_putstr(file_name);
		return ;
	}
	if (ft_strlen(file_name) > 50)
	{
		ft_putstr("erreur lors du l'execution du generateur de scene\n");
		return ;
	}
	system("/bin/rm -f .jesuiscacher");
	load_new_scene(map, file_name);
}

void	load_new_scene(t_map *map, char *file_name)
{
	printf("le fichier charger : %s\n", file_name);
	//free_scene(&map->scene); // TODO: MEMORY non allocated apparament 
	map->scene.nb_shape = get_nb_shape(file_name);
	map->scene.shape = parse(map, file_name);
	printf("ptr shape : %p\n", map->scene.shape);
	map->obj_selected = map->scene.shape;
	init_inter(map, map->height * map->width);
	printf("coucou\n");
	raytrace(map);
}

void	choose_file(GtkWidget *widget, t_map *map)
{
	GtkWidget		*dialog;
	GtkFileChooser	*chooser;
	char			*filename;
	gint			res;

	(void)widget;
	dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(map->window),
			GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL,
							"Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		printf(" DEBUG FILENAME %s\n\n", filename);
		load_new_scene(map, filename);
		//free(filename);
	}
	gtk_widget_destroy(dialog);
}
