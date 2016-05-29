/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 01:07:27 by apaget            #+#    #+#             */
/*   Updated: 2016/05/25 17:47:56 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

void	vector_from_angle(t_cam *cam)
{
	cl_float4		up;
	float		tmp;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	if (cam->phi > 89.0f)
		cam->phi = 89.0f;
	if (cam->phi < -89.0f)
		cam->phi = -89.0f;
	tmp = cos((cam->phi * M_PI) / 180.f);
	cam->forward.x =  tmp * sin((cam->theta * M_PI) / 180.f);
	cam->forward.y = sin((cam->phi * M_PI) / 180.f);
	cam->forward.z = tmp * cos((cam->theta * M_PI) / 180.f);
	cam->left = cross_vec(up, cam->forward);
	normalize_vec(&cam->left);
	cam->target = add_vec(cam->pos, cam->forward);
	cam->dir = cam->forward;
	normalize_vec(&cam->dir);
}

void	update_cam(t_cam *cam, t_key *key, t_map *map)
{
	cam->speed = 4.05f;

	if (key->up)
		cam->pos = add_vec(cam->pos, scale_vec(cam->speed, cam->forward));
	if (key->down)
		cam->pos = sub_vec(cam->pos, scale_vec(cam->speed, cam->forward));
	if (key->mleft)
		cam->pos = add_vec(cam->pos, scale_vec(cam->speed, cam->left));
	if (key->mright)
		cam->pos = sub_vec(cam->pos, scale_vec(cam->speed, cam->left));
	cam->target = add_vec(cam->pos, cam->forward);
	vector_from_angle(cam);
	draw(map);
}
