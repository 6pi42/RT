/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:29:58 by amathias          #+#    #+#             */
/*   Updated: 2016/05/29 16:41:59 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void scene_update(t_map *map)
{
	(void)map;
}
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
	GdkPixbuf	*pixel_buf;
	int		*shading;
	int		i;
	int		k;
	unsigned char	*buf;

	buf = (unsigned char*)malloc(sizeof(unsigned char) * (map->height *
		map->width * 3));
	primary = get_primary(map);
	inter = get_inter(map, (size_t)(map->height * map->width), primary);
	//display_thread(map, inter, primary);
	shading = shade(map, inter, primary);
	i = 0;
	k = 0;
	while (i < (int)map->width * (int)map->height)
	{
		buf[k] = (shading[i] & 0xFF0000) >> 16;
		buf[k + 1] = (shading[i] & 0xFF00) >> 8;
		buf[k + 2] = (shading[i] & 0xFF);
		k += 3;
		i++;
	}	
	pixel_buf = gdk_pixbuf_new_from_data((guchar*)buf,GDK_COLORSPACE_RGB,
			FALSE, 8, map->width, map->height, map->width * 3, NULL, NULL);
	gtk_image_set_from_pixbuf(GTK_IMAGE(map->render), pixel_buf);
				g_object_unref(G_OBJECT(pixel_buf));
	free(buf);
	free(primary);
	free(inter);
	free(shading);
}
