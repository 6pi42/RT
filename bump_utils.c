/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 14:31:26 by amathias          #+#    #+#             */
/*   Updated: 2016/07/14 14:36:12 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	get_bump_normal(int color)
{
	cl_float4	normal;
	int			red;
	int			green;
	int			blue;

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
	return (perp);
}

cl_float4	mul_mat3_vector(cl_float4 tan, cl_float4 bi, cl_float4 norm,
		cl_float4 bump)
{
	cl_float4 res;

	res.x = (bump.x * tan.x) + (bump.y * bi.x) + (bump.z * norm.x);
	res.y = (bump.x * tan.y) + (bump.y * bi.y) + (bump.z * norm.y);
	res.z = (bump.x * tan.z) + (bump.y * bi.z) + (bump.z * norm.z);
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
