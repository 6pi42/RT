/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <amathias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 11:31:54 by amathias          #+#    #+#             */
/*   Updated: 2016/07/19 17:15:37 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	rotate_tri(cl_float4 pt, cl_float4 value)
{
	cl_float4 new;

	new.x = pt.z * sin(value.y * M_PI / 180) + pt.x * cos(value.y * M_PI / 180);
	new.y = pt.y;
	new.z = pt.z * cos(value.y * M_PI / 180) - pt.x * sin(value.y * M_PI / 180);
	new.y = new.y * cos(value.x * M_PI / 180)
		- new.z * sin(value.x * M_PI / 180);
	new.z = new.y * sin(value.x * M_PI / 180)
		+ new.z * cos(value.x * M_PI / 180);
	new.x = new.x * cos(value.z * M_PI / 180)
		- new.y * sin(value.z * M_PI / 180);
	new.y = new.x * sin(value.z * M_PI / 180)
		+ new.y * cos(value.z * M_PI / 180);
	return (new);
}

cl_float4	get_objvector(char *line)
{
	char		**tab;
	cl_float4	vector;
	int			i;

	i = 0;
	while (line[i] == '\t')
		i++;
	tab = ft_strsplit(line + i, ' ');
	i = 0;
	while (tab[i])
		i++;
	if (i != 3)
		ft_putstr("error\n");
	vector.x = atof(tab[0]);
	vector.y = atof(tab[1]);
	vector.z = atof(tab[2]);
	vector.w = 0.0f;
	//vector = rotate_tri(vector, 90.0f);
	free_tab(tab);
	return (vector);
}

cl_float4	parse_element(char *line)
{
	char		**tab;
	cl_float4	vector;
	int			i;

	i = 0;
	tab = ft_strsplit(line, '/');
	while (tab[i])
		i++;
	if (i != 3)
		ft_putstr("error\n");
	vector.x = ft_atoi(tab[0]) - 1;
	vector.y = ft_atoi(tab[1]) - 1;
	vector.z = ft_atoi(tab[2]) - 1;
	vector.w = 0.0f;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (vector);
}

void		parse_face(char *line, t_obj *obj, t_shape *shape)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while (tab[i])
		i++;
	if (i != 3)
		ft_putstr("error\n");
	shape->pos = obj->v[(int)parse_element(tab[0]).x];
	shape->radius = obj->v[(int)parse_element(tab[1]).x];
	shape->axis = obj->v[(int)parse_element(tab[2]).x];
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_shape		get_face(char *line, t_obj *obj)
{
	t_shape shape;

	shape.type.x = 8.0f;
	shape.type.y = 0.0f;
	parse_face(line, obj, &shape);
	shape.color.x = 255.0f;
	shape.color.y = 255.0f;
	shape.color.z = 255.0f;
	shape.color.w = 0.0f;
	shape.axe_decoupe.x = 0.0f;
	shape.axe_decoupe.y = 0.0f;
	shape.axe_decoupe.z = 0.0f;
	shape.axe_decoupe.w = 0.0f;
	shape.mat_id = 0;
	return (shape);
}
