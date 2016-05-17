/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_writer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 10:04:06 by amathias          #+#    #+#             */
/*   Updated: 2016/05/13 11:20:09 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*get_img(t_map *map, int work_size)
{
	int		k;
	int		i;
	int		j;
	int		index;
	char	*tmp;

	if ((tmp = (char*)malloc(work_size)) == NULL)
		return (NULL);
	i = (int)map->height - 1;
	k = 0;
	while (i >= 0)
	{
		j = 0;
		while (j < (int)map->width)
		{
			index = i * map->img.size_line + (j * map->img.bpp) / 8;
			tmp[k] = map->img.data[index];
			tmp[k + 1] = map->img.data[index + 1];
			tmp[k + 2] = map->img.data[index + 2];
			k += 3;
			j++;
		}
		i--;
	}
	return (tmp);
}

void	write_header(t_map *map, int fd, int zero, int work_size)
{
	int value;

	ft_putstr_fd("BM", fd);
	value = 0x36 + (map->img.size_line * (int)map->height);
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
	if ((fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT,
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
