/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 10:21:01 by amathias          #+#    #+#             */
/*   Updated: 2016/07/12 12:00:47 by apaget           ###   ########.fr       */
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
	int tmp;

	tmp = 0;
	tmp = (int)color.z * 256 * 256;
	tmp += (int)color.y * 256;
	tmp += (int)color.z;
	return (tmp);
}
