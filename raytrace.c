/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:29:58 by amathias          #+#    #+#             */
/*   Updated: 2016/05/19 15:10:36 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	raytrace(t_map *map)
{
	t_ray	*primary;
	t_inter	*inter;
	cl_float4	black;
	int		*is_shadow;
	int		i;

	primary = get_primary(map);
	inter = get_inter(map, (size_t)(map->height * map->width), primary);
	is_shadow = shadow(map, inter, primary);
	i = 0;
	black.x = 0.0f;
	black.y = 0.0f;
	black.z = 0.0f;
	while (i < (int)map->width * (int)map->height)
	{
		if (inter[i].id != -1)
		{
			if (is_shadow[i] > 0)
				draw_pixel_to_image(map, i % (int)map->width,
					i / (int)map->width, black);
			else
				draw_pixel_to_image(map, i % (int)map->width,
					i / (int)map->width, map->scene.shape[inter[i].id].color);
		}
		else
			draw_pixel_to_image(map, i % (int)map->width, i / (int)map->width,
				black);

		i++;
	}
	free(primary);
	free(inter);
	free(is_shadow);
	
}
