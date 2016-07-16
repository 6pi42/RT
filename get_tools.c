/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:53:34 by emontagn          #+#    #+#             */
/*   Updated: 2016/07/16 11:23:11 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	get_position(char *line)
{
	char		**tab;
	cl_float4	pos;
	int			i;

	i = 0;
	while (line[i] == '\t')
		i++;
	tab = ft_strsplit(line + i, ' ');
	i = 0;
	while (tab[i])
		i++;
	if (i != 3)
		printf("error\n");
	pos.x = atoi_double(tab[0]);
	pos.y = atoi_double(tab[1]);
	pos.z = atoi_double(tab[2]);
	pos.w = 0.0f;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (pos);
}

cl_float4	get_vector(char *line)
{
	char		**tab;
	cl_float4	vector;
	int			i;

	i = 0;
	while (line[i] == '\t')
		i++;
	tab = ft_strsplit(line + i, ' ');
	i = 0;
	while (tab[i])
		i++;
	if (!(i == 3 || i == 4))
		printf("error\n");
	vector.x = atoi_double(tab[0]);
	vector.y = atoi_double(tab[1]);
	vector.z = atoi_double(tab[2]);
	if (i == 3)
		vector.w = 0.0f;
	else
		vector.w = atoi_double(tab[3]);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (vector);
}

cl_float4	get_radius(char *line)
{
	char		**tab;
	cl_float4	radius;
	int			i;

	i = 0;
	while (line[i] == '\t')
		i++;
	tab = ft_strsplit(line + i, ' ');
	i = 0;
	while (tab[i])
		i++;
	if (i != 1)
		printf("error\n");
	radius.x = atoi_double(tab[0]);
	radius.y = 0.0f;
	radius.z = 0.0f;
	radius.w = 0.0f;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (radius);
}

cl_float4	get_radius2(char *line)
{
	char		**tab;
	cl_float4	radius;
	int			i;

	i = 0;
	while (line[i] == '\t')
		i++;
	tab = ft_strsplit(line + i, ' ');
	i = 0;
	while (tab[i])
		i++;
	if (i != 2)
		printf("error\n");
	radius.x = atoi(tab[0]);
	radius.y = atoi(tab[1]);
	radius.z = 0.0f;
	radius.w = 0.0f;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (radius);
}

cl_float4	get_rgb(char *line)
{
	char		**tab;
	cl_float4	color;
	int			i;

	i = 0;
	while (line[i] == '\t')
		i++;
	tab = ft_strsplit(line + i, ' ');
	i = 0;
	while (tab[i])
		i++;
	if (i != 3)
		printf("error\n");
	color.x = atoi(tab[0]);
	color.y = atoi(tab[1]);
	color.z = atoi(tab[2]);
	color.w = 0.0f;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (color);
}

int		get_rgb_int(char *line)
{
	char		**tab;
	int			rgb;
	int			i;

	i = 0;
	while (line[i] == '\t')
		i++;
	tab = ft_strsplit(line + i, ' ');
	i = 0;
	while (tab[i])
		i++;
	if (i != 3)
		printf("error\n");
	rgb = 0;
	rgb += atoi(tab[0]) * 256 * 256;
	rgb += atoi(tab[1]) * 256;
	rgb += atoi(tab[2]);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (rgb);
}
