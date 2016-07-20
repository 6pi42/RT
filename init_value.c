/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 06:18:05 by apaget            #+#    #+#             */
/*   Updated: 2016/07/19 17:13:06 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_material_value(t_mat *mat, t_parse *fuck)
{
	mat[fuck->nb_mat].ka = 1.0f;
	mat[fuck->nb_mat].kd = 1.0f;
	mat[fuck->nb_mat].ks = 0.0f;
	mat[fuck->nb_mat].ktran = 1.0f;
	mat[fuck->nb_mat].kreflec = 0.0f;
	mat[fuck->nb_mat].krefrac = 0.0f;
	mat[fuck->nb_mat].tex = NULL;
	mat[fuck->nb_mat].bump = NULL;
}

t_tex	*load_perlin_tex(void)
{
	t_tex *tex;

	tex = (t_tex*)malloc(sizeof(t_tex));
	tex->buffer = get_perl_tex(512, 512, 120);
	tex->h = 512;
	tex->w = 512;
	tex->scale = 0.1;
	tex->off_x = 0.0;
	tex->off_y = 0.0;
	tex->scale = 0.1;
	printf("perlin loaded\n");
	return (tex);
}

t_tex	*load_perlin_bump(void)
{
	t_tex	*tex;
	int		*buf;

	buf = get_perl_tex(512, 512, 120);
	tex = (t_tex*)malloc(sizeof(t_tex));
	tex->buffer = get_normal_perlin(buf, 512, 512);
	free(buf);
	tex->h = 512;
	tex->w = 512;
	tex->scale = 0.1;
	tex->off_x = 0.0;
	tex->off_y = 0.0;
	tex->scale = 0.1;
	printf("perlin bump loaded\n");
	return (tex);
}

void	get_value(char *line, char *search, float *value)
{
	if (ft_strsearch(line, search) == -1)
		return ;
	*value = atof(ft_strchr(line, ' ') + 1);
}

void	init_parser_value(t_map *map, t_parse *fuck)
{
	fuck->nb = 0;
	fuck->nb_mat = 0;
	fuck->map = map;
}
