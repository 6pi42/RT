/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/02 15:34:48 by amathias          #+#    #+#             */
/*   Updated: 2016/04/03 11:13:10 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_key(t_map *map)
{
	map->key.up = 0;
	map->key.down = 0;
	map->key.left = 0;
	map->key.right = 0;
	map->key.mleft = 0;
	map->key.mright = 0;
}

int		key_press(int keycode, t_map *map)
{
	if (keycode == 124)
		map->key.mleft = 1;
	if (keycode == 123)
		map->key.mright = 1;
	if (keycode == 13)
		map->key.up = 1;
	if (keycode == 1)
		map->key.down = 1;
	if (keycode == 0)
		map->key.right = 1;
	if (keycode == 2)
		map->key.left = 1;
	return (0);
}


int		loop_hook(t_map *map)
{
	move(map);
	return (0);
}

int		key_hook(int keycode, t_map *map)
{
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(0);
	}
	if (keycode == 124)
		map->key.mleft = 0;
	if (keycode == 123)
		map->key.mright = 0;
	if (keycode == 13)
		map->key.up = 0;
	if (keycode == 1)
		map->key.down = 0;
	if (keycode == 0)
		map->key.right = 0;
	if (keycode == 2)
		map->key.left = 0;
	return (0);
}
