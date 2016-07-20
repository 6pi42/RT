/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 14:20:53 by amathias          #+#    #+#             */
/*   Updated: 2016/07/18 19:36:09 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		color_add4(int c1, int c2, int c3, int c4)
{
	int	red;
	int green;
	int blue;

	red = (((c1 & 0xFF0000) >> 16)
			+ ((c2 & 0xFF0000) >> 16)
			+ ((c3 & 0xFF0000) >> 16)
			+ ((c4 & 0xFF0000) >> 16));
	green = (((c1 & 0xFF00) >> 8)
			+ ((c2 & 0xFF00) >> 8)
			+ ((c3 & 0xFF00) >> 8)
			+ ((c4 & 0xFF00) >> 8));
	blue = ((c1 & 0xFF)
			+ (c2 & 0xFF)
			+ (c3 & 0xFF)
			+ (c4 & 0xFF));
	red = red > 0xFF ? 0xFF : red;
	green = green > 0xFF ? 0xFF : green;
	blue = blue > 0xFF ? 0xFF : blue;
	return (red << 16 | green << 8 | blue);
}

int		bilinear_filtering(t_tex *tex, float x, float y)
{
	t_bil	bil;
	float	fx;
	float	fy;
	int		color;

	fx = (x + 1000.5f) * (float)tex->w;
	fy = (y + 1000.5f) * (float)tex->w;
	bil.x1 = ((int)fx) % tex->w;
	bil.y1 = ((int)fy) % tex->h;
	bil.x2 = (bil.x1 + 1) % tex->w;
	bil.y2 = (bil.y1 + 1) % tex->h;
	bil.fractx = fx - floor(fx);
	bil.fracty = fy - floor(fy);
	color = color_add4(color_mul(tex->buffer[bil.x1 + bil.y1 * tex->w],
				(1.0f - bil.fractx) * (1.0f - bil.fracty)),
			color_mul(tex->buffer[bil.x2 + bil.y1 * tex->w],
				bil.fractx * (1.0f - bil.fracty)),
			color_mul(tex->buffer[bil.x1 + bil.y2 * tex->w],
				(1.0f - bil.fractx) * bil.fracty),
			color_mul(tex->buffer[bil.x2 + bil.y2 * tex->w],
				bil.fractx * bil.fracty));
	return (color);
}
