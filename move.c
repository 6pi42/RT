/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 11:04:26 by amathias          #+#    #+#             */
/*   Updated: 2016/04/03 17:16:03 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate(t_map *map)
{

}

void	move(t_map *map)
{
	int a;

	a = 0;
	if (map->key.up == 1)
	{
		map->scene.sphere->pos.y += 2.0;
		a = 1;
	}
	if (map->key.down == 1)
	{
		map->scene.sphere->pos.y -= 2.0;
		a = 1;
	}
	if (map->key.right == 1)
	{
		map->scene.sphere->pos.x -= 2.0;
		a = 1;
	}
	if (map->key.left == 1)
	{
		map->scene.sphere->pos.x += 2.0;
		a = 1;
	}
	if (map->key.mleft == 1)
	{
		map->scene.sphere->pos.z -= 2.0;
		a = 1;
	}
	if (map->key.mright == 1)
	{
		map->scene.sphere->pos.z += 2.0;
		a = 1;
	}
	if (a)
		draw(map);
}
