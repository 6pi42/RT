/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:59:59 by amathias          #+#    #+#             */
/*   Updated: 2016/07/11 20:07:17 by apaget           ###   ########.fr       */
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

	//TODO: implement parallel light source
	//ez to do (if type == 2) spot.pos = dir of vector
	eye = sub_vec(ray.origin, inter_pos);
	normalize_vec(&eye);
	light = sub_vec(spot.pos, inter_pos);
	normalize_vec(&light);
	halfvec = add_vec(eye, light);
	normalize_vec(&halfvec);
	coef = pow(fmax(0.0f, docl_float4(halfvec, inter.normal)), spot.intensity);
	return (coef);
}

static int	get_color(t_map *map, t_mat mat, t_utils utils, int color)
{
	t_spot spot;
	int diffuse;
	int spec;
	(void)mat;

	spec = 0;
	diffuse = color;
	spot = map->current_spot;
	spec = color_mul(spot.color,
			spec_light(spot, utils.inter, utils.ray, utils.inter_pos) * map->scene.shape[utils.inter.id].mat.ks);
	diffuse = color_mul(color, map->scene.shape[utils.inter.id].mat.kd * diffuse_lighting(spot, utils.inter.normal, utils.inter_pos));
	return (color_add(spec, color_mul(diffuse, 1)));
}

int		iter_spot(t_map *map, t_mat mat, t_utils utils, int color)
{
	int i;

	i = 0;
	(void)mat;
	while (i < map->scene.nb_spot)
	{
		// check shadow here
		if (utils.inter.id != -1)
		{
			map->current_spot = map->scene.spot[i];
			color = get_color(map, mat, utils, color);
		}
		i++;
	}
	return (color);
}

int		*apply_trans(t_map *map, t_inter *inter, int *color)
{
	int		i;
	t_inter *tmp;
	t_ray	*ray;

	i = 0;
	if ((ray = (t_ray*)malloc(sizeof(t_ray) * (size_t)(map->height * map->width))) == NULL)
		return NULL;
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1)
		{
			ray[i].origin = add_vec(inter[i].from.origin, scale_vec(inter[i].dist - 0.05f, inter[i].from.ray));
			ray[i].ray = sub_vec(map->scene.spot[0].pos, add_vec(inter[i].from.origin, scale_vec(inter[i].dist, inter[i].from.ray)));
			normalize_vec(&ray[i].ray);
		}
		i++;
	}
	tmp = get_inter(map, map->height * map->width, ray);
	i = 0;
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1 && tmp[i].id != -1 && inter[i].id != tmp[i].id  && map->scene.shape[tmp[i].id].mat.krefrac != 0)
		{
			color[i] = color_add(color[i], color_mul(color_from_float4(map->scene.shape[tmp[i].id].color), map->scene.shape[tmp[i].id].mat.krefrac / 3));
		}
		i++;
	}
	return (color);
}
int		*shade(t_map *map, t_inter *inter)
{
	t_utils utils;
	int		i;
	t_mat mat;
	cl_float4 tmp;
	int		*color;

	mat.ks = 0;
	color = (int*)malloc(sizeof(int) * (size_t)(map->height * map->width));
	i = 0;
	while (i < (int)(map->height * map->width))
	{
		color[i] = 0x0;
		if (inter[i].id != -1)
		{
			utils.inter = inter[i];
			utils.ray = inter[i].from;
			utils.inter_pos = get_inter_pos(utils.ray, utils.inter);
			// to remove when shape.color == int
			tmp = map->scene.shape[inter[i].id].color;
			color[i] += (int)(tmp.x * 256 * 256);
			color[i] += (int)(tmp.y * 256);
			color[i] += (int)(tmp.z);
			color[i] = iter_spot(map, mat, utils, color[i]);
		}
		i++;
	}
	color = apply_trans(map, inter, color);
	return (color);
}
