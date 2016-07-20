/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_seg_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 15:37:08 by apaget            #+#    #+#             */
/*   Updated: 2016/07/19 17:12:25 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int		check_val(char *line, int max)
{
	char	**tab;
	char	**tab_som;
	int		i;
	int		j;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while (tab[++i])
	{
		tab_som = ft_strsplit(tab[i], '/');
		j = 0;
		while (tab_som[j])
		{
			if (!ft_isdigit(tab_som[j][0]))
				return (0);
			if (ft_isdigit(tab_som[j][0]) && (ft_atoi(tab_som[j]) > max ||
						ft_atoi(tab_som[j]) < 0))
				return (0);
			j++;
		}
		free_tab(tab_som);
	}
	free_tab(tab);
	return (1);
}

int		test_obj(char *filename)
{
	int		fd;
	char	*line;
	int		nb_v;

	fd = open(filename, O_RDONLY);
	nb_v = 0;
	while (get_next_line(fd, &line) > 0 && ft_strsearch(line, "f") == -1)
	{
		if (ft_strsearch(line, "v") != -1)
			nb_v++;
		free(line);
	}
	if (!check_val(line, nb_v))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (!check_val(line, nb_v))
			return (0);
	}
	return (1);
}
