/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 13:19:27 by amathias          #+#    #+#             */
/*   Updated: 2016/07/15 15:56:37 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		plane_texturing(t_tex *tex, t_inter inter, cl_float4 inter_pos)
{
	cl_float4	u_axis;
	cl_float4	v_axis;
	int			color;

	u_axis.x = inter.normal.y;
	u_axis.y = inter.normal.z;
	u_axis.z = -inter.normal.x;
	v_axis = cross_vec(inter.normal, u_axis);
	color = bilinear_filtering(tex,
		tex->off_x + fmod(docl_float4(inter_pos, v_axis) * tex->scale, tex->w),
		tex->off_y + fmod(docl_float4(inter_pos, u_axis) * tex->scale, tex->h));
	return (color);
}

int		sphere_texturing(t_tex *tex, t_inter inter)
{
	float	u;
	float	v;
	int		color;

	u = 0.5f + atan2(inter.normal.z, inter.normal.x) * (2.0f * M_PI);
	v = 0.5f - asin(inter.normal.y) * M_PI;
	color = bilinear_filtering(tex,
		tex->off_x + (((float)tex->w - 1.0f) * u) * tex->scale,
		tex->off_y + (((float)tex->h - 1.0f) * v) * tex->scale);
	return (color);
}

int		cylinder_texturing(t_tex *tex, t_inter inter, t_shape shape,
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
	return (color);
}

int		get_texture_color(t_map *map, t_inter inter, t_shape shape,
			cl_float4 inter_pos)
{
	int		color;
	t_tex	*tex;

	(void)map;
	tex = map->scene.mat[shape.mat_id].tex;
	color = color_from_float4(shape.color);
	if (tex)
	{
		if (shape.type.x == 1.0f)
			color = sphere_texturing(tex, inter);
		else if (shape.type.x == 2.0f)
			color = plane_texturing(tex, inter, inter_pos);
		else if (shape.type.x == 3.0f || shape.type.x == 4.0f)
			color = cylinder_texturing(tex, inter, shape, inter_pos);
	}
	return (color);
}
