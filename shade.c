/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:59:59 by amathias          #+#    #+#             */
/*   Updated: 2016/07/16 16:41:39 by apaget           ###   ########.fr       */
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
	
	diffuse = color;
	spot = map->current_spot;
	spec = color_mul(spot.color,
	spec_light(spot, utils.inter, utils.ray, utils.inter_pos) * mat.ks);
	diffuse = color_mul(color, mat.kd * diffuse_lighting(spot, utils.inter.normal, utils.inter_pos));
	return (color_add(color_add(spec, color_mul(color, mat.ka)), diffuse));
}

int		iter_spot(t_map *map, t_mat mat, t_utils utils, int color)
{
	int i;
	int c;
	int	*acolor;

	i = 0;
	(void)mat;
	acolor = (int*)malloc(sizeof(int) * map->scene.nb_spot);
	while (i < map->scene.nb_spot)
	{
		// check shadow here
		c = 0x00;
		if (utils.inter.id != -1)
		{
			mat = map->scene.mat[map->scene.shape[utils.inter.id].mat_id];
			map->current_spot = map->scene.spot[i];
			if (utils.shadow)
			{
				c = color_mul(get_color(map, mat, utils, color), 0.2);
				utils.shadow--;
			}
			else
				c = get_color(map, mat, utils, color);
		}
		acolor[i] = c;
		i++;
	}
	return (color_average(acolor, map->scene.nb_spot));
}

t_ray *prep_ray_trans(t_map *map, t_inter *inter)
{
	t_ray	*ray;
	int		i;

	i = 0;
	if ((ray = (t_ray*)malloc(sizeof(t_ray) * (size_t)(map->height * map->width))) == NULL)
		return NULL;
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1)
		{
			ray[i].origin =  map->scene.spot[0].pos;
			ray[i].ray = sub_vec(add_vec(inter[i].from.origin, scale_vec(inter[i].dist, inter[i].from.ray)), map->scene.spot[0].pos);
			normalize_vec(&ray[i].ray);
		}
		i++;
	}
	return (ray);
}

int		*apply_trans(t_map *map, t_inter *inter, int *color)
{
	int		i;
	t_inter *tmp;
	t_ray	*ray;

	i = 0;
	
	if ((ray = prep_ray_trans(map, inter)) == NULL)
		return (color);
	tmp = get_inter(map, map->height * map->width, ray);
	i = 0;
	while (i < (int)(map->height * map->width))
	{
		if (inter[i].id != -1 && tmp[i].id != -1 && inter[i].id != tmp[i].id
		&& map->scene.mat[map->scene.shape[tmp[i].id].mat_id].krefrac != 0)
		{
			color[i] = color_add(color[i], color_mul(
				get_texture_color(map, tmp[i], map->scene.shape[tmp[i].id],
				get_inter_pos(tmp[i].from, tmp[i])),
				map->scene.mat[map->scene.shape[tmp[i].id].mat_id].krefrac / 2));
		}
		i++;
	}
	return (color);
}

int		*shade(t_map *map, t_inter *inter)
{
	int		*is_shadow;
	t_utils utils;
	int		i;
	cl_float4 tmp;
	int		*color;

	color = (int*)malloc(sizeof(int) * (size_t)(map->height * map->width));
	i = 0;
	is_shadow = shadow(map, inter);
	while (i < (int)(map->height * map->width))
	{
		color[i] = 0x0;
		if (inter[i].id != -1)
		{
			utils.inter = inter[i];
			utils.ray = inter[i].from;
			utils.inter_pos = get_inter_pos(utils.ray, utils.inter);
			utils.shadow = is_shadow[i];
			tmp = map->scene.shape[inter[i].id].color;
			if (map->config.texture)
			{
				color[i] = get_texture_color(map, inter[i],
					map->scene.shape[inter[i].id],
					get_inter_pos(inter[i].from, inter[i]));

				utils.inter.normal = get_bumped_normal(map, inter[i],
					map->scene.shape[inter[i].id],
					get_inter_pos(inter[i].from, inter[i]));
			}
			else
				color[i] = color_from_float4( map->scene.shape[inter[i].id].color);
			color[i] = iter_spot(map, map->scene.mat[map->scene.shape[inter[i].id].mat_id], utils, color[i]);
		}
		i++;
	}
	if (map->config.transparence)
		color = apply_trans(map, inter, color);
	free(is_shadow);
	return (color);
}
