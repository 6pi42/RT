/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_writer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:01:09 by apaget            #+#    #+#             */
/*   Updated: 2016/05/25 17:47:43 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*load_from_gtk_image(t_map *map)
{
	GdkPixbuf *pix_buf;

	pix_buf = gtk_image_get_pixbuf(GTK_IMAGE(map->render));
	return ((char*)gdk_pixbuf_get_pixels(pix_buf));
}

char	*get_img(t_map *map, int work_size)
{
	int		k;
	int		i;
	int		j;
	int		index;
	char	*tmp;
	char	*pix_buf;

	if ((tmp = (char*)malloc(work_size)) == NULL)
		return (NULL);
	pix_buf = load_from_gtk_image(map);
	i = (int)map->height;
	k = 0;
	while (--i >= 0)
	{
		j = -1;
		while (++j < (int)map->width)
		{
			index = i * map->width * 3 + (j * 3) ;
			tmp[k] = pix_buf[index + 2];
			tmp[k + 1] = pix_buf[index + 1];
			tmp[k + 2] = pix_buf[index];
			k += 3;
		}
	}
	return (tmp);
}

void	write_header(t_map *map, int fd, int zero, int work_size)
{
	int value;

	ft_putstr_fd("BM", fd);
	value = 0x36 + work_size;
	write(fd, &value, 4);
	write(fd, &zero, 4);
	value = 0x36;
	write(fd, &value, 4);
	value = 0x28;
	write(fd, &value, 4);
	value = (int)map->width;
	write(fd, &value, 4);
	value = (int)map->height;
	write(fd, &value, 4);
	value = 0x01;
	write(fd, &value, 2);
	value = 0x18;
	write(fd, &value, 2);
	write(fd, &zero, 4);
	write(fd, &work_size, 4);
	value = 2835;
	write(fd, &value, 4);
	write(fd, &value, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
}

char	*get_file_name(char *base_name, char *ext)
{
	char			*file_name;
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	file_name = ft_itoa((int)timestamp.tv_sec);
	base_name = ft_strjoin(base_name, file_name);
	free(file_name);
	file_name = ft_strjoin(base_name, ext);
	free(base_name);
	return (file_name);
}

void	write_bitmap(t_map *map)
{
	char	*file_name;
	int		fd;
	char	*img;
	int		work_size;

	file_name = get_file_name("screenshot_", ".bmp");
	if ((fd = open(file_name, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT,
					S_IRUSR | S_IWUSR)) == -1)
		return ;
	free(file_name);
	work_size = 3 * (int)map->width * (int)map->height;
	write_header(map, fd, 0, work_size);
	img = get_img(map, work_size);
	if (img)
	{
		write(fd, img, work_size);
		free(img);
		ft_putchar_fd('\n', fd);
	}
	if (close(fd) == -1)
		return ;
}
