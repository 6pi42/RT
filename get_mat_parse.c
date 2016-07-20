/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mat_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 16:42:30 by apaget            #+#    #+#             */
/*   Updated: 2016/07/19 20:32:34 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_value_parse(t_mat *mat, char *line, t_parse *fuck)
{
	get_value(line, "ka: ", &mat[fuck->nb_mat].ka);
	get_value(line, "ks: ", &mat[fuck->nb_mat].ks);
	get_value(line, "kd: ", &mat[fuck->nb_mat].kd);
	get_value(line, "ktran: ", &mat[fuck->nb_mat].ktran);
	get_value(line, "kreflec: ", &mat[fuck->nb_mat].kreflec);
	get_value(line, "krefrac: ", &mat[fuck->nb_mat].krefrac);
	if (mat[fuck->nb_mat].tex > (t_tex*)0x1)
	{
		get_value(line, "off_x: ", &mat[fuck->nb_mat].tex->off_x);
		get_value(line, "off_y: ", &mat[fuck->nb_mat].tex->off_y);
		get_value(line, "scale: ", &mat[fuck->nb_mat].tex->scale);
	}
}

void	get_tex(t_mat *mat, char *line, t_parse *fuck)
{
	if (ft_strsearch(ft_strchr(line, ' ') + 1, "perlin") != -1)
		mat[fuck->nb_mat].tex = load_perlin_tex();
	else if (ft_strsearch(ft_strchr(line, ' ') + 1, "damier") != -1)
		mat[fuck->nb_mat].tex = (t_tex*)0x1;
	else
		mat[fuck->nb_mat].tex = load_texture(ft_strchr(line, ' ') + 1);
}

void	get_bump(t_mat *mat, char *line, t_parse *fuck)
{
	if (ft_strsearch(ft_strchr(line, ' ') + 1, "perlin") != -1)
		mat[fuck->nb_mat].bump = load_perlin_bump();
	else if (ft_strsearch(ft_strchr(line, ' ') + 1, "sin") != -1)
		mat[fuck->nb_mat].bump = (t_tex*)0x1;
	else
	{
		mat[fuck->nb_mat].bump = load_texture(ft_strchr(line, ' ') + 1);
		mat[fuck->nb_mat].bump->off_x = 0;
		mat[fuck->nb_mat].bump->off_y = 0;
		mat[fuck->nb_mat].bump->scale = 3;
	}
}

int		get_nb_spot(char *file)
{
	int		spot_nb;

	spot_nb = get_number(file, "Spotlight");
	return (spot_nb);
}

int		get_nb_mat(char *file)
{
	int		spot_nb;

	spot_nb = get_number(file, "mat");
	return (spot_nb);
}
