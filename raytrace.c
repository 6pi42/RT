/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:29:58 by amathias          #+#    #+#             */
/*   Updated: 2016/07/19 18:00:10 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_update(t_map *map)
{
	(void)map;
}

void	disp(t_map *map, int *shading)
{
	unsigned char	*buf;
	GdkPixbuf		*pixel_buf;
	int				i;
	int				k;

	buf = (unsigned char*)malloc(map->height * map->width * 3);
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
	pixel_buf = gdk_pixbuf_new_from_data((guchar*)buf, GDK_COLORSPACE_RGB,
			FALSE, 8, map->width, map->height, map->width * 3, NULL, NULL);
	gtk_image_set_from_pixbuf(GTK_IMAGE(map->render), pixel_buf);
	if (map->img.data)
		free(map->img.data);
	map->img.data = shading;
	g_object_unref(G_OBJECT(pixel_buf));
	free(buf);
}

void	multi_sample(t_map *map, int *shading, unsigned int multi)
{
	t_ray	*primary;
	t_inter	*inter;
	int		*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while ((unsigned int)i < multi - 1)
	{
		primary = get_primary(map, i);
		inter = get_inter(map, (size_t)(map->height * map->width), primary);
		tmp = get_color2(map, inter, shading, map->scene.max_depth);
		color_average_array(map, shading, tmp);
		free(primary);
		free(inter);
		i++;
	}
}

void	raytrace(t_map *map)
{
	t_ray			*primary;
	t_inter			*inter;
	int				*shading;

	shading = NULL;
	primary = get_primary(map, 0);
	inter = get_inter(map, (size_t)(map->height * map->width), primary);
	printf("coucou\n");
	shading = get_color2(map, inter, shading, map->scene.max_depth);
	if (map->multi_sampling)
		multi_sample(map, shading, map->multi_sampling);
	disp(map, shading);
	free(primary);
	free(inter);
}
