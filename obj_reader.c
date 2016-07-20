/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 11:28:47 by amathias          #+#    #+#             */
/*   Updated: 2016/07/19 15:20:51 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*obj_alloc(char *file_name, int v, int vn, int vt)
{
	t_obj	*obj;
	char	*line;
	int		fd;
	int		f;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		ft_putstr("error");
	obj = (t_obj*)malloc(sizeof(t_obj));
	f = 0;
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
	obj->v = (cl_float4*)malloc(sizeof(cl_float4) * v);
	obj->vn = (cl_float4*)malloc(sizeof(cl_float4) * vn);
	obj->vt = (cl_float4*)malloc(sizeof(cl_float4) * vt);
	obj->f = (t_shape*)malloc(sizeof(t_shape) * f);
	close(fd);
	return (obj);
}

void	init_obj(t_obj *obj)
{
	obj->nb_v = 0;
	obj->nb_vn = 0;
	obj->nb_vt = 0;
	obj->nb_f = 0;
}

void	obj_read(t_map *map, char *file_name)
{
	char	*line;
	t_obj	*obj;
	int		fd;
	
	obj = obj_alloc(file_name, 0, 0, 0);
	init_obj(obj);
	(void)map;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		ft_putstr("error");
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strsearch(line, "v ") != -1)
			obj->v[obj->nb_v++] = get_objvector(ft_strchr(line, 'v') + 1);
		if (ft_strsearch(line, "f ") != -1)
			obj->f[obj->nb_f++] = get_face(ft_strchr(line, 'f') + 1, obj);
		free(line);
	}

	int i;

	i = 0;
	while (i < obj->nb_v)
	{
		printf("%f %f %f\n", obj->v[i].x, obj->v[i].y, obj->v[i].z);
		i++;
	}
	free(obj->v);
	free(obj->vn);
	free(obj->vt);
	map->scene.shape = obj->f;
	printf("nb: %d", obj->nb_f);
	map->scene.nb_shape = obj->nb_f;
}
