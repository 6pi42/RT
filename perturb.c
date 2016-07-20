/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 14:24:07 by amathias          #+#    #+#             */
/*   Updated: 2016/07/18 14:24:13 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	get_sin_perturbation(t_map *map, t_shape shape, cl_float4 inter_pos,
		t_inter inter)
{
	cl_float4	orientation;
	cl_float4	new;
	float		dist;

	(void)map;
	orientation = sub_vec(inter_pos, shape.pos);
	dist = dis_point(inter_pos, shape.pos);
	normalize_vec(&orientation);
	new = add_vec(inter.normal, scale_vec(exp(-dist / 5)
			* sin(dist) * 20, orientation));
	normalize_vec(&new);
	return (new);
}
