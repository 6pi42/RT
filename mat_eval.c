/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:39 by amathias          #+#    #+#             */
/*   Updated: 2016/05/27 10:18:04 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	get_refract_ray(t_inter inter, t_ray ray)
{
	t_ray		refract;
	cl_float4	inter_pos;
	
	//Mimic of refract
	//TODO: implement real refraction
	inter_pos = get_inter_pos(ray, inter);
	refract.ray.x = ray.ray.x;
	refract.ray.y = ray.ray.y;
	refract.ray.z = ray.ray.z;
	refract.origin.x = inter_pos.x + refract.ray.x * 0.1f;
	refract.origin.y = inter_pos.y + refract.ray.y * 0.1f;
	refract.origin.z = inter_pos.z + refract.ray.z * 0.1f;
	return (refract);
}

t_ray	get_reflec_ray(t_inter inter, t_ray ray)
{
	t_ray		reflec;
	cl_float4	inter_pos;

	inter_pos.x = ray.origin.x + ray.ray.x * inter.dist;
	inter_pos.y = ray.origin.y + ray.ray.y * inter.dist;
	inter_pos.z = ray.origin.z + ray.ray.z * inter.dist;
	reflec.ray.x = ray.ray.x - 2.0f * inter.normal.x
		* docl_float4(ray.ray, inter.normal);
	reflec.ray.y = ray.ray.y - 2.0f * inter.normal.y
		* docl_float4(ray.ray, inter.normal);
	reflec.ray.z = ray.ray.z - 2.0f * inter.normal.z
		* docl_float4(ray.ray, inter.normal);
	reflec.origin.x = inter_pos.x + reflec.ray.x * 0.1f;
	reflec.origin.y = inter_pos.y + reflec.ray.y * 0.1f;
	reflec.origin.z = inter_pos.z + reflec.ray.z * 0.1f;
	return (reflec);
}

t_ray	get_secondary(t_map *map, t_inter inter, t_ray ray)
{
	t_ray	secondary;
	t_mat	mat;
	int		mat_id;

	secondary.ray.x = 0.0f;
	secondary.ray.y = 0.0f;
	secondary.ray.z = 0.0f;
	secondary.ray.w = 0.0f;
	mat_id = (int)map->scene.shape[inter.id].type.w;
	if (mat_id >= 0 && mat_id < map->scene.nb_mat)
	{
		mat = map->scene.mat[mat_id];
		if (mat.ktran != 0.0f)
			secondary = get_refract_ray(inter, ray);
		if (mat.kreflec != 0.0f)	
			secondary = get_reflec_ray(inter, ray);
	}
	return (secondary);
}

t_ray	*get_secondaries(t_map *map, t_inter *inter, t_ray *ray)
{
	t_ray	*secondaries;
	int		i;
	
	secondaries = (t_ray*)malloc(sizeof(t_ray) * (size_t)(map->height
				* map->width));
	i = 0;
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1)
		{
			secondaries[i] = get_secondary(map, inter[i], ray[i]);
		}
		i++;
	}
	return (secondaries);
}

int		*get_color(t_map *map, t_inter *inter, t_ray *ray)
{
	int		*color;
	t_ray	*secondaries;
	t_inter	*inter_new;

	color = (int*)malloc(sizeof(int) * (size_t)(map->height * map->width));
	secondaries = get_secondaries(map, inter, ray);
	inter_new = get_inter(map, (size_t)(map->height * map->width), secondaries);
	return (color);
}

int		*mat_eval(t_map *map, t_inter *inter, t_ray *ray, int *is_shadow)
{
	int *color;
	int depth;

	(void)inter;
	(void)ray;
	(void)is_shadow;
	color = (int*)malloc(sizeof(int) * (size_t)(map->height * map->width));
	depth = 0;
	while (depth < map->scene.max_depth)
	{
		
	}	
	return (color);	
}
