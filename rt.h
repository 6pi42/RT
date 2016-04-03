/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:34:06 by amathias          #+#    #+#             */
/*   Updated: 2016/04/03 17:08:05 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <OpenCL/cl.h>
# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
#include <stdio.h>

typedef struct	s_sphere
{
	cl_float4 type;
	cl_float4 pos;
	cl_float4 radius;
	cl_float4 color;
}				t_sphere;

typedef struct	s_ray
{
	cl_float4	origin;
	cl_float4	ray;
}				t_ray;

typedef struct	s_scene
{
	t_ray	*cam;
	int nb_sphere;
	t_sphere *sphere;
	int	nb_plan;
	t_sphere *plan;
}				t_scene;

typedef struct	s_img
{
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_key
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			mleft;
	int			mright;
}				t_key;

typedef struct	s_env
{
	cl_device_id		id;
	cl_context			context;
	cl_command_queue	cmds;
	cl_program			program;
	cl_kernel			kernel;
}				t_env;

typedef struct	s_map
{
	void		*mlx;
	void		*win;
	t_env		env;
	t_img		img;
	t_key		key;
	t_scene		scene;
	int			height;
	int			width;
}				t_map;

typedef struct	s_prog
{
	char		*buffer;
	size_t		len;
}				t_prog;

void	draw(t_map *map);
void	ocl_init(t_env *env, t_prog prog);
t_prog	get_prog(char *file_name);
int		key_hook(int keycode, t_map *map);
int		loop_hook(t_map *map);
void	move(t_map *map);
void	init_key(t_map *map);
int		key_press(int keycode, t_map *map);
#endif
