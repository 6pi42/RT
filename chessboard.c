/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chessboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 11:19:09 by amathias          #+#    #+#             */
/*   Updated: 2016/07/17 14:09:46 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_even(int x)
{
	if (x % 2 == 0)
		return (1);
	else
		return (0);
}

int		plane_chessboard(int c, cl_float4 inter_pos)
{
	int			sum;
	int			color;
	//u_axis.x = inter.normal.y;
	//u_axis.y = inter.normal.z;
	//u_axis.z = -inter.normal.x;
	//v_axis = cross_vec(inter.normal, u_axis);
	/*float dist = dis_point(inter_pos, shape.pos);
	cl_float4 tmp;
	tmp.x = 0.0f;
	tmp.y = 1.0f;
	tmp.z = 0.0f;
	tmp.w = 0.0f;
	float agl = docl_float4(cross_vec(tmp, inter.normal), sub_vec(shape.pos, inter_pos));
	float x = dist * cos(agl * M_PI / 180.0f);
	float y = dist * sin(agl * M_PI / 180.0f); */
	sum = (int)round(inter_pos.x / 10.0f) + (int)round(inter_pos.y / 10.0f) + (int)round(inter_pos.z / 10.0f);
	if (is_even(sum))
		color = c;
	else
		color = color_sub(0xFFFFFF, c);
	return (color);
}

int		sphere_chessboard(int c, t_inter inter)
{
	float	u;
	float	v;
	int		color;

	u = 0.5f + atan2(inter.normal.z, inter.normal.x) * (2.0f * M_PI);
	v = 0.5f - asin(inter.normal.y) * M_PI;
	if (is_even(round(u) + round(v)))
		color = c;
	else
		color = color_sub(0xFFFFFF, c);
	return (color);
}

int		cylinder_chessboard(int c, cl_float4 inter_pos)
{
	float	sum;
	int		color;

	sum = (int)round(inter_pos.x / 10.0f)
		+ (int)round(inter_pos.y / 10.0f) + (int)round(inter_pos.z / 10.0f);
	if (is_even(sum))
		color = c;
	else
		color = color_sub(0xFFFFFF, c);
	return (color);
}

int		get_chessboard_color(t_map *map, t_inter inter, t_shape shape,
			cl_float4 inter_pos)
{
	int		color;
	t_tex	*tex;

	(void)map;
	(void)shape;
	(void)inter;
	tex = NULL;
	color = color_from_float4(shape.color);
	if (shape.type.x == 1.0f)
		color = sphere_chessboard(color, inter);
	if (shape.type.x == 2.0f)
		color = plane_chessboard(color, inter_pos);
	else if (shape.type.x == 3.0f || shape.type.x == 4.0f)
		color = cylinder_chessboard(color, inter_pos);
	return (color);
}
