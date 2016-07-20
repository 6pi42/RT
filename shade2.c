/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 16:30:55 by amathias          #+#    #+#             */
/*   Updated: 2016/07/19 13:31:58 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	diffuse_lighting(t_spot spot, cl_float4 norm, cl_float4 inter)
{
	cl_float4	light;
	float		angle;

	light.x = spot.pos.x - inter.x;
	light.y = spot.pos.y - inter.y;
	light.z = spot.pos.z - inter.z;
	normalize_vec(&light);
	angle = fmax(0.0f, docl_float4(light, norm));
	return (angle);
}

float	spec_light(t_spot spot, t_inter inter, t_ray ray, cl_float4 inter_pos)
{
	cl_float4	eye;
	cl_float4	light;
	cl_float4	halfvec;
	float		coef;

	eye = sub_vec(ray.origin, inter_pos);
	normalize_vec(&eye);
	light = sub_vec(spot.pos, inter_pos);
	normalize_vec(&light);
	halfvec = add_vec(eye, light);
	normalize_vec(&halfvec);
	coef = pow(fmax(0.0f, docl_float4(halfvec, inter.normal)), spot.intensity);
	return (coef);
}

int		get_color(t_map *map, t_mat mat, t_utils utils, int color)
{
	t_spot	spot;
	int		diffuse;
	int		spec;

	diffuse = color;
	spot = map->current_spot;
	spec = color_mul(spot.color,
	spec_light(spot, utils.inter, utils.ray, utils.inter_pos) * mat.ks);
	diffuse = color_mul(color, mat.kd * diffuse_lighting(spot,
		utils.inter.normal, utils.inter_pos));
	return (color_add(color_add(spec, color_mul(color, mat.ka)), diffuse));
}

int		get_trans_color(t_map *map, int color, t_inter tmp)
{
	if (map->scene.mat[map->scene.shape[tmp.id].mat_id].krefrac == 0)
		color = color_mul(color, 0.2);
	else
	{
		color = color_add(color, color_mul(
		get_texture_color(map, tmp, map->scene.shape[tmp.id],
		get_inter_pos(tmp.from, tmp)),
		map->scene.mat[map->scene.shape[tmp.id].mat_id].krefrac));
	}
	return (color);
}
