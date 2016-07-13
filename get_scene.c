/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 16:16:11 by emontagn          #+#    #+#             */
/*   Updated: 2016/07/13 02:47:21 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_window(int fd, t_map *map)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 4)
	{
		if ((j = ft_strsearch(line, "width: ")) != -1)
			map->width = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "height: ")) != -1)
			map->height = atoi(ft_strchr(line, ' ') + 1);
		free(line);
		i++;
	}
	if (ret == -1)
		exit(0);
}

void	get_camera(int fd, t_map *map)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 3)
	{
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			map->free_cam.pos = get_position(ft_strchr(line, ' ') + 1);
		free(line);
		i++;
	}
	if (ret == -1)
		exit(0);
}

void	get_multi_sampling(int fd, t_map *map)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 3)
	{
		if ((j = ft_strsearch(line, "power: ")) != -1)
			map->multi_sampling = atoi(ft_strchr(line, ' ') + 1);
		free(line);
		i++;
	}
	if (ret == -1)
		exit(0);
}

void	get_spotlight(int fd, t_map *map)
{
	int			i;
	int			j;
	int			ret;
	char		*line;

	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && i != 6)
	{
		if ((j = ft_strsearch(line, "pos: ")) != -1)
			map->scene.spot[map->spoti].pos = get_position(line + j);
		else if ((j = ft_strsearch(line, "rgb: ")) != -1)
			map->scene.spot[map->spoti].color = get_rgb_int(line + j);
		else if ((j = ft_strsearch(line, "type: ")) != -1)
			map->scene.spot[map->spoti].type = atoi(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "intensity: ")) != -1)
			map->scene.spot[map->spoti].intensity = atoi_double(ft_strchr(line, ' ') + 1);

		free(line);
		i++;
	}
	if (ret == -1)
		printf("fuck\n");
	map->spoti++;
}
void	init_material_value(t_mat *mat, t_parse *fuck)
{
	mat[fuck->nb_mat].ka = 0.4f;
	mat[fuck->nb_mat].kd = 0.2f;
	mat[fuck->nb_mat].ks = 0.0f;
	mat[fuck->nb_mat].ktran = 0.0f;
	mat[fuck->nb_mat].kreflec = 0.0f;
	mat[fuck->nb_mat].krefrac = 0.0f;
	mat[fuck->nb_mat].tex = NULL;
	mat[fuck->nb_mat].bump = NULL;
}
void	get_material(int fd, t_parse *fuck)
{
	int			i;
	int			j;
	int			ret;
	char		*line;
	t_mat		*mat;

	i = 0;
	mat = fuck->map->scene.mat;
	init_material_value(mat, fuck);
	while ((ret = get_next_line(fd, &line)) > 0 && i != 9)
	{
		if ((j = ft_strsearch(line, "ka: ")) != -1)
			mat[fuck->nb_mat].ka = atoi_double(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "ks: ")) != -1)
			mat[fuck->nb_mat].ks = atoi_double(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "kd: ")) != -1)
			mat[fuck->nb_mat].kd = atoi_double(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "ktran: ")) != -1)
			mat[fuck->nb_mat].ktran = atoi_double(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "kreflec: ")) != -1)
			mat[fuck->nb_mat].kreflec = atoi_double(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "krefrac: ")) != -1)
			mat[fuck->nb_mat].krefrac = atoi_double(ft_strchr(line, ' ') + 1);
		else if ((j = ft_strsearch(line, "tex: ")) != -1)
		{
			printf("texture charger : %s\n", ft_strchr(line, ' ') + 1);
			mat[fuck->nb_mat].tex = load_texture(ft_strchr(line, ' ') + 1);
		}
		free(line);
		i++;
	}
	fuck->nb_mat++;
	if (ret == -1)
		exit(0);
}
