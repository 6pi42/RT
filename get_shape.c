/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:52:38 by emontagn          #+#    #+#             */
/*   Updated: 2016/04/16 14:09:25 by emontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
static short nb;

void	get_plane(int fd, t_shape *shape)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 3)
	{
		shape[nb].type.x = 2;
		if ((j = ft_strsearch(line, "rgb:")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "nor:")) != -1)
			shape[nb].radius = get_vector(line + j);
		else
			printf("error\n");
		free(line);
		i++;
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}

void	get_sphere(int fd, t_shape *shape)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 3)
	{
		shape[nb].type.x = 1;
		if ((j = ft_strsearch(line, "rad: ")) != -1)
			shape[nb].radius = get_radius(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		else
			printf("error\n");
		free(line);
		i++;
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}

void	get_ellipsoid(int fd, t_shape *shape)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 4)
	{
		shape[nb].type.x = 5;
		if ((j = ft_strsearch(line, "rad: ")) != -1)
			shape[nb].radius = get_vector(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "dir: ")) != -1)
			shape[nb].axis = get_vector(line + j);
		else
			printf("error\n");
		free(line);
		i++;
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}

void	get_cone(int fd, t_shape *shape)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = -1;
	while ((ret = get_next_line(fd, &line)) > 0 && ++i != 4)
	{
		shape[nb].type.x = 4;
		if ((j = ft_strsearch(line, "agl: ")) != -1)
			shape[nb].radius = get_radius(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "dir: ")) != -1)
			shape[nb].axis = get_vector(line + j);
		else
			printf("error\n");
		free(line);
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}

void	get_cylinder(int fd, t_shape *shape)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = -1;
	while ((ret = get_next_line(fd, &line)) > 0 && ++i != 4)
	{
		shape[nb].type.x = 3;
		if ((j = ft_strsearch(line, "rad: ")) != -1)
			shape[nb].radius = get_radius(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			shape[nb].color = get_rgb(line + j);
		else if ((j = ft_strsearch(line, "pos: ")) != -1)
			shape[nb].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "dir: ")) != -1)
			shape[nb].axis = get_vector(line + j);
		else
			printf("error\n");
		free(line);
	}
	if (ret == -1)
		printf("error\n");
	nb++;
}
