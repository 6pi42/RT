/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 11:04:26 by amathias          #+#    #+#             */
/*   Updated: 2016/04/03 17:57:13 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate(t_map *map)
{
	(void)map;
}

void	move(t_map *map)
{
	int a;

	a = 0;
	if (map->key.up == 1)
	{
		map->scene.cam->origin.y += 2.0;
		a = 1;
	}
	if (map->key.down == 1)
	{
		map->scene.cam->origin.y -= 2.0;
		a = 1;
	}
	if (map->key.right == 1)
	{
		map->scene.cam->origin.x -= 2.0;
		a = 1;
	}
	if (map->key.left == 1)
	{
		map->scene.cam->origin.x += 2.0;
		a = 1;
	}
	if (map->key.mleft == 1)
	{
		map->scene.cam->origin.z -= 2.0;
		a = 1;
	}
	if (map->key.mright == 1)
	{
		map->scene.cam->origin.z += 2.0;
		a = 1;
	}
	
	if (a)
		draw(map);
}
