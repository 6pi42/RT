/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 16:16:11 by emontagn          #+#    #+#             */
/*   Updated: 2016/07/18 18:41:54 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_window(int fd, t_map *map)
{
	int			j;
	int			ret;
	char		*line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((j = ft_strsearch(line, "width: ")) != -1)
			map->width = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "height: ")) != -1)
			map->height = atoi(ft_strchr(line, ' ') + 1);
		if (ft_strsearch(line, "}") != -1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (ret == -1)
		exit(0);
}

void	get_camera(int fd, t_map *map)
{
	int			j;
	int			ret;
	char		*line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			map->free_cam.pos = get_position(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "phi: ")) != -1)
			map->free_cam.phi = atof(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "theta: ")) != -1)
			map->free_cam.phi = atof(ft_strchr(line, ' ') + 1);
		if (ft_strsearch(line, "}") != -1)
		{
			free(line);
			vector_from_angle(&map->free_cam);
			break ;
		}
		free(line);
	}
	if (ret == -1)
		exit(0);
}

void	get_multi_sampling(int fd, t_map *map)
{
	int			j;
	int			ret;
	char		*line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((j = ft_strsearch(line, "power: ")) != -1)
			map->multi_sampling = atoi(ft_strchr(line, ' ') + 1);
		if (ft_strsearch(line, "}") != -1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (ret == -1)
		exit(0);
}

void	get_spotlight(int fd, t_map *map)
{
	int			j;
	int			ret;
	char		*line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			map->scene.spot[map->spoti].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			map->scene.spot[map->spoti].color = get_rgb_int(line + j);
		else if ((j = ft_strsearch(line, "type: ")) != -1)
			map->scene.spot[map->spoti].type = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "intensity: ")) != -1)
			map->scene.spot[map->spoti].intensity =
				atof(ft_strchr(line, ' ') + 1);
		if (ft_strsearch(line, "}") != -1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (ret == -1)
		printf("error spot\n");
	map->spoti++;
}

void	get_material(int fd, t_parse *fuck)
{
	int			j;
	int			ret;
	char		*line;
	t_mat		*mat;

	mat = fuck->map->scene.mat;
	init_material_value(mat, fuck);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((j = ft_strsearch(line, "tex: ")) != -1)
			get_tex(mat, line, fuck);
		else if ((j = ft_strsearch(line, "bump: ")) != -1)
			get_bump(mat, line, fuck);
		get_value_parse(mat, line, fuck);
		if (ft_strsearch(line, "}") != -1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	fuck->nb_mat++;
	if (ret == -1)
		exit(0);
}
