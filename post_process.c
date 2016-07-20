/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 14:54:44 by amathias          #+#    #+#             */
/*   Updated: 2016/07/18 14:37:31 by amathias         ###   ########.fr       */
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

int		sepia(int red, int green, int blue)
{
	int nred;
	int ngreen;
	int nblue;

	nred = (int)((red * 0.393f) + (green * 0.769f) + (blue * 0.189f));
	ngreen = (int)((red * 0.349f) + (green * 0.686f) + (blue * 0.168f));
	nblue = (int)((red * 0.272f) + (green * 0.534f) + (blue * 0.131f));
	nred = nred < 0x0 ? 0x0 : nred;
	ngreen = ngreen < 0x0 ? 0x0 : ngreen;
	nblue = nblue < 0x0 ? 0x0 : nblue;
	nred = nred > 0xFF ? 0xFF : nred;
	ngreen = ngreen > 0xFF ? 0xFF : ngreen;
	nblue = nblue > 0xFF ? 0xFF : nblue;
	return (nred << 16 | ngreen << 8 | nblue);
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
		c[i] = sepia(red, green, blue);
		i++;
	}
	return (c);
}
