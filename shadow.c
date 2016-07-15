/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:32:14 by amathias          #+#    #+#             */
/*   Updated: 2016/07/15 14:07:57 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	get_shadow_dir(cl_float4 inter_pos, t_spot spot)
{
	cl_float4	shadow_dir;

	shadow_dir.x = inter_pos.x - spot.pos.x;
	shadow_dir.y = inter_pos.y - spot.pos.y;
	shadow_dir.z = inter_pos.z - spot.pos.z;
	shadow_dir.w = 0.0f;
	normalize_vec(&shadow_dir);
	return (shadow_dir);
}

t_ray		*get_shadow_ray(t_map *map, t_spot spot, t_inter *inter)
{
	t_ray		*shadow;
	cl_float4	inter_pos;
	int			i;

	i = 0;
	shadow = (t_ray*)malloc(sizeof(t_ray) * (size_t)(map->height * map->width));
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1)
		{
			//printf("%f %f %f\n", spot.pos.x, spot.pos.y, spot.pos.z);
			shadow[i].origin.x = spot.pos.x;
			shadow[i].origin.y = spot.pos.y;
			shadow[i].origin.z = spot.pos.z;
			shadow[i].origin.w = 0.0f;

			inter_pos.x = (inter[i].from.origin.x + (inter[i].from.ray.x
						* inter[i].dist)) + (inter[i].from.ray.x * 0.01f);
			inter_pos.y = (inter[i].from.origin.y + (inter[i].from.ray.y
						* inter[i].dist)) + (inter[i].from.ray.y * 0.01f);
			inter_pos.z = (inter[i].from.origin.z + (inter[i].from.ray.z
						* inter[i].dist)) + (inter[i].from.ray.z * 0.01f);
			inter_pos.w = 0.0f;
			shadow[i].ray = get_shadow_dir(inter_pos, spot);
		}
		i++;
	}
	return (shadow);
}

int		*shadow(t_map *map, t_inter *inter)
{
	t_ray	*shadow;
	t_inter	*inter_shadow;
	int		*is_shadow;
	int		i;
	int		j;

	is_shadow = (int*)malloc(sizeof(int) * (size_t)(map->height * map->width));
	i = 0;
	while (i < map->scene.nb_spot)
	{
		j = 0;
		shadow = get_shadow_ray(map, map->scene.spot[i], inter);
		inter_shadow = get_inter(map, (size_t)map->height * map->width, shadow);
		while (j < (int)(map->height * map->width))
		{
			if (i == 0)
				is_shadow[j] = 0;
			if (inter_shadow[j].id != -1
					&& (inter[j].id != inter_shadow[j].id))
			{
				is_shadow[j]++; //need this to create different shade of shadow
			}
			j++;
		}
		i++;
	}
	return (is_shadow);
}
