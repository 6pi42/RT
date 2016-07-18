/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <amathias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 11:31:54 by amathias          #+#    #+#             */
/*   Updated: 2016/07/15 14:00:41 by emontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

cl_float4	get_vector(char *line)
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
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
	vector.x = ft_atoi(tab[0]);
	vector.y = ft_atoi(tab[1]);
	vector.z = ft_atoi(tab[2]);
	vector.w = 0.0f;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
	parse_face(line, obj);
	obj->color.x = 255.0f;
	obj->color.y = 0.0f;
	obj->color.z = 0.0f;
	obj->color.w = 0.0f;
}
