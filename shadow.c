/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:32:14 by amathias          #+#    #+#             */
/*   Updated: 2016/07/17 10:41:54 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	get_shadow_dir(t_inter inter, t_spot spot)
{
	cl_float4	shadow_dir;
	cl_float4	inter_pos;

	inter_pos.x = (inter.from.origin.x + (inter.from.ray.x
						* inter.dist)) + (inter.from.ray.x * 0.01f);
	inter_pos.y = (inter.from.origin.y + (inter.from.ray.y
						* inter.dist)) + (inter.from.ray.y * 0.01f);
	inter_pos.z = (inter.from.origin.z + (inter.from.ray.z
						* inter.dist)) + (inter.from.ray.z * 0.01f);
	shadow_dir.x = inter_pos.x - spot.pos.x;
	shadow_dir.y = inter_pos.y - spot.pos.y;
	shadow_dir.z = inter_pos.z - spot.pos.z;
	shadow_dir.w = 0.0f;
	normalize_vec(&shadow_dir);
	return (shadow_dir);
}

t_inter		*get_shadow_inter(t_map *map, t_spot spot, t_inter *inter)
{
	t_ray		*shadow;
	t_inter		*inter_shadow;
	int			i;

	i = 0;
	shadow = (t_ray*)malloc(sizeof(t_ray) * (size_t)(map->height * map->width));
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1)
		{
			shadow[i].origin.x = spot.pos.x;
			shadow[i].origin.y = spot.pos.y;
			shadow[i].origin.z = spot.pos.z;
			shadow[i].origin.w = 0.0f;
			shadow[i].ray = get_shadow_dir(inter[i], spot);
		}
		i++;
	}
	inter_shadow = get_inter(map, (size_t)map->height * map->width, shadow);
	free(shadow);
	return (inter_shadow);
}

int			*shadow(t_map *map, t_inter *inter)
{
	t_inter	*inter_shadow;
	int		*is_shadow;
	int		i;
	int		j;

	is_shadow = (int*)malloc(sizeof(int) * (size_t)(map->height * map->width));
	i = 0;
	while (i < map->scene.nb_spot)
	{
		j = 0;
		inter_shadow = get_shadow_inter(map, map->scene.spot[i], inter);
		while (j < (int)(map->height * map->width))
		{
			if (i == 0)
				is_shadow[j] = 0;
			if (inter_shadow[j].id != -1 && (inter[j].id != inter_shadow[j].id))
				is_shadow[j]++;
			j++;
		}
		i++;
		free(inter_shadow);
	}
	return (is_shadow);
}
