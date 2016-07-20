/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 12:47:52 by apaget            #+#    #+#             */
/*   Updated: 2016/07/18 14:06:46 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_scene(t_map *map)
{
	int i = 0;
	printf("------------------------------------------------------------\n\n");
	printf("SCENE\n\t{");
	printf("\t-Window\n{\t\twidth :%.0f\n\t\theight: %.0f\n\t", map->width, map->height);
	printf("}\n\n");
	printf("\t -Camera\n\t{\n\t\tpos : %.2f %.2f %.2f\n\t\tphi: %.2f\n\t\ttheta: %.2f\n\t}\n\n", map->free_cam.pos.x, map->free_cam.pos.y,map->free_cam.pos.z, map->free_cam.phi, map->free_cam.theta);
	for (i = 0; i < map->scene.nb_spot; i++) {
	printf("\t- Spotlight\n\t{\n\t\ttype: %d\n\t\tpos: %f %f %f\n\t\trgb: %d %d %d\n\t\tintensity: %.1f\n\t}\n\n",map->scene.spot[i].type, 
			map->scene.spot[i].pos.x, map->scene.spot[i].pos.y, map->scene.spot[i].pos.z, (map->scene.spot[i].color & 0xff0000) >> 16, (map->scene.spot[i].color & 0x00ff00) >> 8, (map->scene.spot[i].color & 0xff), map->scene.spot[i].intensity);
	}
	printf("\t- Multi Sampling\n\t{\n\t\tpower: %d\n\t}\n\n", map->multi_sampling);
	printf("MATERIAL\n{\n");
	for (i = 0; i < map->scene.nb_mat; i++) {
		printf("\t- mat %d\n\t{\n\t\ttex: \n\t\tka: %.2f\n\t\tks: %.2f\n\t\tkd: %.2f\n\t\tktran: %.2f\n\t\tkreflec: %.2f\n\t\tkrefrac: %.2f\n\t}\n", i,
				map->scene.mat[i].ka, map->scene.mat[i].ks,map->scene.mat[i].kd, map->scene.mat[i].ktran, map->scene.mat[i].kreflec, map->scene.mat[i].krefrac);
	}
	printf("\n");
	printf("SHAPES\n{\n");
	for (i = 0; i < map->scene.nb_shape; i++) {
		if (map->scene.shape[i].type.x == 1)
			printf("\t - Sphere\n");
		else if (map->scene.shape[i].type.x == 2)
			printf("\t - Plane\n");
		else if (map->scene.shape[i].type.x == 3)
			printf("\t - Cylinder\n");
		else if (map->scene.shape[i].type.x == 4)
			printf("\t - Cone\n");
		else if (map->scene.shape[i].type.x == 8)
			printf("\t - Triangle\n");
		else if (map->scene.shape[i].type.x == 7)
			printf("\t - Cercle\n");
		printf("\t{\n\t\tid: %d\n\t\tneg: %.0f\n\t\trgb: %.0f %.0f %.0f\n\t\tpos: %.2f %.2f %.2f\n", map->scene.shape[i].mat_id,
				map->scene.shape[i].type.y, map->scene.shape[i].color.x, map->scene.shape[i].color.y, map->scene.shape[i].color.z,
				map->scene.shape[i].pos.x, map->scene.shape[i].pos.y, map->scene.shape[i].pos.z);
		if (map->scene.shape[i].type.x == 4 || map->scene.shape[i].type.x == 3)
			printf("\t\tdir: %.2f %.2f %.2f\n\t\tsize: %.2f\n", map->scene.shape[i].axis.x, map->scene.shape[i].axis.y, map->scene.shape[i].axis.z, map->scene.shape[i].type.w);
		else if (map->scene.shape[i].type.x == 2 || map->scene.shape[i].type.x == 7)
			printf("\t\tnor: %.2f %.2f %.2f\n", map->scene.shape[i].axis.x, map->scene.shape[i].axis.y, map->scene.shape[i].axis.z);
		if (map->scene.shape[i].type.x == 4)
			printf("\t\tagl: %.2f\n",map->scene.shape[i].radius.x);
		if (map->scene.shape[i].type.x == 3 || map->scene.shape[i].type.x == 1 || map->scene.shape[i].type.x == 7)
			printf("\t\trad: %.2f\n", map->scene.shape[i].radius.x);
		printf("\t}\n\n");
	}
	printf("}\n");
}
