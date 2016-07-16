/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 14:54:44 by amathias          #+#    #+#             */
/*   Updated: 2016/07/16 16:01:40 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		*post_greyshade(t_map *map, int *color)
{
	int i;
	int	tmp;

	i = 0;
	while (i < (int)map->width * map->height)
	{
		tmp = (((color[i] & 0xFF0000) >> 16)
			+ ((color[i] & 0xFF00) >> 8)
			+ (color[i] & 0xFF)) / 3;
		color[i] = (tmp << 16 | tmp << 8 | tmp);
		i++;
	}
	return (color);
}

int		*post_sepia(t_map *map, int *c)
{
	int i;
	int	red;
	int green;
	int blue;

	i = 0;
	while (i < (int)map->width * map->height)
	{
		red = ((c[i] & 0xFF0000) >> 16);
		green = ((c[i] & 0xFF00) >> 8);
		blue = (c[i] & 0xFF);
		c[i] = ((int)((red * 0.393f) + (green * 0.769f) + (blue * 0.189f)) << 16
			| (int)((red * 0.349f) + (green * 0.686f) + (blue * 0.168f)) << 8
			| (int)((red * 0.272f) + (green * 0.534f) + (blue * 0.131f)));
		i++;
	}
	return (c);
}
