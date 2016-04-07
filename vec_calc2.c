/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 03:41:10 by apaget            #+#    #+#             */
/*   Updated: 2016/04/07 13:54:05 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	scale_vec(double fact, cl_float4 v1)
{
	cl_float4 res;

	res.x = v1.x * fact;
	res.y = v1.y * fact;
	res.z = v1.z * fact;
	return (res);
}

void	normalize_vec(cl_float4 *v1)
{
	double	fact;
	double	vec_len;

	if ((vec_len = len_vec(*v1)) == 0)
		vec_len = 0.001;
	fact = 1.0f / vec_len;
	v1->x *= fact;
	v1->y *= fact;
	v1->z *= fact;
}

double	docl_float4(cl_float4 v1, cl_float4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	dis_point(cl_float4 pt1, cl_float4 pt2)
{
	return (sqrt((pt2.x - pt1.x) * (pt2.x - pt1.x) + (pt2.y - pt1.y) *
				(pt2.y - pt1.y) + (pt2.z - pt1.z) * (pt2.z - pt1.z)));
}

cl_float4	neg_vec(cl_float4 vec)
{
	vec.x *= -1;
	vec.y *= -1;
	vec.z *= -1;
	return (vec);
}
