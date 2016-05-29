/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 10:21:01 by amathias          #+#    #+#             */
/*   Updated: 2016/05/25 16:27:27 by amathias         ###   ########.fr       */
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
