/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 16:16:11 by emontagn          #+#    #+#             */
/*   Updated: 2016/05/27 16:41:29 by emontagn         ###   ########.fr       */
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
		printf("error win\n");
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
		printf("error sample\n");
}

void	get_spotlight(int fd, t_map *map)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 3)
	{
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			map->spot = get_position(line + j);
		free(line);
		i++;
	}
	if (ret == -1)
		printf("error sample\n");
}
