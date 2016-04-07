/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 01:07:27 by apaget            #+#    #+#             */
/*   Updated: 2016/04/07 13:54:26 by amathias         ###   ########.fr       */
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
	if (cam->phi > 89)
		cam->phi = 89;
	if (cam->phi < -89)
		cam->phi = -89;
	if (cam->theta < -89)
		cam->theta = -89;
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

void	update_cam(t_cam *cam, t_key *key)
{
	cam->speed = 4.05;

	if (key->up)
		cam->pos = add_vec(cam->pos, scale_vec(cam->speed, cam->forward));
	if (key->down)
		cam->pos = sub_vec(cam->pos, scale_vec(cam->speed, cam->forward));
	if (key->left)
		cam->pos = add_vec(cam->pos, scale_vec(cam->speed, cam->left));
	if (key->right)
		cam->pos = sub_vec(cam->pos, scale_vec(cam->speed, cam->left));
	cam->target = add_vec(cam->pos, cam->forward);
	vector_from_angle(cam);
}
