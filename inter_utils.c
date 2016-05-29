/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 10:36:52 by amathias          #+#    #+#             */
/*   Updated: 2016/05/25 10:42:11 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	get_inter_pos(t_ray ray, t_inter inter)
{
	cl_float4	inter_pos;

	inter_pos.x = ray.origin.x + (ray.ray.x * inter.dist);
	inter_pos.y = ray.origin.y + (ray.ray.y * inter.dist);
	inter_pos.z = ray.origin.z + (ray.ray.z * inter.dist);
	inter_pos.w = 0.0f;
	return (inter_pos);
}
