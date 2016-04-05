/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:34:06 by amathias          #+#    #+#             */
/*   Updated: 2016/04/05 11:18:39 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <OpenCL/cl.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <unistd.h>
# include "libft.h"
#include <stdio.h>

typedef struct	s_fps
{
	double		frames;
	time_t		start;
	time_t		end;
}				t_fps;

typedef struct	s_shape
{
	cl_float4 	type;
	cl_float4	pos;
	cl_float4	radius;
	cl_float4	color;
	cl_float4	axis;
}				t_shape;

typedef struct	s_ray
{
	cl_float4	origin;
	cl_float4	ray;
}				t_ray;

typedef struct	s_scene
{
	t_ray		*cam;
	int 		nb_sphere;
	t_shape 	*sphere;
	int			nb_plan;
	t_shape		*plan;
	int			nb_cyl;
	t_shape		*cyl;
	int			nb_cone;
	t_shape		*cone;
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
	int			num_8;
	int			num_4;
	int			num_2;
	int			num_6;
	int			mx;
	int			my;
	double		theta;
	double		phi;
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
	t_fps		fps;
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
void	rotate(t_map *map);
void	init_key(t_map *map);
int		key_press(int keycode, t_map *map);
int		motion_notify(int x, int y, t_map *map);
#endif
