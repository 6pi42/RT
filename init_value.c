/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 06:18:05 by apaget            #+#    #+#             */
/*   Updated: 2016/07/13 06:22:58 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void		init_material_value(t_mat *mat, t_parse *fuck)
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
