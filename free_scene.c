/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 06:30:33 by apaget            #+#    #+#             */
/*   Updated: 2016/07/14 16:54:02 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		free_scene(t_scene *scene)
{
	if (scene->shape)
		free(scene->shape);
	scene->shape = NULL;
	scene->nb_shape = 0;
	if (scene->spot)
		free(scene->spot);
	scene->spot = NULL;
	scene->nb_spot = 0;
}
