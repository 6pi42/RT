/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:34:06 by amathias          #+#    #+#             */
/*   Updated: 2016/05/29 15:27:23 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <OpenCL/cl.h>
# include <pthread.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include <unistd.h>
# include "libft.h"
#include <stdio.h>

typedef	struct	s_ray
{
	cl_float4	origin;
	cl_float4	ray;
}				t_ray;

typedef struct	s_spot
{
	int			type;
	cl_float4	pos;
	int			color;
	float		intensity;
}				t_spot;

typedef	struct	s_mat
{
	float		ka;
	float		kd;
	float		ks;
	float		ktran;
	float		kreflec;
	float		krefrac;
}				t_mat;

typedef struct	s_clbuf
{
	cl_mem		output;
	cl_mem		ray;
	cl_mem		shape;
}				t_clbuf;

typedef struct	s_fps
{
	double			frames;
	struct timeval	start;
	struct timeval	end;
}				t_fps;

typedef struct	s_shape
{
	cl_float4 	type;
	cl_float4	pos;
	cl_float4	radius;
	cl_float4	color;
	cl_float4	axis;
}				t_shape;

typedef struct	s_camera
{
	cl_float4	origin;
	cl_float4	ray;
	cl_float4	down;
	cl_float4	right;
	cl_float	ratio;
}				t_camera;

typedef struct	s_scene
{
	t_camera	*cam;
	int			max_depth;
	int 		nb_shape;
	t_shape 	*shape;
	t_spot		*spot;
	int			nb_spot;
	t_mat		*mat;
	int			nb_mat;
}				t_scene;

typedef struct	s_img
{
	int			bpp;
	int			size_line;
	int			endian;
	void		*img;
	char		*data;
}				t_img;

typedef struct	s_inter
{
	int			id;
	float		dist;
	cl_float4	normal;
}				t_inter;

typedef struct	s_cam
{
	float		speed;
	float		sensitivity;
	float		theta;
	float		aspect_ratio;
	float		phi;
	cl_float4	pos;
	cl_float4	dir;
	cl_float4	target;
	cl_float4	forward;
	cl_float4	left;
	cl_float4	down;
	cl_int2		win_size;
	cl_int2		old_mouse_pos;
}				t_cam;

typedef struct	s_key
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			mleft;
	int			mright;
	int			mx;
	int			my;
	float		theta;
	float		phi;
}				t_key;

typedef struct	s_env
{
	cl_device_id		id;
	cl_context			context;
	cl_command_queue	cmds;
	cl_program			program;
	cl_kernel			kernel;
	t_clbuf				clbuf;
}				t_env;

typedef	struct	s_utils
{
	t_inter		inter;
	t_ray		ray;
	cl_float4	inter_pos;
}				t_utils;

typedef struct	s_map
{
	void		*mlx;
	void		*win;
	unsigned int multi_sampling;
	t_spot		current_spot;
	t_env		env;
	t_cam		free_cam;
	t_img		img;
	t_key		key;
	t_fps		fps;
	t_scene		scene;
	float		height;
	float		width;
}				t_map;

typedef struct	s_prog
{
	char		*buffer;
	size_t		len;
}				t_prog;

typedef struct	s_args
{
	t_map		*map;
	t_inter		*inter;
	t_ray		*ray;
}				t_args;

void	draw_pixel_to_image(t_map *map, int x, int y, int c);
void	draw(t_map *map);
void	ocl_init(t_env *env, t_prog prog);
t_prog	get_prog(char *file_name);
int		key_hook(int keycode, t_map *map);
int		loop_hook(t_map *map);
void	move(t_map *map);
void	rotate(t_map *map);
void	init_key(t_map *map);
int		key_press(int keycode, t_map *map);
cl_float4	sub_vec(cl_float4 v1, cl_float4 v2);
cl_float4	add_vec(cl_float4 v1, cl_float4 v2);
cl_float4	mult_vec(cl_float4 v1, cl_float4 v2);
cl_float4	cross_vec(cl_float4 v1, cl_float4 v2);
double	len_vec(cl_float4 v1);
cl_float4	scale_vec(double fact, cl_float4 v1);
void	normalize_vec(cl_float4 *v1);
double	docl_float4(cl_float4 v1, cl_float4 v2);
double	dis_point(cl_float4 pt1, cl_float4 pt2);
cl_float4	neg_vec(cl_float4 vec);
void	vector_from_angle(t_cam *cam);
void	update_cam(t_cam *cam, t_key *key);
void	init_cam(t_map *map);
int		color_mul(int color, float coef);
int		color_add(int c1, int c2);
cl_float4	get_inter_pos(t_ray ray, t_inter inter);
void	raytrace(t_map *map);
int		*shade(t_map *map, t_inter *inter, t_ray *ray);
//void	shade(t_args *args);

t_ray	*get_primary(t_map *map);

void	init_inter(t_map *map, size_t work_size);
t_inter	*get_inter(t_map *map, size_t work_size, t_ray *ray);

int		*shadow(t_map *map, t_inter *inter, t_ray *primary);

int		motion_notify(int x, int y, t_map *map);
void	write_bitmap(t_map *map);

int		ft_strsearch(char *str1, char *str2);
t_shape	*parse(t_map *map, char *file);
float	atoi_double(char *line);
void	get_sphere(int fd, t_shape *shape);
void	get_plane(int fd, t_shape *shape);
void	get_ellipsoid(int fd, t_shape *shape);
void	get_cylinder(int fd, t_shape *shape);
void	get_cone(int fd, t_shape *shape);
cl_float4	get_position(char *line);
cl_float4	get_vector(char *line);
cl_float4	get_rgb(char *line);
cl_float4	get_radius(char *line);
int		get_number(char *file, char *shape_name);
int		get_nb_shape(char *file);
void	get_window(int fd, t_map *map);
void	get_spotlight(int fd, t_map *map);
void	get_multi_sampling(int fd, t_map *map);
void	get_triangle(int fd, t_shape *shape);
void	get_cube(int fd, t_shape *shape);
void	get_cercle(int fd, t_shape *shape);

#endif
