/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:25:39 by amathias          #+#    #+#             */
/*   Updated: 2016/07/17 18:07:10 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	calc_binormal(cl_float4 polygon_n, cl_float4 ts_n)
{
	cl_float4 binormal;
	cl_float4 tangent;

	tangent = get_perpendicular_vec(polygon_n);
	normalize_vec(&tangent);
	binormal = cross_vec(tangent, polygon_n);
	normalize_vec(&binormal);
	return (mul_mat3_vector(tangent, binormal, polygon_n, ts_n));
}

cl_float4	plane_bumpmapping(t_tex *tex, t_inter inter, cl_float4 inter_pos)
{
	cl_float4	u_axis;
	cl_float4	v_axis;
	int			color;

	u_axis.x = inter.normal.y;
	u_axis.y = inter.normal.z;
	u_axis.z = -inter.normal.x;
	v_axis = cross_vec(inter.normal, u_axis);
	color = bilinear_filtering(tex,
		tex->off_x + docl_float4(inter_pos, v_axis) * tex->scale,
		tex->off_y + docl_float4(inter_pos, u_axis) * tex->scale);
	return (calc_binormal(inter.normal, get_bump_normal(color)));
}

cl_float4	sphere_bumpmapping(t_tex *tex, t_inter inter)
{
	float	u;
	float	v;
	int		color;

	u = 0.5f + atan2(inter.normal.z, inter.normal.x) * (2.0f * M_PI);
	v = 0.5f - asin(inter.normal.y) * M_PI;
	color = bilinear_filtering(tex,
		tex->off_x + (((float)tex->w - 1.0f) * u) * tex->scale,
		tex->off_y + (((float)tex->h - 1.0f) * v) * tex->scale);
	return (calc_binormal(inter.normal, get_bump_normal(color)));
}

cl_float4	cylinder_bumpmapping(t_tex *tex, t_inter inter, t_shape shape,
				cl_float4 inter_pos)
{
	float	u;
	float	v;
	int		color;

	(void)shape;
	(void)inter;
	u = atan2(inter_pos.z, inter_pos.x) + M_PI;
	v = inter_pos.y / 42.0f;
	color = bilinear_filtering(tex,
		tex->off_x + (((float)tex->w - 1.0f) * u) * tex->scale,
		tex->off_y + (((float)tex->h - 1.0f) * v) * tex->scale);
	return (calc_binormal(inter.normal, get_bump_normal(color)));
}

cl_float4	get_sin_perturbation(t_map *map, t_shape shape, cl_float4 inter_pos,
		t_inter inter)
{
	cl_float4 orientation;
	cl_float4	new;
	float dist;
	(void)map;

	orientation = sub_vec(inter_pos, shape.pos);
	dist = dis_point(inter_pos, shape.pos);
	normalize_vec(&orientation);
	new = add_vec(inter.normal, scale_vec(exp(-dist / 5) * sin (dist) * 20, orientation));
	normalize_vec(&new);
	return (new);
}

cl_float4	get_bumped_normal(t_map *map, t_inter inter, t_shape shape,
				cl_float4 inter_pos)
{
	t_tex		*bump;
	t_tex		*tex;
	cl_float4	normal;

	(void)map;
	bump = map->scene.mat[shape.mat_id].bump;
	tex = map->scene.mat[shape.mat_id].tex;
	normal = inter.normal;
	if (bump)
	{
		bump->off_x = 0.5f;
		bump->off_y = 0.0f;
		/*
		bump->off_x = tex->off_x;
		bump->off_y = tex->off_x;
		bump->scale = tex->scale;
		bump->h = tex->h;
		bump->w = tex->w;
		*/
		bump->scale = 0.5;
		if (shape.type.x == 1.0f)
			normal = sphere_bumpmapping(bump, inter);
		else if (shape.type.x == 2.0f)
			normal = plane_bumpmapping(bump, inter, inter_pos);
		else if (shape.type.x == 3.0f || shape.type.x == 4.0f)
			normal = cylinder_bumpmapping(bump, inter, shape, inter_pos);
	}
		else if (shape.type.x == 2.0f)
			normal = get_sin_perturbation(map, shape, inter_pos, inter);
	return (normal);
}
