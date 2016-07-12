/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:25:39 by amathias          #+#    #+#             */
/*   Updated: 2016/07/12 14:08:17 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	get_bump_normal(int color)
{
	cl_float4 normal;
	int	red;
	int green;
	int blue;

	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0xFF00) >> 8);
	blue = (color & 0xFF);
	normal.x = 2.0f * ((float)red / 256.0f) - 1.0f;
	normal.y = 2.0f * ((float)green / 256.0f) - 1.0f;
	normal.z = 2.0f * ((float)blue / 256.0f) - 1.0f;
	normal.w = 0.0f;
	normalize_vec(&normal);
	return (normal);
}

cl_float4	get_perpendicular_vec(cl_float4 normal)
{
	cl_float4 perp;
	cl_float4 tmp;
	tmp.x = 0.0f;
	tmp.y = 0.0f;
	tmp.z = 1.0f;
	tmp.w = 0.0f;

	perp = cross_vec(normal, tmp);
	normalize_vec(&perp);
	//if (fabs(docl_float4(perp, normal)) != 0.0f)
	//	printf("not perp %f\n", docl_float4(perp, normal));
	return (perp);
}

cl_float4	mul_mat3_vector(cl_float4 tan, cl_float4 bi, cl_float4 norm,
				cl_float4 bump)
{
	cl_float4 res;
	/*
	if (docl_float4(tan, norm) != 0.0f || docl_float4(norm, bi) != 0.0f)
	{
		printf("tan: %f %f %f %f\n", tan.x, tan.y, tan.z, tan.w);
		printf("bi: %f %f %f %f\n", bi.x, bi.y, bi.z, bi.w);
		printf("norm: %f %f %f %f\n", norm.x, norm.y, norm.z, norm.w);
	} */
	res.x = (bump.x * tan.x) + (bump.y * bi.x) + (bump.z * norm.x);
	res.y = (bump.x * tan.y) + (bump.y * bi.y) + (bump.z * norm.y);
	res.z = (bump.x * tan.z) + (bump.y * bi.z) + (bump.z * norm.z);

	//res.x = (bump.x * tan.x) + (bump.y * tan.y) + (bump.z * tan.z);
	//res.y = (bump.x * bi.x) + (bump.y * bi.y) + (bump.z * bi.z);
	//res.z = (bump.x * norm.x) + (bump.y * norm.y) + (bump.z * norm.z);
	res.w = 0.0f;
	normalize_vec(&res);
	return (res);
}

cl_float4	add3_vec(cl_float4 tangent, cl_float4 binormal, cl_float4 normal)
{
	cl_float4 res;

	res.x = tangent.x + binormal.x + normal.x;
	res.y = tangent.y + binormal.y + normal.y;
	res.z = tangent.z + binormal.z + normal.z;
	res.w = 0.0f;
	normalize_vec(&res);
	return (res);
}
cl_float4	calc_binormal(cl_float4 polygon_n, cl_float4 ts_n)
{
	cl_float4 binormal;
	cl_float4 tangent;

	tangent = get_perpendicular_vec(polygon_n);
	//tangent.x = tangent.x - docl_float4(tangent, polygon_n) * polygon_n.x;
	//tangent.y = tangent.y - docl_float4(tangent, polygon_n) * polygon_n.y;
	//tangent.z = tangent.z - docl_float4(tangent, polygon_n) * polygon_n.z;
	normalize_vec(&tangent);
	//tangent.x = tangent.x - ts_n.x * docl_float4(tangent, ts_n);
	//tangent.y = tangent.y - ts_n.y * docl_float4(tangent, ts_n);
	//tangent.z = tangent.z - ts_n.z * docl_float4(tangent, ts_n);
	//tangent.w = 0.0f;
	//normalize_vec(&tangent);
	binormal = cross_vec(tangent, polygon_n);
	normalize_vec(&binormal);
	return (mul_mat3_vector(tangent, binormal, polygon_n, ts_n));
/*
	cl_float4 polygon_t;
	cl_float4 polygon_b;
	cl_float4 ts_t;
	cl_float4 ts_b;
	cl_float4 normal;
	
	polygon_t = get_perpendicular_vec(polygon_n);
	polygon_b = cross_vec(polygon_t, polygon_n);
	ts_t = get_perpendicular_vec(ts_n);
	ts_b = cross_vec(ts_t, ts_n);
	normal = add3_vec(scale_vec(ts_n.x, polygon_t),
						scale_vec(ts_n.y, polygon_b),
						scale_vec(ts_n.z, polygon_n));
	return (normal); */
}

cl_float4	plane_bumpmapping(t_tex *tex, t_inter inter, cl_float4 inter_pos)
{
	cl_float4 u_axis;
	cl_float4 v_axis;
	int color;
	
	u_axis.x = inter.normal.y;
	u_axis.y = inter.normal.z;
	u_axis.z = -inter.normal.x;	
	v_axis = cross_vec(inter.normal, u_axis);

	color = bilinear_filtering(tex,
			fmod(docl_float4(inter_pos, v_axis) * 0.005f, tex->w),
			fmod(docl_float4(inter_pos, u_axis) * 0.005f, tex->h));
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
				(((float)tex->w - 1.0f) * u) * 0.001f,
				(((float)tex->h - 1.0f) * v) * 0.001f);
	return (calc_binormal(inter.normal, get_bump_normal(color)));
}

cl_float4	get_bumped_normal(t_map *map, t_inter inter, t_shape shape,
				cl_float4 inter_pos)
{
	t_tex		*tex;
	cl_float4	normal;

	(void)map;
	tex = shape.mat.bump;
	normal = inter.normal;
	if (tex)
	{
		if (shape.type.x == 1.0f)
			normal = sphere_bumpmapping(tex, inter);
		else if (shape.type.x == 2.0f)
			normal = plane_bumpmapping(tex, inter, inter_pos);
	}
	return (normal);
}
