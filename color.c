/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 10:21:01 by amathias          #+#    #+#             */
/*   Updated: 2016/07/16 16:43:00 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		color_mul(int color, float coef)
{
	int red;
	int green;
	int blue;

	red = ((color & 0xFF0000) >> 16) * coef;
	green = ((color & 0xFF00) >> 8) * coef;
	blue = (color & 0xFF) * coef;
	red = red > 0xFF ? 0xFF : red;
	green = green > 0xFF ? 0xFF : green;
	blue = blue > 0xFF ? 0xFF : blue;
	return (red << 16 | green << 8 | blue);
}

int		color_sub(int c1, int c2)
{
	int	red;
	int green;
	int blue;

	red = (((c1 & 0xFF0000) >> 16) - ((c2 & 0xFF0000) >> 16));
	green = (((c1 & 0xFF00) >> 8) - ((c2 & 0xFF00) >> 8));
	blue = ((c1 & 0xFF) - (c2 & 0xFF));
	red = red < 0x0 ? 0x0 : red;
	green = green < 0x0 ? 0x0 : green;
	blue = blue < 0x0 ? 0x0 : blue;
	return (red << 16 | green << 8 | blue);
}

int		color_add(int c1, int c2)
{
	int	red;
	int green;
	int blue;

	red = (((c1 & 0xFF0000) >> 16) + ((c2 & 0xFF0000) >> 16));
	green = (((c1 & 0xFF00) >> 8) + ((c2 & 0xFF00) >> 8));
	blue = ((c1 & 0xFF) + (c2 & 0xFF));
	red = red > 0xFF ? 0xFF : red;
	green = green > 0xFF ? 0xFF : green;
	blue = blue > 0xFF ? 0xFF : blue;
	return (red << 16 | green << 8 | blue);
}

int		color_from_float4(cl_float4 color)
{
	return ((int)color.x << 16 | (int)color.y << 8 | (int)color.z);
}

static int	caverage(int *n, int len)
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

int			color_average(int *rgb, int len)
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

