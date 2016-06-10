/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_primary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 10:57:13 by amathias          #+#    #+#             */
/*   Updated: 2016/06/10 02:45:50 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	get_dir(t_map *map, float x, float y)
{
	cl_float4	dir;
	cl_float4	vp_right;
	cl_float4	vp_down;
	cl_float	xamnt;
	cl_float	yamnt;

	xamnt = ((x + 0.5f) / map->width) * map->scene.cam->ratio
				- (((map->width - map->height) / map->height) / 2.0f);
	yamnt = ((map->height - y) + 0.5f) / map->height;
	vp_down.x = (yamnt - 0.5f) * map->scene.cam->down.x;
	vp_down.y = (yamnt - 0.5f) * map->scene.cam->down.y;
	vp_down.z = (yamnt - 0.5f) * map->scene.cam->down.z;
	vp_right.x = (xamnt - 0.5f) * map->scene.cam->right.x;
	vp_right.y = (xamnt - 0.5f) * map->scene.cam->right.y;
	vp_right.z = (xamnt - 0.5f) * map->scene.cam->right.z;
	dir.x = (vp_right.x + vp_down.x) + map->scene.cam->ray.x;
	dir.y = (vp_right.y + vp_down.y) + map->scene.cam->ray.y;
	dir.z = (vp_right.z + vp_down.z) + map->scene.cam->ray.z;
	normalize_vec(&dir);
	return (dir);
}

t_ray		*get_primary(t_map *map)
{
	t_ray	*ray;
	int		x;
	int		y;
	int		i;

	ray = (t_ray*)malloc(sizeof(t_ray) * (size_t)(map->height * map->width));
	y = 0;
	i = 0;
	while (y < (int)map->height)
	{
		x = 0;
		while (x < (int)map->width)
		{
			ray[i].origin = map->scene.cam->origin;
			ray[i].ray = get_dir(map, (float)x, (float)y);
			i++;
			x++;
		}
		y++;
	}
	return (ray);
}
