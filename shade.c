/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:59:59 by amathias          #+#    #+#             */
/*   Updated: 2016/07/19 17:37:27 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		iter_spot(t_map *map, t_mat mat, t_utils utils, int color)
{
	int i;
	int c;
	int	*acolor;

	i = 0;
	acolor = (int*)malloc(sizeof(int) * map->scene.nb_spot);
	while (i < map->scene.nb_spot)
	{
		c = 0x00;
		if (utils.inter.id != -1)
		{
			mat = map->scene.mat[map->scene.shape[utils.inter.id].mat_id];
			map->current_spot = map->scene.spot[i];
			c = utils.shadow ? color_mul(get_color(map, mat, utils, color), 0.2)
				: get_color(map, mat, utils, color);
			utils.shadow = utils.shadow ? utils.shadow - 1 : utils.shadow;
		}
		acolor[i] = c;
		i++;
	}
	c = color_average(acolor, map->scene.nb_spot);
	free(acolor);
	return (c);
}

t_ray	*prep_ray_trans(t_map *map, t_inter *inter, int num_spot)
{
	t_ray	*ray;
	int		i;

	i = 0;
	if ((ray = (t_ray*)malloc(sizeof(t_ray) *
		(size_t)(map->height * map->width))) == NULL)
		return (NULL);
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1)
		{
			ray[i].origin = add_vec(add_vec(inter[i].from.origin, scale_vec(
			inter[i].dist, inter[i].from.ray)), scale_vec(0.001, sub_vec(
			map->scene.spot[num_spot].pos, add_vec(inter[i].from.origin,
			scale_vec(inter[i].dist, inter[i].from.ray)))));
			ray[i].ray = sub_vec(map->scene.spot[num_spot].pos, add_vec(
			inter[i].from.origin, scale_vec(inter[i].dist, inter[i].from.ray)));
			normalize_vec(&ray[i].ray);
		}
		i++;
	}
	return (ray);
}

int		*apply_trans(t_map *map, t_inter *inter, int *color)
{
	int		i;
	int		j;
	t_inter *tmp;
	t_ray	*ray;

	j = 0;
	while (j < map->scene.nb_spot)
	{
		if ((ray = prep_ray_trans(map, inter, j)) == NULL)
			return (color);
		tmp = get_inter(map, map->height * map->width, ray);
		i = 0;
		while (i < (int)(map->height * map->width))
		{
			if (inter[i].id != -1 && tmp[i].id != -1 &&
					inter[i].id != tmp[i].id)
				color[i] = get_trans_color(map, color[i], tmp[i]);
			i++;
		}
		free(tmp);
		free(ray);
		j++;
	}
	return (color);
}

int		process_shade(t_map *map, t_utils *utils)
{
	int	color;

	color = 0xFF;
	utils->inter.normal = get_bumped_normal(map, utils->inter,
		map->scene.shape[utils->inter.id],
		get_inter_pos(utils->inter.from, utils->inter));
	color = map->config.texture ? get_texture_color(map, utils->inter,
		map->scene.shape[utils->inter.id],
		get_inter_pos(utils->inter.from, utils->inter)) :
		color_from_float4(map->scene.shape[utils->inter.id].color);
	color = iter_spot(map, map->scene.mat[
		map->scene.shape[utils->inter.id].mat_id], *utils, color);
	return (color);
}

int		*shade(t_map *map, t_inter *inter)
{
	t_utils		utils;
	int			i;
	int			*color;

	color = (int*)malloc(sizeof(int) * (size_t)(map->height * map->width));
	i = -1;
	printf("coucou shade\n");
	while (i++ < (int)(map->height * map->width))
	{
		color[i] = 0x0;
		if (inter[i].id != -1)
		{
			utils.inter = inter[i];
			utils.ray = inter[i].from;
			utils.inter_pos = get_inter_pos(utils.ray, utils.inter);
			utils.shadow = 0;
			color[i] = process_shade(map, &utils);
		}
	}
	if (map->config.transparence)
		color = apply_trans(map, inter, color);
	return (color);
}
