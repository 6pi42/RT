/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 13:19:27 by amathias          #+#    #+#             */
/*   Updated: 2016/07/14 13:57:47 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		color_add4(int c1, int c2, int c3, int c4)
{
	int	red;
	int green;
	int blue;

	red = (((c1 & 0xFF0000) >> 16)
			+ ((c2 & 0xFF0000) >> 16)
			+ ((c3 & 0xFF0000) >> 16)
			+ ((c4 & 0xFF0000) >> 16));
	green = (((c1 & 0xFF00) >> 8)
			+ ((c2 & 0xFF00) >> 8)
			+ ((c3 & 0xFF00) >> 8)
			+ ((c4 & 0xFF00) >> 8));
	blue = ((c1 & 0xFF)
			+ (c2 & 0xFF)
			+ (c3 & 0xFF)
			+ (c4 & 0xFF));
	red = red > 0xFF ? 0xFF : red;
	green = green > 0xFF ? 0xFF : green;
	blue = blue > 0xFF ? 0xFF : blue;
	return (red << 16 | green << 8 | blue);
}

int		bilinear_filtering(t_tex *tex, float x, float y)
{
	t_bil 	bil;
	float 	fx;
	float 	fy;
	int		color;

	fx = (x + 1000.5f) * (float)tex->w;
	fy = (y + 1000.5f) * (float)tex->w;
	bil.x1 = ((int)fx) % tex->w;
	bil.y1 = ((int)fy) % tex->h;
	bil.x2 = (bil.x1 + 1) % tex->w;
	bil.y2 = (bil.y1 + 1) % tex->h;
	bil.fractx = fx - floor(fx);
	bil.fracty = fy - floor(fy);
	color = color_add4(color_mul(tex->buffer[bil.x1 + bil.y1 * tex->w],
				(1.0f - bil.fractx) * (1.0f - bil.fracty)),
			color_mul(tex->buffer[bil.x2 + bil.y1 * tex->w],
				bil.fractx * (1.0f - bil.fracty)),
			color_mul(tex->buffer[bil.x1 + bil.y2 * tex->w],
				(1.0f - bil.fractx) * bil.fracty),
			color_mul(tex->buffer[bil.x2 + bil.y2 * tex->w],
				bil.fractx * bil.fracty));
	return (color);
}

int		plane_texturing(t_tex *tex, t_inter inter, cl_float4 inter_pos)
{
	cl_float4 u_axis;
	cl_float4 v_axis;
	int color;

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

int 	get_texture_color(t_map *map, t_inter inter, t_shape shape,
		cl_float4 inter_pos)
{
	int		color;
	t_tex 	*tex;

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
			color = cylinder_texturing(tex, inter, shape,inter_pos);
	}
	return (color);	
}
