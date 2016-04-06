/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/02 15:34:48 by amathias          #+#    #+#             */
/*   Updated: 2016/04/06 16:06:18 by amathias         ###   ########.fr       */
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
	map->key.mx = 0;
	map->key.my = 0;
	map->key.num_8 = 0;
	map->key.num_4 = 0;
	map->key.num_2 = 0;
	map->key.num_6 = 0;
	map->key.phi = 0.0;
	map->key.theta = 0.0;
}

int		motion_notify(int x, int y, t_map *map)
{
	if (x > 0 && y > 0 && x < map->height && y < map->width)
	{
		(void)map;
	}
	return (0);
}

int		key_press(int keycode, t_map *map)
{
	if (keycode == 126)
		map->key.mleft = 1;
	if (keycode == 125)
		map->key.mright = 1;
	if (keycode == 13)
		map->key.up = 1;
	if (keycode == 1)
		map->key.down = 1;
	if (keycode == 0)
		map->key.right = 1;
	if (keycode == 2)
		map->key.left = 1;
	if (keycode == 91)
		map->key.num_8 = 1;
	if (keycode == 86)
		map->key.num_4 = 1;
	if (keycode == 84)
		map->key.num_2 = 1;
	if (keycode == 88)
		map->key.num_6 = 1;

	return (0);
}


int		loop_hook(t_map *map)
{
	move(map);
	rotate(map);
	return (0);
}

int		key_hook(int keycode, t_map *map)
{
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(0);
	}
	if (keycode == 126)
		map->key.mleft = 0;
	if (keycode == 125)
		map->key.mright = 0;
	if (keycode == 13)
		map->key.up = 0;
	if (keycode == 1)
		map->key.down = 0;
	if (keycode == 0)
		map->key.right = 0;
	if (keycode == 2)
		map->key.left = 0;
	if (keycode == 91)
		map->key.num_8 = 0;
	if (keycode == 86)
		map->key.num_4 = 0;
	if (keycode == 84)
		map->key.num_2 = 0;
	if (keycode == 88)
		map->key.num_6 = 0;

	return (0);
}
