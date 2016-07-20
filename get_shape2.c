/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 17:31:15 by amathias          #+#    #+#             */
/*   Updated: 2016/07/18 18:02:23 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_cylinder(int fd, t_parse *fuck)
{
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		fuck->shape[fuck->nb].type.x = 3.0f;
		iter_cyl(fuck, line);
		if (ft_strsearch(line, "}") != -1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (ret == -1)
		exit(0);
	fuck->nb++;
}

void	iter_tri(t_parse *fuck, char *line)
{
	short j;

	if ((j = ft_strsearch(line, "pt1: ")) != -1)
		fuck->shape[fuck->nb].radius = get_vector(line + j);
	else if ((j = ft_strsearch(line, "rgb: ")) != -1)
		fuck->shape[fuck->nb].color = get_rgb(line + j);
	else if ((j = ft_strsearch(line, "pt2: ")) != -1)
		fuck->shape[fuck->nb].pos = get_vector(line + j);
	else if ((j = ft_strsearch(line, "pt3: ")) != -1)
		fuck->shape[fuck->nb].axis = get_vector(line + j);
	else if ((j = ft_strsearch(line, "id: ")) != -1)
		fuck->shape[fuck->nb].mat_id = ft_atoi(ft_strchr(line, ' ') + 1);
}

void	get_triangle(int fd, t_parse *fuck)
{
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		fuck->shape[fuck->nb].type.x = 8.0f;
		iter_tri(fuck, line);
		if (ft_strsearch(line, "}") != -1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (ret == -1)
		printf("error tri\n");
	fuck->nb++;
}

void	iter_cercle(t_parse *fuck, char *line)
{
	short j;

	if ((j = ft_strsearch(line, "pos: ")) != -1)
		fuck->shape[fuck->nb].pos = get_position(line + j);
	else if ((j = ft_strsearch(line, "rgb: ")) != -1)
		fuck->shape[fuck->nb].color = get_rgb(line + j);
	else if ((j = ft_strsearch(line, "nor: ")) != -1)
		fuck->shape[fuck->nb].axis = get_vector(line + j);
	else if ((j = ft_strsearch(line, "rad: ")) != -1)
		fuck->shape[fuck->nb].radius = get_radius(line + j);
	else if ((j = ft_strsearch(line, "id: ")) != -1)
		fuck->shape[fuck->nb].mat_id = ft_atoi(ft_strchr(line, ' ') + 1);
}

void	get_cercle(int fd, t_parse *fuck)
{
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		fuck->shape[fuck->nb].type.x = 7.0f;
		iter_cercle(fuck, line);
		if (ft_strsearch(line, "}") != -1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (ret == -1)
		exit(0);
	fuck->nb++;
}
