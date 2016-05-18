/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 16:16:11 by emontagn          #+#    #+#             */
/*   Updated: 2016/05/15 15:07:14 by emontagn         ###   ########.fr       */
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
	while ((ret = get_next_line(fd, &line)) > 0 && i != 2)
	{
		if ((j = ft_strsearch(line, "width: ")) != -1)
			map->width = atoi_double(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "height: ")) != -1)
			map->height = atoi_double(ft_strchr(line, ' ') + 1);
		else
			printf("error win\n");
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
	while ((ret = get_next_line(fd, &line)) > 0 && i != 1)
	{
		if ((j = ft_strsearch(line, "power: ")) != -1)
			map->multi_sampling = ft_atoi(ft_strchr(line, ' ') + 1);
		else
			printf("error sample\n");
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
	while ((ret = get_next_line(fd, &line)) > 0 && i != 1)
	{
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			map->spot = get_position(line + j);
		else
			printf("error sample\n");
		free(line);
		i++;
	}
	if (ret == -1)
		printf("error sample\n");
}
