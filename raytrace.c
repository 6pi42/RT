/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:29:58 by amathias          #+#    #+#             */
/*   Updated: 2016/05/29 15:28:01 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
void	display_thread(t_map *map, t_inter *inter, t_ray *ray)
{
	pthread_t	tid[1];
	t_args		*arg1;
	
	arg1 = malloc(sizeof(t_args));
	arg1->map = map;
	arg1->inter = inter;
	arg1->ray = ray;
	pthread_create(&tid[0], NULL, (void*)shade, (void*)arg1);
	pthread_join(tid[0], NULL);
	free(inter);
	free(ray);
	free(arg1);
	//pthread_exit(tid[0]);
}
*/
void	raytrace(t_map *map)
{
	t_ray	*primary;
	t_inter	*inter;
	int		*shading;
	int		i;

	primary = get_primary(map);
	inter = get_inter(map, (size_t)(map->height * map->width), primary);
	//display_thread(map, inter, primary);
	shading = shade(map, inter, primary);
	i = 0;
	while (i < (int)map->width * (int)map->height)
	{
		draw_pixel_to_image(map, i % (int)map->width,
				i / (int)map->width, shading[i]);
		i++;
	}
	free(primary);
	free(inter);
	free(shading);
}
