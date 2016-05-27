/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:52:38 by emontagn          #+#    #+#             */
/*   Updated: 2016/05/27 16:42:13 by emontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
static short nb;

void	get_plane(int fd, t_shape *shape)
{
	short		i;
	short		j;
	short		ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 6)
	{
		shape[nb].type.x = 2.0f;
		if ((j = ft_strsearch(line, "tex: ")) != -1)
			shape[nb].type.y = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "nor: ")) != -1)
			shape[nb].radius = get_vector(line + j);
		free(line);
		i++;
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}

void	get_sphere(int fd, t_shape *shape)
{
	short		i;
	short		j;
	short		ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 6)
	{
		shape[nb].type.x = 1.0f;
		if ((j = ft_strsearch(line, "tex: ")) != -1)
			shape[nb].type.y = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "rad: ")) != -1)
			shape[nb].radius = get_radius(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		free(line);
		i++;
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}

void	get_ellipsoid(int fd, t_shape *shape)
{
	short		i;
	short		j;
	short		ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 6)
	{
		shape[nb].type.x = 5.0f;
		if ((j = ft_strsearch(line, "tex: ")) != -1)
			shape[nb].type.y = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "rad: ")) != -1)
			shape[nb].radius = get_vector(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		free(line);
		i++;
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}

void	get_cone(int fd, t_shape *shape)
{
	short		i;
	short		j;
	short		ret;
	char		*line;

	i = -1;
	while ((ret = get_next_line(fd, &line)) > 0 && ++i != 7)
	{
		shape[nb].type.x = 4.0f;
		if ((j = ft_strsearch(line, "tex: ")) != -1)
			shape[nb].type.y = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "agl: ")) != -1)
			shape[nb].radius = get_radius(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "dir: ")) != -1)
			shape[nb].axis = get_vector(line + j);
		free(line);
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}

void	get_cylinder(int fd, t_shape *shape)
{
	short		i;
	short		j;
	short		ret;
	char		*line;

	i = -1;
	while ((ret = get_next_line(fd, &line)) > 0 && ++i != 7)
	{
		shape[nb].type.x = 3.0f;
		if ((j = ft_strsearch(line, "tex: ")) != -1)
			shape[nb].type.y = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "rad: ")) != -1)
			shape[nb].radius = get_radius(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "dir: ")) != -1)
			shape[nb].axis = get_vector(line + j);
		free(line);
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}

void	get_triangle(int fd, t_shape *shape)
{
	short		i;
	short		j;
	short		ret;
	char		*line;

	i = -1;
	while ((ret = get_next_line(fd, &line)) > 0 && ++i != 6)
	{
		shape[nb].type.x = 8.0f;
		if ((j = ft_strsearch(line, "pt1: ")) != -1)
			shape[nb].radius = get_vector(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pt2: ")) != -1)
			shape[nb].pos = get_vector(line + j);
		else if ((j = ft_strsearch(line, "pt3: ")) != -1)
			shape[nb].axis = get_vector(line + j);
		free(line);
	}
	if (ret == -1)
		printf("error tri\n");
	nb++;
}

void	get_cube(int fd, t_shape *shape)
{
	short		i;
	short		j;
	short		ret;
	char		*line;

	i = -1;
	while ((ret = get_next_line(fd, &line)) > 0 && ++i != 5)
	{
		shape[nb].type.x = 6.0f;
		if ((j = ft_strsearch(line, "pt1: ")) != -1)
			shape[nb].pos = get_vector(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pt2: ")) != -1)
			shape[nb].radius = get_vector(line + j);
		free(line);
	}
	if (ret == -1)
		printf("error cune\n");
	nb++;
}


void	get_cercle(int fd, t_shape *shape)
{
	short		i;
	short		j;
	short		ret;
	char		*line;

	i = -1;
	while ((ret = get_next_line(fd, &line)) > 0 && ++i != 6)
	{
		shape[nb].type.x = 7.0f;
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "dir: ")) != -1)
			shape[nb].radius = get_vector(line + j);
		else if ((j = ft_strsearch(line, "rad: ")) != -1)
			shape[nb].axis = get_radius(line + j);
		free(line);
	}
	if (ret == -1)
		printf("error ewfw\n");
	nb++;
}
