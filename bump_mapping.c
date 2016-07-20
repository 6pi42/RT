/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:25:39 by amathias          #+#    #+#             */
/*   Updated: 2016/07/19 19:47:12 by apaget           ###   ########.fr       */
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

	if (inter.normal.x == 0)
	{
		u_axis.x = inter.normal.x;
		u_axis.y = inter.normal.y * cos(90 * M_PI / 180) - inter.normal.z * sin(90 * M_PI / 180);
		u_axis.z = inter.normal.y * sin(90 * M_PI / 180) + inter.normal.z * cos(90 * M_PI / 180);
		v_axis = cross_vec(inter.normal, u_axis);
	}
	else
	{
		v_axis.x = inter.normal.z * sin(90 * M_PI / 180) + inter.normal.x * cos(90 * M_PI / 180);
		v_axis.y = inter.normal.y;
		v_axis.z = inter.normal.z * cos(90 * M_PI / 180) - inter.normal.x * sin(90 * M_PI / 180);
		u_axis = cross_vec(inter.normal, v_axis);
	}
	normalize_vec(&u_axis);
	normalize_vec(&v_axis);
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
		if (!tex)
		{
			bump->off_x = 0.0f;
			bump->off_y = 0.0f;
			bump->scale = 0.001f;
		}
		else
		{
			bump->off_x = tex->off_x;
			bump->off_y = tex->off_y;
			bump->scale = tex->scale;
		}
		
		if (shape.type.x == 1.0f)
			normal = sphere_bumpmapping(bump, inter);
		else if (shape.type.x == 2.0f)
			normal = plane_bumpmapping(bump, inter, inter_pos);
		else if (shape.type.x == 3.0f || shape.type.x == 4.0f)
			normal = cylinder_bumpmapping(bump, inter, shape, inter_pos);
	}
	else if (shape.type.x == 2.0f && bump == (t_tex*)0x1)
		normal = get_sin_perturbation(map, shape, inter_pos, inter);
	return (normal);
}
