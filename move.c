/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 11:04:26 by amathias          #+#    #+#             */
/*   Updated: 2016/04/03 11:28:15 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move(t_map *map)
{
	if (map->key.up == 1)
	{
		map->scene.sphere->pos.y += 2.0;
		draw(map);
	}
	if (map->key.down == 1)
	{
		map->scene.sphere->pos.y -= 2.0;
		draw(map);
	}
	if (map->key.right == 1)
	{
		map->scene.sphere->pos.x -= 2.0;
		draw(map);
	}
	if (map->key.left == 1)
	{
		map->scene.sphere->pos.x += 2.0;
		draw(map);
	}
}
