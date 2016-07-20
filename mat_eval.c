/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:39 by amathias          #+#    #+#             */
/*   Updated: 2016/07/19 17:41:28 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	*get_secondaries(t_map *map, t_inter *inter, t_ray *ray, int type)
{
	t_ray	*secondaries;
	int		i;

	(void)ray;
	secondaries = (t_ray*)malloc(sizeof(t_ray) * (size_t)(map->height
				* map->width));
	ft_memset(secondaries, 0, sizeof(t_ray) * (size_t)(map->height *
				map->width));
	i = 0;
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1)
		{
			if (type == 1)
				secondaries[i] = get_refract_ray(inter[i], inter[i].from,
				map->scene.mat[map->scene.shape[inter[i].id].mat_id].indice);
			else
				secondaries[i] = get_reflec_ray(inter[i], inter[i].from);
		}
		i++;
	}
	return (secondaries);
}

int		*end_recursion(t_map *map, int *reflec, int *refract, t_inter *inter)
{
	t_mat	mat;
	int		i;
	int		*c;

	i = -1;
	c = shade(map, inter);
	while (++i < map->height * map->width)
	{
		if (inter[i].id != -1)
		{
			mat = map->scene.mat[map->scene.shape[inter[i].id].mat_id];
			if (reflec != NULL && refract == NULL)
				c[i] = color_add(c[i], color_mul(reflec[i], mat.kreflec));
			else if (reflec == NULL && refract != NULL)
				c[i] = color_add(c[i], color_mul(refract[i], mat.krefrac));
			else if (reflec != NULL && refract != NULL)
				c[i] = color_add(color_add(c[i], color_mul(reflec[i],
					mat.kreflec)), color_mul(refract[i], mat.krefrac));
		}
	}
	if (reflec)
		free(reflec);
	if (refract)
		free(refract);
	return (c);
}

int		*get_refract_color(t_map *map, t_inter *inter, int *color, int depth)
{
	t_ray	*tmp;
	t_inter	*tmp_inter;
	int		*ret_refrac;

	tmp = get_secondaries(map, inter, &inter->from, 0);
	tmp_inter = get_inter(map, (size_t)map->height * map->width, tmp);
	ret_refrac = get_color2(map, tmp_inter, color, depth - 1);
	free(tmp_inter);
	free(tmp);
	return (ret_refrac);
}

int		*get_reflect_color(t_map *map, t_inter *inter, int *color, int depth)
{
	t_ray	*tmp;
	t_inter	*tmp_inter;
	int		*ret_reflec;

	tmp = get_secondaries(map, inter, &inter->from, 1);
	tmp_inter = get_inter(map, (size_t)map->height * map->width, tmp);
	ret_reflec = get_color2(map, tmp_inter, color, depth - 1);
	free(tmp);
	free(tmp_inter);
	return (ret_reflec);
}

int		*get_color2(t_map *map, t_inter *inter, int *color, int depth)
{
	int		*ret;
	int		*ret_refrac;
	int		*ret_reflec;

	ret_refrac = NULL;
	ret_reflec = NULL;
	printf("coucou get color 2 with depth : %d\n", depth);
	if (depth < 1 || (!map->config.reflection && !map->config.refraction))
		ret = shade(map, inter);
	else
	{
		if (map->config.reflection)
			ret_refrac = get_refract_color(map, inter, color, depth);
		if (map->config.refraction)
			ret_reflec = get_reflect_color(map, inter, color, depth);
		ret = end_recursion(map, ret_refrac, ret_reflec, inter);
	}
	if (map->config.filtre_s)
		ret = post_sepia(map, ret);
	if (map->config.filtre_n)
		ret = post_greyshade(map, ret);
	return (ret);
}
