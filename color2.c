/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 10:24:15 by amathias          #+#    #+#             */
/*   Updated: 2016/07/18 14:19:27 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		caverage(int *n, int len)
{
	int nb;
	int i;

	if (len == 0)
		return (0);
	i = 0;
	nb = 0;
	while (i < len)
	{
		nb += n[i];
		i++;
	}
	nb /= i;
	return (nb);
}

int		color_average(int *rgb, int len)
{
	int	red[len];
	int	green[len];
	int	blue[len];
	int	i;

	i = 0;
	while (i < len)
	{
		red[i] = (rgb[i] & 0xFF0000) >> 16;
		green[i] = (rgb[i] & 0xFF00) >> 8;
		blue[i] = rgb[i] & 0xFF;
		i++;
	}
	red[0] = caverage(red, len);
	blue[0] = caverage(blue, len);
	green[0] = caverage(green, len);
	red[0] = red[0] > 0xFF ? 0xFF : red[0];
	blue[0] = blue[0] > 0xFF ? 0xFF : blue[0];
	green[0] = green[0] > 0xFF ? 0xFF : green[0];
	return (red[0] << 16 | green[0] << 8 | blue[0]);
}

void	color_average_array(t_map *map, int *acolor, int *acolor2)
{
	int i;
	int	*tmp;

	if (!acolor2)
		return ;
	i = 0;
	tmp = (int*)malloc(sizeof(int) * 2);
	while (i < (int)(map->height * map->width))
	{
		tmp[0] = acolor[i];
		tmp[1] = acolor2[i];
		acolor[i] = color_average(tmp, 2);
		i++;
	}
	free(tmp);
	free(acolor2);
}
