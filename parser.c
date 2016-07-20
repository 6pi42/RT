/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:54:18 by emontagn          #+#    #+#             */
/*   Updated: 2016/07/19 14:37:12 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_strsearch(char *str1, char *str2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str1[j] && str2[i])
	{
		if (str1[j] == str2[i])
			i++;
		else
			i = 0;
		if (i == (int)ft_strlen(str2))
			return (j + 1);
		j++;
	}
	return (-1);
}

int		get_number(char *file, char *shape_name)
{
	int		i;
	char	*line;
	int		ret;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		printf("error get number\n");
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strsearch(line, shape_name) != -1)
			i++;
		free(line);
	}
	if (ret == -1)
		printf("error get number\n");
	close(fd);
	return (i);
}

int		get_nb_shape(char *file)
{
	int		shape_nb;

	shape_nb = get_number(file, "Plane") + get_number(file, "Sphere") +
	get_number(file, "Cone") + get_number(file, "Cylinder") +
	get_number(file, "Ellipsoid") + get_number(file, "Triangle") +
	get_number(file, "Cercle") + get_number(file, "Cube") +
	get_number(file, "Thorus");
	return (shape_nb);
}

void	parsing(t_parse *fuck, t_map *map, char *line, int fd)
{
	if (ft_strsearch(line, "Multi Sampling") != -1)
		get_multi_sampling(fd, map);
	else if (ft_strsearch(line, "mat") != -1)
		get_material(fd, fuck);
	else if (ft_strsearch(line, "Camera") != -1)
		get_camera(fd, map);
	else if (ft_strsearch(line, "Window") != -1)
		get_window(fd, map);
	else if (ft_strsearch(line, "Spotlight") != -1)
		get_spotlight(fd, map);
	else if (ft_strsearch(line, "Plane") != -1)
		get_plane(fd, fuck);
	else if (ft_strsearch(line, "Sphere") != -1)
		get_sphere(fd, fuck);
	else if (ft_strsearch(line, "Ellipsoid") != -1)
		get_ellipsoid(fd, fuck);
	else if (ft_strsearch(line, "Cone") != -1)
		get_cone(fd, fuck);
	else if (ft_strsearch(line, "Cylinder") != -1)
		get_cylinder(fd, fuck);
	else if (ft_strsearch(line, "Cercle") != -1)
		get_cercle(fd, fuck);
	else if (ft_strsearch(line, "Triangle") != -1)
		get_triangle(fd, fuck);
}

t_shape	*parse(t_map *map, char *file)
{
	char	*line;
	int		ret;
	int		fd;
	t_parse fuck;

	init_parser_value(map, &fuck);
	map->spoti = 0;
	map->scene.nb_shape = get_nb_shape(file);
	map->scene.nb_spot = get_nb_spot(file);
	map->scene.nb_mat = get_nb_mat(file);
	map->scene.spot = (t_spot *)malloc(sizeof(t_spot) * map->scene.nb_spot);
	fuck.shape = (t_shape*)malloc(sizeof(t_shape) * map->scene.nb_shape);
	map->scene.mat = (t_mat*)malloc(sizeof(t_mat) * map->scene.nb_mat);
	if ((fd = open(file, O_RDONLY)) == -1)
		exit(0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		parsing(&fuck, map, line, fd);
		free(line);
	}
	if (ret == -1)
		printf("error ret -1\n");
	close(fd);
	return (fuck.shape);
}
