/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 16:16:11 by emontagn          #+#    #+#             */
/*   Updated: 2016/06/04 18:01:36 by emontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_window(int fd, t_map *map)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 4)
	{
		if ((j = ft_strsearch(line, "width: ")) != -1)
			map->width = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "height: ")) != -1)
			map->height = atoi(ft_strchr(line, ' ') + 1);
		free(line);
		i++;
	}
	if (ret == -1)
		exit(0);
}

void	get_multi_sampling(int fd, t_map *map)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 3)
	{
		if ((j = ft_strsearch(line, "power: ")) != -1)
			map->multi_sampling = atoi(ft_strchr(line, ' ') + 1);
		free(line);
		i++;
	}
	if (ret == -1)
		exit(0);
}

void	get_spotlight(int fd, t_map *map)
{
	int			i;
	int			j;
	int			ret;
	char		*line;
	t_spot		*spot;

	i = 0;
	spot = (t_spot *)malloc(sizeof(t_spot) * map->scene.nb_spot);
	while ((ret = get_next_line(fd, &line)) > 0 && i != 6)
	{
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			spot->pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			spot->color = get_rgb_int(line + j);
		else if ((j = ft_strsearch(line, "type: ")) != -1)
			spot->type = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "intensity: ")) != -1)
			spot->intensity = atoi_double(ft_strchr(line, ' ') + 1);
		/*
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			map->scene.spot->pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			map->scene.spot->color = get_rgb_int(line + j);
		else if ((j = ft_strsearch(line, "type: ")) != -1)
			map->scene.spot->type = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "intensity: ")) != -1)
			map->scene.spot->intensity = atoi_double(ft_strchr(line, ' ') + 1);
		*/
		free(line);
		i++;
	}
	if (ret == -1)
		printf("fuck\n");
	map->scene.spot = spot;
}
