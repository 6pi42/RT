/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 15:25:17 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 15:26:17 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_var(t_perlin *perl, float x, float y, float res)
{
	perl->x = x / res;
	perl->y = y / res;
	perl->x_tab = (int)perl->x;
	perl->y_tab = (int)perl->y;
	perl->xx = perl->x_tab & 255;
	perl->yy = perl->y_tab & 255;
}

void	init_perl(t_perlin *perl)
{
	int		i;
	float	unit;

	i = -1;
	unit = 1.0f / sqrt(2);
	srand(time(NULL));
	while (++i < 512)
		perl->table[i] = rand() % 255;
	perl->gradient[0][0] = unit;
	perl->gradient[0][1] = -unit;
	perl->gradient[1][0] = -unit;
	perl->gradient[1][1] = unit;
	perl->gradient[2][0] = unit;
	perl->gradient[2][1] = -unit;
	perl->gradient[3][0] = -unit;
	perl->gradient[3][1] = -unit;
	perl->gradient[4][0] = 1;
	perl->gradient[4][1] = 0;
	perl->gradient[5][0] = -1;
	perl->gradient[5][1] = 0;
	perl->gradient[6][0] = 0;
	perl->gradient[6][1] = 1;
	perl->gradient[7][0] = 0;
	perl->gradient[7][1] = -1;
}

float	get_sommet(t_perlin *perl, int x, int y)
{
	float	delta_x;
	float	delta_y;
	int		rand_vector;

	delta_x = perl->x - (perl->x_tab + x);
	delta_y = perl->y - (perl->y_tab + y);
	rand_vector = perl->table[perl->xx + x + perl->table[perl->yy + y]] % 8;
	return (perl->gradient[rand_vector][0] * delta_x +
			perl->gradient[rand_vector][1] * delta_y);
}

int		calc_pt_color(t_perlin *perl, int x, int y, float res)
{
	float tmp;
	float coef_lissage_x;
	float coef_lissage_y;
	float lx1;
	float lx2;

	init_var(perl, (x + 0.5), (y + 0.5), res);
	perl->a = get_sommet(perl, 0, 0);
	perl->b = get_sommet(perl, 1, 0);
	perl->c = get_sommet(perl, 0, 1);
	perl->d = get_sommet(perl, 1, 1);
	tmp = perl->x - perl->x_tab;
	coef_lissage_x = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
	lx1 = perl->a + coef_lissage_x * (perl->b - perl->a);
	lx2 = perl->c + coef_lissage_x * (perl->d - perl->c);
	tmp = perl->y - perl->y_tab;
	coef_lissage_y = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
	return (((lx1 + coef_lissage_y * (lx2 - lx1)) + 1) * 0.5 * 255);
}

int		*get_perl_tex(int height, int width, float res)
{
	t_perlin	perl;
	int			x;
	int			y;
	int			*tex;
	int			i;

	if ((tex = (int*)malloc(sizeof(int) * height * width)) == NULL)
		return (NULL);
	init_perl(&perl);
	x = 0;
	i = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			tex[i] = calc_pt_color(&perl, x, y, res);
			tex[i] = tex[i];
			i++;
			y++;
		}
		x++;
	}
	return (tex);
}
