/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <amathias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 10:24:51 by amathias          #+#    #+#             */
/*   Updated: 2016/07/14 16:10:52 by emontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		*convert_texture(guchar *gubuffer, int width, int height, int c)
{
	int *buf;
	int i;
	int j;

	buf = (int*)malloc(sizeof(int) * (width * height));
	i = 0;
	j = ((width * height) * c);
	while (i < (width * height))
	{
		buf[i] = (int)(gubuffer[j] << 16
						| gubuffer[j + 1] << 8
						| gubuffer[j + 2]);
		j -= c;
		i++;
	}
	return buf;
}

t_tex	*load_texture(char *file_name)
{
	t_tex		*tex;
	GdkPixbuf 	*pixbuf;
	GError 		*error;

	error = NULL;
	if ((tex = (t_tex*)malloc(sizeof(t_tex))) == NULL)
		return (NULL);
	pixbuf = gdk_pixbuf_new_from_file(file_name, &error);
	if (pixbuf == NULL)
	{
		ft_putstr("Gdk cannnot load texture\n");
		g_error_free(error);
		return (NULL);
	}
	tex->w = gdk_pixbuf_get_width(pixbuf);
	tex->h = gdk_pixbuf_get_height(pixbuf);
	tex->buffer = convert_texture(gdk_pixbuf_get_pixels(pixbuf), tex->w, tex->h,
					gdk_pixbuf_get_n_channels(pixbuf));
	g_object_unref(pixbuf);
	return (tex);
}
