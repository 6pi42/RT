/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 11:28:47 by amathias          #+#    #+#             */
/*   Updated: 2016/07/14 15:53:25 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*obj_alloc(char *file_name, int v, int vn, int vt)
{
	t_obj	obj;
	char	*line;
	int		fd;
	int		f;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		ft_putstr("error");
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strsearch(line, "v ") != -1)
			v++;
		if (ft_strsearch(line, "vn ") != -1)
			vn++;
		if (ft_strsearch(line, "vt ") != -1)
			vt++;
		if (ft_strsearch(line, "f ") != -1)
			f++;
	}
	obj.v = (cl_float4*)malloc(sizeof(cl_float4) * v);
	obj.vn = (cl_float4*)malloc(sizeof(cl_float4) * vn);
	obj.vt = (cl_float4*)malloc(sizeof(cl_float4) * vt);
	obj.f = (t_shape*)malloc(sizeof(t_shape) * f);
	close(fd);
	return (&obj);
}

void	obj_read(t_map *map, char *file_name)
{
	char	*line;
	t_obj	*obj;
	int		fd;

	obj = obj_alloc(filename, 0, 0, 0);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		ft_putstr("error");
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strsearch(line, "v ") != -1)
			get_vector(ft_strchr(line, 'v') + 1);
		if (ft_strsearch(line, "vn ") != -1)
			get_vector(ft_strchr(line, 'v') + 1);
		if (ft_strsearch(line, "vt ") != -1)
			get_vector(ft_strchr(line, 'v') + 1);
		if (ft_strsearch(line, "f ") != -1)
			get_vector(ft_strchr(line, 'v') + 1);
	}
}
