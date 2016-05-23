/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:39 by amathias          #+#    #+#             */
/*   Updated: 2016/05/23 12:33:40 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	get_reflec_ray(t_inter inter, t_ray ray)
{
	t_ray		reflec;
	cl_float4	inter;

	inter.x = ray.origin.x + ray.ray.x * inter.dist;
	inter.y = ray.origin.y + ray.ray.y * inter.dist;
	inter.z = ray.origin.z + ray.ray.z * inter.dist;
	reflec.ray.x = ray.ray.x - 2.0f * inter.normal.x
		* dotcl_float4(ray->dir, norm);
	reflec.ray.y = ray.ray.y - 2.0f * inter.normal.y
		* dotcl_float4(ray->dir, norm);
	reflec.ray.z = ray.ray.z - 2.0f * inter.normal.z
		* dotcl_float4(ray->dir, norm);
	reflec.origin.x = inter.x + reflec.ray.x * 0.1f;
	reflec.origin.y = inter.y + reflec.ray.y * 0.1f;
	reflec.origin.z = inter.z + reflec.ray.z * 0.1f;
	return (reflec);
}

t_ray	get_secondary(t_map *map, t_inter inter, t_ray ray)
{
	t_ray	secondary;
	t_mat	mat;
	int		mat_id;

	mat_id = (int)shape[inter.id].type.w;
	if (mat_id >= 0 && mat_id < map->scene.nb_mat)
	{
		mat = map->scene.mat[mat_id];
		if (mat.ktran != 0.0f)
			secondary = ;
		if (mat.kreflec != 0.0f)	
			secondary = get_reflec_ray(inter, ray);
	}
}

t_ray	*get_secondaries(t_map *map, t_inter, t_ray *ray)
{
	t_ray	*secondaries;
	int		i;
	
	secondaries = (t_ray*)malloc(sizeof(t_ray) * (size_t)(map->height
				* map->width));
	i = 0;
	while (i < (int)(map->height * map->width))
	{
		if (inter.id != 1)
		{
			secondaries[i].
		}
		i++;
	}
}

//Evaluate secondary ray
int		mat_eval(t_map *map, t_inter *inter, t_ray *ray, int *is_shadow)
{
	
}
