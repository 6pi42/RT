/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 15:40:31 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 16:01:30 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	get_refract_ray(t_inter inter, t_ray ray, double indice)
{
	t_ray	refract;
	double	n;
	double	c1;
	double	c2;

	n = indice / 1;
	refract.ray.x = 0;
	refract.ray.y = 0;
	refract.ray.z = 0;
	c1 = -docl_float4(inter.normal, ray.ray);
	c2 = sqrt(1 - n * (1 - c1 * c1));
	refract.ray = add_vec(scale_vec(n, ray.ray),
		scale_vec(n * c1 - c2, inter.normal));
	refract.origin = add_vec(ray.origin, scale_vec(inter.dist + 0.05, ray.ray));
	normalize_vec(&refract.ray);
	return (refract);
}

t_ray	get_reflec_ray(t_inter inter, t_ray ray)
{
	t_ray		reflec;
	cl_float4	inter_pos;

	inter_pos.x = ray.origin.x + ray.ray.x * (inter.dist - 0.05);
	inter_pos.y = ray.origin.y + ray.ray.y * (inter.dist - 0.05);
	inter_pos.z = ray.origin.z + ray.ray.z * (inter.dist - 0.05);
	reflec.ray.x = ray.ray.x - 2.0f * inter.normal.x
		* docl_float4(ray.ray, inter.normal);
	reflec.ray.y = ray.ray.y - 2.0f * inter.normal.y
		* docl_float4(ray.ray, inter.normal);
	reflec.ray.z = ray.ray.z - 2.0f * inter.normal.z
		* docl_float4(ray.ray, inter.normal);
	normalize_vec(&reflec.ray);
	reflec.origin.x = inter_pos.x;
	reflec.origin.y = inter_pos.y;
	reflec.origin.z = inter_pos.z;
	return (reflec);
}
