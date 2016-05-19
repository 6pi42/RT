/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:32:14 by amathias          #+#    #+#             */
/*   Updated: 2016/05/19 15:10:32 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	get_shadow_dir(cl_float4 inter_pos, cl_float4 spot_pos)
{
	cl_float4	shadow_dir;

	shadow_dir.x = inter_pos.x - spot_pos.x;
	shadow_dir.y = inter_pos.y - spot_pos.y;
	shadow_dir.z = inter_pos.z - spot_pos.z;
	shadow_dir.w = 0.0f;
	normalize_vec(&shadow_dir);
	return (shadow_dir);
}

t_ray		*get_shadow_ray(t_map *map, cl_float4 spot_pos,
									t_ray *ray, t_inter *inter)
{
	t_ray		*shadow;
	int			i;
	
	i = 0;
	shadow = (t_ray*)malloc(sizeof(t_ray) * (size_t)(map->height * map->width));
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1)
		{
			shadow[i].origin.x = ray->origin.x + (ray->ray.x * inter[i].dist);
			shadow[i].origin.y = ray->origin.y + (ray->ray.y * inter[i].dist);
			shadow[i].origin.z = ray->origin.z + (ray->ray.z * inter[i].dist);
			shadow[i].origin.w = 0.0f;
			shadow[i].ray = get_shadow_dir(shadow[i].origin, spot_pos);
		}
		i++;
	}
	return (shadow);
}

int		*shadow(t_map *map, t_inter *inter, t_ray *primary)
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
		shadow = get_shadow_ray(map, map->scene.spot[i], primary, inter);
		inter_shadow = get_inter(map, (size_t)map->height * map->width, shadow);
		while (j < (int)(map->height * map->width))
		{
			if (i == 0)
				is_shadow[j] = 0;
			if (inter_shadow[j].id != -1
					&& (inter[j].id != inter_shadow[j].id))
				is_shadow[j]++; //need this to create different shade of shadow
			j++;
		}
		i++;
	}
	return (is_shadow);
}
