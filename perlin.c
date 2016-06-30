/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 11:28:12 by apaget            #+#    #+#             */
/*   Updated: 2016/06/30 14:15:53 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_var(t_perlin *perl, float x, float y, float res)
{
	perl->x_tab = (int)x;
	perl->y_tab = (int)y;
	perl->xx = perl->x_tab & 255;
	perl->yy = perl->y_tab & 255;
	perl->x = x / res;
	perl->y = y / res;
}

void	init_perl(t_perlin *perl)
{
	unsigned char table[512] =
	{151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
		142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,
		203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
		74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,
		105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
		187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,
		64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
		47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
		153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
		112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,
		235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,
		127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,
		156,180};
	ft_memcpy(perl->table, table, 512);
}

float	get_sommet(t_perlin *perl, int x, int y)
{
	float	delta_x;
	float	delta_y;
	int		rand_vector;
	float unit = 1.0f/sqrt(2);
	float gradient[][2] = {{unit,unit},{-unit,unit},{unit,-unit},
							{-unit,-unit},{1,0},{-1,0},{0,1},{0,-1}};

	delta_x = perl->x - (perl->x_tab + x);
	delta_y = perl->y - (perl->y_tab + y);
	rand_vector = perl->table[perl->xx + x + perl->table[perl->yy + y]] % 8;
	return (gradient[rand_vector][0] * delta_x + gradient[rand_vector][1] * delta_y);
}


int		calc_pt_color(t_perlin *perl, int x, int y, float res)
{
	float tmp;
	float coef_lissage_x;
	float coef_lissage_y;
	float lx1;
	float lx2;

	init_var(perl, (x  + 0.1) / res , y / res, res);
	perl->a = get_sommet(perl, 0, 0);
	perl->b = get_sommet(perl, 1, 0);
	perl->c = get_sommet(perl, 0, 1);
	perl->d = get_sommet(perl, 1, 1);
	tmp = perl->x - perl->x_tab;
	coef_lissage_x = 3 * tmp * tmp - 2 * tmp * tmp;
	lx1 = perl->a + coef_lissage_x * (perl->b - perl->a);
	lx2 = perl->c + coef_lissage_x * (perl->d - perl->c);
	tmp = perl->y - perl->y_tab;
	coef_lissage_y = 3 * tmp * tmp - 2 * tmp * tmp;
	return ((lx1 + coef_lissage_y * (lx2 - lx1)));
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
			tex[i] = tex[i] < 0 ? 0 : tex[i];
			i++;
			y++;
		}
		x++;
	}
	return (tex);
}

/*
float	get_color_perlin(float x, float y, float res)
{

	int x_tab;
	int y_tab;
	int rand_vector;
	float delta_x;
	float delta_y;
	float a,b,c,d;
	float tmp, coef_lissage_x, coef_lissage_y;
	float lx1, lx2, ly;
	int xx, yy;
	
	x /= res;
	y /= res;
	x_tab = (int)x;
	y_tab = (int)y;

	xx = x_tab & 0xff;
	yy = y_tab & 0xff;

	delta_x = x - x_tab;
	delta_y = y - y_tab;
	rand_vector = table[xx + table[yy]] % 8;
	a = gradient[rand_vector][0] * delta_x + gradient[rand_vector][1] * delta_y;
	delta_x = x - (x_tab + 1);
	delta_y = y - y_tab;
	rand_vector = table[xx + 1 + table[yy]] % 8;
	b = gradient[rand_vector][0] * delta_x + gradient[rand_vector][1] * delta_y;
	delta_x = x - x_tab;
	delta_y = y - (y_tab + 1);
	rand_vector = table[xx + table[yy + 1]] % 8;
	c = gradient[rand_vector][0] * delta_x + gradient[rand_vector][1] * delta_y;
	delta_x = x - (x_tab + 1);
	delta_y = y - (y_tab + 1);
	rand_vector = table[xx + 1 + table[yy + 1]] % 8;
	d = gradient[rand_vector][0] * delta_x + gradient[rand_vector][1] * delta_y;
	tmp = x - x_tab;
	coef_lissage_x = 3 * tmp * tmp - 2 * tmp * tmp;
	lx1 = a + coef_lissage_x * (b - a);
	lx2 = c + coef_lissage_x * (d - c);
	tmp = y - y_tab;
	coef_lissage_y = 3 * tmp * tmp - 2 * tmp * tmp;
	return (lx1 + coef_lissage_y * (lx2 - lx1));
	*/
