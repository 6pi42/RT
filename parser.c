/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:54:18 by emontagn          #+#    #+#             */
/*   Updated: 2016/04/18 17:14:27 by emontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	atoi_double(char *line)
{
	float	integer;
	float	decimal;
	float	sign;

	sign = 1.0f;
	integer = (double)ft_atoi(line);
	if (ft_strchr(line, '-'))
		sign = -1.0f;
	integer = fabs(integer);
	line = ft_strchr(line, '.') + 1;
	decimal = (double)ft_atoi(line);
	while (decimal >= 1.0f)
		decimal /= 10.0f;
	return (sign * (integer + decimal));
}

int		ft_strsearch(char *str1, char *str2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str1[j] && str2[i])
	{
		if (str1[j] == str2[i])
			i++;
		else
			i = 0;
		if (i == (int)ft_strlen(str2))
			return (j + 1);
		j++;
	}
	return (-1);
}

int		get_number(char *file, char *shape_name)
{
	int		i;
	char	*line;
	int		ret;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		printf("error\n");
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strsearch(line, shape_name) != -1)
			i++;
		free(line);
	}
	if (ret == -1)
		printf("error\n");
	close(fd);
	return (i);
}

int		get_nb_shape(char *file)
{
	int		shape_nb;

	shape_nb = get_number(file, "PLANE") + get_number(file, "SPHERE") +
	get_number(file, "CONE") + get_number(file, "CYLINDER") +
	get_number(file, "ELLIPSOID");
	return (shape_nb);
}

void	parsing(t_shape *shape, t_map *map, char *line, int fd)
{
	if (ft_strsearch(line, "MULTI_SAMPLING") != -1)
		get_multi_sampling(fd, map);
	else if (ft_strsearch(line, "WINDOW") != -1)
		get_window(fd, map);
	else if (ft_strsearch(line, "PLANE") != -1)
		get_plane(fd, shape);
	else if (ft_strsearch(line, "SPHERE") != -1)
		get_sphere(fd, shape);
	else if (ft_strsearch(line, "ELLIPSOID") != -1)
		get_ellipsoid(fd, shape);
	else if (ft_strsearch(line, "CONE") != -1)
		get_cone(fd, shape);
	else if (ft_strsearch(line, "CYLINDER") != -1)
		get_cylinder(fd, shape);
	free(line);
}

t_shape	*parse(t_map *map, char *file)
{
	char	*line;
	int		ret;
	int		fd;
	t_shape	*shape;

	printf("NB OF SHAPES:%d\n", get_nb_shape(file));
	shape = (t_shape*)malloc(sizeof(t_shape) * get_nb_shape(file));
	if ((fd = open(file, O_RDONLY)) == -1)
		printf("error\n");
	while ((ret = get_next_line(fd, &line)) > 0)
		parsing(shape, map, line, fd);
	if (ret == -1)
		printf("error\n");
	close(fd);
	return (shape);
}
