/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_perlin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 14:29:01 by apaget            #+#    #+#             */
/*   Updated: 2016/06/30 15:00:33 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int *get_normal_perlin(int *tex, int height, int width)
{
	int x;
	int y;
	int i;
	int *normal;

	if ((normal = (int*)malloc(sizeof(int) * height * width)) == NULL)
		return (NULL);
	i = 0;
	while (i < height * width)
	{
		x = i % width;
		y = i / width;
		normal = 0;
		normal |= tex[y * width + x] - tex[y * width + x + 1] << 16;
		normal |= tex[(y + 1) * width + x] - tex[y * width + x] << 8;
		normal |= 255;
		i++;
	}
	return (normal);
}
