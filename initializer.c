/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 13:52:38 by emontagn          #+#    #+#             */
/*   Updated: 2016/07/20 08:59:03 by emontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_shape(t_parse *fuck)
{
	fuck->shape[fuck->nb].type.x = 0;
	fuck->shape[fuck->nb].type.y = 0;
	fuck->shape[fuck->nb].type.z = 0;

	fuck->shape[fuck->nb].pos.x = 0;
	fuck->shape[fuck->nb].pos.y = 0;
	fuck->shape[fuck->nb].pos.z = 0;

	fuck->shape[fuck->nb].radius.x = 0;
	fuck->shape[fuck->nb].radius.y = 0;
	fuck->shape[fuck->nb].radius.z = 0;

	fuck->shape[fuck->nb].color.x = 255;
	fuck->shape[fuck->nb].color.y = 255;
	fuck->shape[fuck->nb].color.z = 255;

	fuck->shape[fuck->nb].axis.x = 1;
	fuck->shape[fuck->nb].axis.y = 0;
	fuck->shape[fuck->nb].axis.z = 0;

	fuck->shape[fuck->nb].axe_decoupe.x = 0;
	fuck->shape[fuck->nb].axe_decoupe.y = 0;
	fuck->shape[fuck->nb].axe_decoupe.z = 0;
	fuck->shape[fuck->nb].axe_decoupe.w = 0;

	fuck->shape[fuck->nb].mat_id = 0;
}

void init_scene(t_map *map)
{
	// CAMERA
	map->scene.max_depth = 0;
	map->scene.nb_shape = 0;
	map->scene.nb_spot = 0;
	map->scene.nb_mat = 0;

	map->scene->cam.origin.x = 0.0;
	map->scene->cam.origin.y = 0.0;
	map->scene->cam.origin.z = 0.0;

	map->scene->cam.ray.x = 0.0;
	map->scene->cam.ray.y = 0.0;
	map->scene->cam.ray.z = 0.0;

	map->scene->cam.down.x = 0.0;
	map->scene->cam.down.y = 0.0;
	map->scene->cam.down.z = 0.0;

	map->scene->cam.right.x = 0.0;
	map->scene->cam.right.y = 0.0;
	map->scene->cam.right.z = 0.0;

	map->scene->cam.ratio = 0.0;

	// SPOT
	map->scene->spot.type = 0;

	map->scene->spot.pos.x = 0.0;
	map->scene->spot.pos.y = 0.0;
	map->scene->spot.pos.z = 0.0;

	map->scene->spot.color = 0xFFFFFF;

	map->scene->spot.intensity = 42.0;

	// MAT
	map->scene->mat.ka = 0.0;
	map->scene.mat.kd = 0.0;
	map->scene.mat.ks = 0.0;
	map->scene.mat.ktran = 0.0;
	map->scene.mat.kreflec = 0.0;
	map->scene.mat.krefrac = 0.0;
	map->scene.mat.indice = 0;

	map->scene->mat->tex = NULL;
	map->scene->mat->bump = NULL;
}
