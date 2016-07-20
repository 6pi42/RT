/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 17:16:50 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 17:18:53 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

int			get_rgb_int(char *line)
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
