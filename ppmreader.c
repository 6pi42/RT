/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppmreader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 14:07:09 by cboyer            #+#    #+#             */
/*   Updated: 2016/04/18 17:21:39 by cboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_line(int *tex, char *line)
{
	static int	i = 2;
	static int	j = 1;
	char		*ptr;

	ptr = line;
	while (i < tex[1] * j - 2)
	{
		tex[i] = ft_atoi(ptr);
		if (ptr[0] == ' ')
			ptr++;
		while (ft_isdigit(*ptr))
			ptr++;
		i++;
	}
	j++;
}

int	*get_texture(char *file_name, int sizel, int sizeh)
{
	int		fd;
	int		*tex;
	char	*line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (NULL);
	if (!(tex = (int*)malloc(sizeof(int) * sizeh * sizel + 2)))
		return (NULL);
	tex[0] = sizeh;
	tex[1] = sizel;
	while (get_next_line(fd, &line) > 0)
	{
		get_line(tex, line);
		free(line);
	}
	free(line);
	return (tex);
}
