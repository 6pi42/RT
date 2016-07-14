/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:52:38 by emontagn          #+#    #+#             */
/*   Updated: 2016/07/14 02:34:41 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_shape(t_parse *fuck)
{
	fuck->shape[fuck->nb].pos.x = 0;
	fuck->shape[fuck->nb].pos.y = 0;
	fuck->shape[fuck->nb].pos.z = 0;
	fuck->shape[fuck->nb].axis.x = 0;
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
}


void	get_plane(int fd, t_parse *fuck)
{
	short		j;
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strsearch(line, "}") == -1)
	{
		fuck->shape[fuck->nb].type.x = 2.0f;
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
			fuck->shape[fuck->nb].axe_decoupe = get_vector(ft_strchr(line, ' ') + 1);
		free(line);
	}
	if (ret == -1)
		exit(0);
	fuck->nb++;
}

void	get_sphere(int fd, t_parse *fuck)
{
	short		j;
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strsearch(line, "}") == -1)
	{
		fuck->shape[fuck->nb].type.x = 1.0f;
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
			fuck->shape[fuck->nb].axe_decoupe = get_vector(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "neg: ")) != -1)
			fuck->shape[fuck->nb].type.y = ft_atoi(ft_strchr(line, ' ') + 1);
		free(line);
	}
	if (ret == -1)
		exit(0);
	fuck->nb++;
}

void	get_ellipsoid(int fd, t_parse *fuck)
{
	short		j;
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strsearch(line, "}") == -1)
	{
		fuck->shape[fuck->nb].type.x = 5.0f;
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
			fuck->shape[fuck->nb].axe_decoupe = get_vector(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "neg: ")) != -1)
			fuck->shape[fuck->nb].type.y = ft_atoi(ft_strchr(line, ' ') + 1);
		free(line);
	}
	if (ret == -1)
		exit(0);
	fuck->nb++;
}

void	get_cone(int fd, t_parse *fuck)
{
	short		j;
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strsearch(line, "}") == -1)
	{
		fuck->shape[fuck->nb].type.x = 4.0f;
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
			fuck->shape[fuck->nb].axe_decoupe = get_vector(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "neg: ")) != -1)
			fuck->shape[fuck->nb].type.y = ft_atoi(ft_strchr(line, ' ') + 1);
		free(line);
	}
	if (ret == -1)
		exit(0);
	fuck->nb++;
}

void	get_cylinder(int fd, t_parse *fuck)
{
	short		j;
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strsearch(line, "}") == -1)
	{
		fuck->shape[fuck->nb].type.x = 3.0f;
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
			fuck->shape[fuck->nb].axe_decoupe = get_vector(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "neg: ")) != -1)
			fuck->shape[fuck->nb].type.y = ft_atoi(ft_strchr(line, ' ') + 1);
		free(line);
	}
	if (ret == -1)
		exit(0);
	fuck->nb++;
}

void	get_triangle(int fd, t_parse *fuck)
{
	short		j;
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strsearch(line, "}") == -1)
	{
		fuck->shape[fuck->nb].type.x = 8.0f;
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
		free(line);
	}
	if (ret == -1)
		printf("error tri\n");
	fuck->nb++;
}

void	get_cercle(int fd, t_parse *fuck)
{
	short		j;
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strsearch(line, "}") == -1)
	{
		fuck->shape[fuck->nb].type.x = 7.0f;
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
		free(line);
	}
	//printf("le cercle charger pos\npos: %f %f %f\nnor: %f %f %f\nrad: %f\nid: %d", fuck->shape[fuck->nb].pos.x, fuck->shape[fuck->nb].pos.y, fuck->shape[fuck->nb].pos.z, fuck->shape[fuck->nb].color.x, fuck->shape[fuck->nb].color.y, fuck->shape[fuck->nb].color.z, fuck->shape[fuck->nb].radius.x, fuck->shape[fuck->nb].mat_id);
	if (ret == -1)
		exit(0);
	fuck->nb++;
}

void	get_thorus(int fd, t_parse *fuck)
{
	short		j;
	short		ret;
	char		*line;

	init_shape(fuck);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strsearch(line, "}") == -1)
	{
		fuck->shape[fuck->nb].type.x = 6.0f;
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			fuck->shape[fuck->nb].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			fuck->shape[fuck->nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "dir: ")) != -1)
			fuck->shape[fuck->nb].axis = get_vector(line + j);
		else if ((j = ft_strsearch(line, "rad: ")) != -1)
			fuck->shape[fuck->nb].radius = get_radius2(line + j);
		else if ((j = ft_strsearch(line, "id: ")) != -1)
			fuck->shape[fuck->nb].mat_id = ft_atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "neg: ")) != -1)
			fuck->shape[fuck->nb].type.y = ft_atoi(ft_strchr(line, ' ') + 1);
		free(line);
	}
	if (ret == -1)
		exit(0);
	printf("THORUS\n");
	printf("pos: %.1f %.1f %.1f\n", fuck->shape[fuck->nb].pos.x, fuck->shape[fuck->nb].pos.y, fuck->shape[fuck->nb].pos.z);
	printf("dir: %.1f %.1f %.1f\n", fuck->shape[fuck->nb].axis.x, fuck->shape[fuck->nb].axis.y, fuck->shape[fuck->nb].axis.z);
	printf("rgb: %.0f %.0f %.0f\n", fuck->shape[fuck->nb].color.x, fuck->shape[fuck->nb].color.y, fuck->shape[fuck->nb].color.z);
	printf("rad: %.0f %.0f\n", fuck->shape[fuck->nb].radius.x,fuck->shape[fuck->nb].radius.y);
	fuck->nb++;
}
