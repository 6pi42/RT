/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 02:15:07 by apaget            #+#    #+#             */
/*   Updated: 2016/05/26 18:12:52 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_nb_trianle(int fd)
{
	char	*ligne;
	int		count;

	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'v' && *(line + 1) == ' ')
			count++;
	}
	return (count);
}

int			analyse_buffer(char **tab, float *buffer)
{
	int		i;
		
	i = -1;
	if (!tab[0] || !tab[1], || !tab[2])
		return (0);
	while (++i < 3)
		buffer[i] = atoi_double(tab[i]);
}

void		load_buffer(int fd, float **buffer, int nb_vertex, int nb_normal)
{
	char	*ligne;
	char	**tab;
	
	while (get_next_line(fd, &ligne) > 0)
	{
		tab = ft_strsplit(ligne, ' ');
		if (ft_strstr(tab[0], "vn"))
			analyse_buffer()
	}
}

t_shape		*load_obj(char *file)
{
	int		fd;
	int		nb_normal;
	int		nb_vertex;
	t_shape	*obj;
	float	*buffer[2];

	fd = 0;
	nb_vertex = get_nb_trianle(fd);
	nb_normal = get_number(file, "vn");
	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	*buffer = (float*)malloc(sizeof(float) * 3 * nb_vertex);
	*(buffer + 1) = (float*)malloc(sizeof(float) * 3 * nb_normal);
	if (!buffer || !(buffer + 1))
		return (NULL);

}
