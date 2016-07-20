/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 17:32:24 by amathias          #+#    #+#             */
/*   Updated: 2016/07/19 14:39:39 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	iter_elli(t_parse *fuck, char *line)
{
	short j;

	if ((j = ft_strsearch(line, "tex: ")) != -1)
		fuck->shape[fuck->nb].type.y = atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "rad: ")) != -1)
		fuck->shape[fuck->nb].radius = get_vector(line + j);
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

void	get_ellipsoid(int fd, t_parse *fuck)
{
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		fuck->shape[fuck->nb].type.x = 5.0f;
		iter_elli(fuck, line);
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

void	iter_cone(t_parse *fuck, char *line)
{
	short j;

	if ((j = ft_strsearch(line, "tex: ")) != -1)
		fuck->shape[fuck->nb].type.y = atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "agl: ")) != -1)
		fuck->shape[fuck->nb].radius = get_radius(line + j);
	else if ((j = ft_strsearch(line, "rgb: ")) != -1)
		fuck->shape[fuck->nb].color = get_rgb(line + j);
	else if ((j = ft_strsearch(line, "pos: ")) != -1)
		fuck->shape[fuck->nb].pos = get_position(line + j);
	else if ((j = ft_strsearch(line, "dir: ")) != -1)
		fuck->shape[fuck->nb].axis = get_vector(line + j);
	else if ((j = ft_strsearch(line, "id: ")) != -1)
		fuck->shape[fuck->nb].mat_id = ft_atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "decoupe: ")) != -1)
		fuck->shape[fuck->nb].axe_decoupe =
			get_vector(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "neg: ")) != -1)
		fuck->shape[fuck->nb].type.y = ft_atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "size: ")) != -1)
		fuck->shape[fuck->nb].type.w = ft_atoi(ft_strchr(line, ' ') + 1);
}

void	get_cone(int fd, t_parse *fuck)
{
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		fuck->shape[fuck->nb].type.x = 4.0f;
		iter_cone(fuck, line);
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

void	iter_cyl(t_parse *fuck, char *line)
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
	else if ((j = ft_strsearch(line, "dir: ")) != -1)
		fuck->shape[fuck->nb].axis = get_vector(line + j);
	else if ((j = ft_strsearch(line, "id: ")) != -1)
		fuck->shape[fuck->nb].mat_id = ft_atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "decoupe: ")) != -1)
		fuck->shape[fuck->nb].axe_decoupe =
			get_vector(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "neg: ")) != -1)
		fuck->shape[fuck->nb].type.y = ft_atoi(ft_strchr(line, ' ') + 1);
	else if ((j = ft_strsearch(line, "size: ")) != -1)
		fuck->shape[fuck->nb].type.w = ft_atoi(ft_strchr(line, ' ') + 1);
}
