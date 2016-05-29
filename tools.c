/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 07:31:45 by apaget            #+#    #+#             */
/*   Updated: 2016/05/26 18:28:31 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void	vec_normalize(cl_float4 *vec)
{
	float tmp;

	tmp = 1.0f / sqrt((vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
	vec->x *= tmp;
	vec->y *= tmp;
	vec->z *= tmp;
}

void	init_cam2(t_map *map)
{
	map->free_cam.pos.x = 50;
	map->free_cam.pos.y = 50;
	map->free_cam.pos.z = 50;
	map->free_cam.dir.x = 1;
	map->free_cam.dir.y = 0;
	map->free_cam.dir.z = 0;
	map->free_cam.phi = 60;
	map->free_cam.theta = 90;
	vector_from_angle(&map->free_cam);
}

void	init_cam(t_map *map)
{
	cl_float4 tmp;

	tmp.x = 0;
	tmp.y = 1;
	tmp.z = 0;
	map->free_cam.aspect_ratio = map->width / map->height;
	normalize_vec(&map->free_cam.dir);
	map->free_cam.left = cross_vec(tmp, map->free_cam.dir);
	normalize_vec(&map->free_cam.left);
	map->free_cam.down = cross_vec(map->free_cam.dir, map->free_cam.left);
}


