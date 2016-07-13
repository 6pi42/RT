/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:39 by amathias          #+#    #+#             */
/*   Updated: 2016/07/13 08:49:49 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	get_refract_ray(t_inter inter, t_ray ray, double indice)
{
	t_ray	refract;
	double	n;
	double	c1;
	double	c2;

	//if (inter.in_shape)
		n = indice / 1;
//else
//		n = 1 / indice;
	refract.ray.x = 0;
	refract.ray.y = 0;
	refract.ray.z = 0;
	c1 = -docl_float4(inter.normal, ray.ray);
	c2 = sqrt(1 - n * (1 - c1 * c1));
	//if ((n * n * (1 - c1 * c1)) > 1.0f)
	//	return (refract);
	refract.ray = add_vec(scale_vec(n, ray.ray), scale_vec(n * c1 - c2,
																inter.normal));
	refract.origin = add_vec(ray.origin, scale_vec(inter.dist + 0.05, ray.ray));
	normalize_vec(&refract.ray);
	return (refract);
}

t_ray	get_reflec_ray(t_inter inter, t_ray ray)
{
	t_ray		reflec;
	cl_float4	inter_pos;

	inter_pos.x = ray.origin.x + ray.ray.x * (inter.dist - 0.05);
	inter_pos.y = ray.origin.y + ray.ray.y * (inter.dist - 0.05);
	inter_pos.z = ray.origin.z + ray.ray.z * (inter.dist - 0.05);
	reflec.ray.x = ray.ray.x - 2.0f * inter.normal.x
		* docl_float4(ray.ray, inter.normal);
	reflec.ray.y = ray.ray.y - 2.0f * inter.normal.y
		* docl_float4(ray.ray, inter.normal);
	reflec.ray.z = ray.ray.z - 2.0f * inter.normal.z
		* docl_float4(ray.ray, inter.normal);
	normalize_vec(&reflec.ray);
	reflec.origin.x = inter_pos.x ;
	reflec.origin.y = inter_pos.y ;
	reflec.origin.z = inter_pos.z ;
	return (reflec);
}

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
	t_mat mat;
	int i;
	int	*color;

	i = 0;
	color = shade(map, inter);
	while (i < map->height * map->width)
	{
		if (inter[i].id != -1)
		{
			mat = map->scene.mat[map->scene.shape[inter->id].mat_id];
			if (reflec != NULL && refract == NULL)
				color[i] = color_add(color[i], color_mul(reflec[i], mat.kreflec));
			else if (reflec == NULL && refract != NULL)
				color[i] = color_add(color[i], color_mul(refract[i], mat.krefrac));
			else if (reflec != NULL && refract != NULL)
			color[i] = color_add(color_add(color[i], color_mul(reflec[i], mat.kreflec)), color_mul(refract[i], mat.krefrac));
		}
		i++;
	}
	if (reflec)
		free(reflec);
	if (refract)
		free(refract);
	return (color);
}

int		*get_color2(t_map *map, t_inter *inter, int *color, int depth)
{
	t_ray	*tmp;
	t_inter	*tmp_inter;
	int		*ret;
	int		*ret_refrac;
	int		*ret_reflec;

	ret_refrac = NULL;
	ret_reflec = NULL;
	if (depth < 1 || (!map->config.reflection && !map->config.refraction))
		return (shade(map, inter));
	if (map->config.reflection)
	{
		tmp = get_secondaries(map, inter, &inter->from, 0);
		tmp_inter = get_inter(map, (size_t)map->height * map->width, tmp);
		ret_refrac = get_color2(map, tmp_inter, color, depth - 1);
		free(tmp_inter);
		free(tmp);
	}
	if (map->config.refraction)
	{
		tmp = get_secondaries(map, inter, &inter->from, 1);
		tmp_inter = get_inter(map, (size_t)map->height * map->width, tmp);
		ret_reflec = get_color2(map, tmp_inter, color, depth - 1);
		free(tmp);
		free(tmp_inter);
	}
	ret = end_recursion(map, ret_refrac, ret_reflec, inter);
	return (ret);
}
