/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:52:38 by emontagn          #+#    #+#             */
/*   Updated: 2016/07/18 18:04:39 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_shape(t_parse *fuck)
{
	fuck->shape[fuck->nb].pos.x = 0;
	fuck->shape[fuck->nb].pos.y = 0;
	fuck->shape[fuck->nb].pos.z = 0;
	fuck->shape[fuck->nb].axis.x = 1;
	fuck->shape[fuck->nb].axis.y = 0;
	fuck->shape[fuck->nb].axis.z = 0;
	fuck->shape[fuck->nb].color.x = 255;
	fuck->shape[fuck->nb].color.y = 255;
	fuck->shape[fuck->nb].color.z = 255;
	fuck->shape[fuck->nb].type.y = 0;
	fuck->shape[fuck->nb].axe_decoupe.x = 0;
	fuck->shape[fuck->nb].axe_decoupe.y = 0;
	fuck->shape[fuck->nb].axe_decoupe.z = 0;
	fuck->shape[fuck->nb].axe_decoupe.w = 0;
	fuck->shape[fuck->nb].radius.x = 0;
	fuck->shape[fuck->nb].radius.y = 0;
	fuck->shape[fuck->nb].radius.z = 0;
	fuck->shape[fuck->nb].mat_id = 0;
}

void	iter_plane(t_parse *fuck, char *line)
{
	short j;

	if ((j = ft_strsearch(line, "tex: ")) != -1)
		fuck->shape[fuck->nb].type.y = atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "rgb: ")) != -1)
		fuck->shape[fuck->nb].color = get_rgb(line + j);
	else if ((j = ft_strsearch(line, "pos: ")) != -1)
		fuck->shape[fuck->nb].pos = get_position(line + j);
	else if ((j = ft_strsearch(line, "nor: ")) != -1)
		fuck->shape[fuck->nb].radius = get_vector(line + j);
	else if ((j = ft_strsearch(line, "id: ")) != -1)
		fuck->shape[fuck->nb].mat_id = ft_atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "decoupe: ")) != -1)
		fuck->shape[fuck->nb].axe_decoupe =
		get_vector(ft_strchr(line, ' ') + 1);
}

void	get_plane(int fd, t_parse *fuck)
{
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		fuck->shape[fuck->nb].type.x = 2.0f;
		iter_plane(fuck, line);
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

void	iter_sphere(t_parse *fuck, char *line)
{
	short j;

	if ((j = ft_strsearch(line, "tex: ")) != -1)
		fuck->shape[fuck->nb].type.y = atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "rad: ")) != -1)
		fuck->shape[fuck->nb].radius = get_radius(line + j);
	else if ((j = ft_strsearch(line, "rgb: ")) != -1)
		fuck->shape[fuck->nb].color = get_rgb(line + j);
	else if ((j = ft_strsearch(line, "pos: ")) != -1)
		fuck->shape[fuck->nb].pos = get_position(line + j);
	else if ((j = ft_strsearch(line, "id: ")) != -1)
		fuck->shape[fuck->nb].mat_id = ft_atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "decoupe: ")) != -1)
		fuck->shape[fuck->nb].axe_decoupe =
			get_vector(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "neg: ")) != -1)
		fuck->shape[fuck->nb].type.y = ft_atoi(ft_strchr(line, ' ') + 1);
}

void	get_sphere(int fd, t_parse *fuck)
{
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		fuck->shape[fuck->nb].type.x = 1.0f;
		iter_sphere(fuck, line);
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
