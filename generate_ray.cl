typedef struct	s_img
{
	int		bpp;
	int		size_line;
	int		endian;
	void	*img;
	char	*data;

}				t_img;

typedef struct	s_mat
{
	float4		ka;
	float4		kd;
	float4		ks;
	float4		kr;
}				t_mat;

typedef struct s_sphere
{
	float4		type;
	float4		pos;
	float4		radius;
	float4		color;
	float4		axis;
}				t_sphere;

typedef struct	s_ray
{
	float4		origin;
	float4		dir;
	float4		down;
	float4		right;
	float		ratio;
}				t_ray;

static float4	clamp_color(float4 color)
{
	color.x = color.x > 0xFF ? 0xFF : color.x;
	color.y = color.y > 0xFF ? 0xFF : color.y;
	color.z = color.z > 0xFF ? 0xFF : color.z;
	return (color);
}

static float diffuse_lighting(float4 spot, float4 norm, float4 inter)
{
	float4	light;
	float	angle;

	light = fast_normalize(spot - inter);
	light = spot - inter;
	light = fast_normalize(light);
	angle = fmax(0.0f, dot(light, norm));;
	return (angle);
}

static float	spec_lighting(float4 spot, float4 norm, float4 inter, t_ray ray)
{
	float4	eye;
	float4	light;
	float4	halfvec;
	float	coef;

	eye = fast_normalize(ray.origin - inter);
	light = fast_normalize(spot - inter);
	halfvec = fast_normalize(eye + light);
	coef = pow(fmax(0.0f, dot(halfvec, norm)), 42.0f);
	return (coef);
	eye = ray.origin - inter;
	eye = fast_normalize(eye);
	light = spot - inter;
	light = fast_normalize(light);
	if (dot(light, norm) > 0.0f)
	{
		halfvec = eye + light;
		halfvec = fast_normalize(halfvec);
		coef = fmax(0.0f, dot(halfvec, norm));
		coef = pow(coef, 42.0f);
		return (coef);
	}
	return (0.0f);
}

static float intersect_sph(t_ray *ray, t_sphere sph)
{
	float4 x = ray->origin - sph.pos;
	float a = dot(ray->dir, ray->dir);
	float b = 2.0f * (dot(ray->dir, x));
	float c = (dot(x, x)) - (sph.radius.x * sph.radius.x);
	float d = (b * b) - (4.0f * a * c);
	if (d < 0.0f || a == 0.0f || b == 0.0f || c == 0.0f)
		return (-1.0f);
	d = sqrt(d);
	float t1 = (-b + d) / (2.0f * a);
	float t2 = (-b - d) / (2.0f * a);
	if (t2 >= 0.0f && t2 < t1)
		t1 = t2;
	if (t1 < 0.0f)
		return (-1.0f);
	return (t1);
}

static float intersect_plan(t_ray *ray, t_sphere obj)
{
	float t1 = -(dot(obj.radius, ray->origin - obj.pos)
				  / dot(obj.radius, ray->dir));
	return (t1 < 0.0f ? -1.0f : t1);
}

static float intersect_cyl(t_ray *ray, t_sphere cyl)
{
	float dir_axis = dot(ray->dir, cyl.axis);
	float4 x = ray->origin - cyl.pos;
	float a = dot(ray->dir, ray->dir) - dir_axis * dir_axis;
	float b = 2.0f * (dot(ray->dir, x) - (dir_axis *
		dot(ray->origin - cyl.pos, cyl.axis)));
	float c = dot(x, x) - (dot(x, cyl.axis) * dot(x, cyl.axis)) -
		cyl.radius.x * cyl.radius.x;
	float d = (b * b) - (4.0f * a * c);
	if (d < 0.0f || a == 0.0f || b == 0.0f || c == 0.0f)
		return (-1.0f);
	d = sqrt(d);
	float t1 = (-b + d) / (2.0f * a);
	float t2 = (-b - d) / (2.0f * a);
	if (t2 >= 0.0f && t2 < t1)
		t1 = t2;
	if (t1 < 0.0f)
		return (-1.0f);
	return (t1);
}

static float intersect_ellips(t_ray *ray, t_sphere e)
{
	float4 v = (ray->origin - e.pos);
	float a = ((ray->dir.x * ray->dir.x) / (e.radius.x * e.radius.x))
		+ ((ray->dir.y * ray->dir.y) / (e.radius.y * e.radius.y))
		+ ((ray->dir.z * ray->dir.z) / (e.radius.z * e.radius.z));
	float b = ((2.0f * v.x * ray->dir.x) / (e.radius.x * e.radius.x))
		+ ((2.0f * v.y * ray->dir.y) / (e.radius.y * e.radius.y))
		+ ((2.0f * v.z * ray->dir.z) / (e.radius.z * e.radius.z));
	float c = (v.x * v.x) / (e.radius.x * e.radius.x)
		+ (v.y * v.y) / (e.radius.y * e.radius.y)
		+ (v.z * v.z) / (e.radius.z * e.radius.z) - 1.0f;
	float d = (b * b) - (4 * a * c);
	if (d < 0.0f || a == 0.0f || b == 0.0f || c == 0.0f)
		return (-1.0f);
	d = sqrt(d);
	float t1 = (-b + d) / (2.0f * a);
	float t2 = (-b - d) / (2.0f * a);
	if (t1 <= 0.0f && t2 <= 0.0f)
		return (-1.0f);
	e.radius.w = (t1 <= 0.0f || t2 <= 0.0f);
	if (t2 >= 0.0f && t2 < t1)
		t1 = t2;
	if (t1 < 0.0f)
		return (-1.0f);
	return (t1);
}

static float intersect_cone(t_ray *ray, t_sphere cyl)
{
	float4 x = ray->origin - cyl.pos;
	float dir_axis = dot(ray->dir, cyl.axis);
	float x_axis = dot(x, cyl.axis);
	float k = (1.0f + cyl.radius.x * cyl.radius.x);
	float a = dot(ray->dir, ray->dir) - k * dir_axis *
		dir_axis;
	float b = 2.0f * ((dot(ray->dir, x) - k * dir_axis *
		x_axis));
	float c = dot(x, x) - k * (x_axis * x_axis);
	float d = (b * b) - (4.0f * a * c);
	if (d < 0.0f || a == 0.0f || b == 0.0f || c == 0.0f)
		return (-1.0f);
	d = sqrt(d);
	float t1 = (-b + d) / (2.0f * a);
	float t2 = (-b - d) / (2.0f * a);
	if (t2 >= 0.0f && t2 < t1)
		t1 = t2;
	if (t1 < 0.0f)
		return (-1.0f);
	if (t1 != t1)
		return (-1.0f);
	return (t1);
}

static	float4 get_intersection(t_ray *ray, float t1)
{
	float4 inter;
	inter = ray->origin + (ray->dir * t1);
	return (inter);
}

static float4 get_normal_cone(t_sphere cone, t_ray ray, float t)
{
	float m = (dot(ray.dir, cone.axis) * t) +
		dot(ray.origin - cone.pos, cone.axis);
	float4 norm;

	norm = (ray.dir * t) + (ray.origin - cone.pos) -
		(1.0f + cone.radius * cone.radius) * (cone.axis * m);
	return (norm);
}

static float4 get_normal_sphere(t_sphere obj, float4 inter)
{
	float4 norm;

	norm = inter - obj.pos;
	return(norm);
}

static float4 get_normal_plan(t_sphere obj)
{
	return(obj.radius);
}

static float4 get_normal_ellips(t_sphere ellips, float4 inter)
{
	float4 tmp;
	float4 norm;

	tmp = inter - ellips.pos;
	norm = 2.0f * tmp;
	norm /= (ellips.radius * ellips.radius);
	norm.w = 0.0f;
	norm *= ellips.radius.w ? -1.0f : 1.0f;
	return (norm);
}

static float4 get_normal_cyl(t_sphere cyl, float4 inter, float t, t_ray ray)
{
	float4 norm;
	float m;

	m = dot(ray.dir, cyl.axis) * t + dot(ray.origin - cyl.pos, cyl.axis);
	norm = (ray.dir * t) + (ray.origin - cyl.pos) - (cyl.axis * m);
	return (norm);
}

static float4 get_normal(t_sphere obj, float4 inter, float t1, t_ray ray)
{
	float4 norm;

	if (obj.type.x == 1.0f)
		norm = get_normal_sphere(obj, inter);
	if (obj.type.x == 2.0f)
		norm = get_normal_plan(obj);
	if (obj.type.x == 3.0f)
		norm = get_normal_cyl(obj, inter, t1, ray);
	if (obj.type.x == 4.0f)
		norm = get_normal_cone(obj, ray, t1);
	if (obj.type.x == 5.0f)
		norm = get_normal_ellips(obj, inter);
	norm = fast_normalize(norm);
	return (norm);
}

static uint intersect_all(t_ray *ray,
		__constant t_sphere *shape, uint num_shapes, float *t1)
{
	uint	i;
	uint	j;
	float	tmp;

	i = 0;
	j = -1;
	while (i < num_shapes)
	{
		if (shape[i].type.x == 1.0f)
			tmp = intersect_sph(ray, shape[i]);
		if (shape[i].type.x == 2.0f)
			tmp = intersect_plan(ray, shape[i]);
		if (shape[i].type.x == 3.0f)
			tmp = intersect_cyl(ray, shape[i]);
		if (shape[i].type.x == 4.0f)
			tmp = intersect_cone(ray, shape[i]);
		if (shape[i].type.x == 5.0f)
			tmp = intersect_ellips(ray, shape[i]);
		if (tmp != -1.0f && (*t1 == -1.0f || tmp < *t1))
		{
			*t1 = tmp;
			j = i;
		}
		i++;
	}
	return (j);
}

static float4 get_color(t_sphere obj, float4 spot, float4 norm,
								 float4 inter, float4 color, t_ray ray)
{
	float4 ambient;
	float4 diffuse;
	float4 spec;
	float4 lightcolor;
	t_mat mat;

	mat.kd = 0.6f;
	mat.ka = 0.2f;
	mat.ks = 0.8f;
	lightcolor = (float4)(255.0f, 255.0f, 255.0f, 255.0f);
	spec = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	ambient = (color * mat.ka);
	if (obj.type.x != 2.0f)
		spec = lightcolor * (spec_lighting(spot, norm, inter, ray) * mat.ks);
	diffuse = color * (diffuse_lighting(spot, norm, inter) * mat.kd);
	color = ambient + spec + diffuse;
	color = clamp_color(color);
	return (color);
}

static float4 shadow_color(float4 color)
{
	color *= 0.2f;
	return (color);
}

static	float4	reflect(t_ray *ray, __constant t_sphere *shape, uint num_shapes,
		__constant int *tex)
{
	float4 		color;
	float		t1;
	float4		norm;
	float4		inter;
	float4		spot;
	uint id;

	spot = (float4)(500.0f, 200.0f, 0.0f, 0.0f);
	t1 = -1.0f;
	color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	id = intersect_all(ray, shape, num_shapes, &t1);
	if (t1 > 0.0f)
	{
		color = shape[id].color;
		inter = get_intersection(ray, t1);
		if (id == 3)
		{

			int n = (abs((int)inter.y) % tex[0]) * tex[1] + (int)(abs((int)inter.x) % 64) + (int)2;
			if (n < tex[0] * tex[1])
			{
				color.x = (float)((tex[n] & 0xFF0000) >> 16);
				color.y = (float)((tex[n] & 0xFF00) >> 8);
				color.z = (float)((tex[n] & 0xFF));
			}
		}
		if (id == 4 || id == 5)
		{
			int jump = ((int)inter.x / (int)shape[id].pos.x + (int)inter.y / (int)shape[id].pos.y) % 2;
			if (jump)
				color = (float4)(255.0f, 255.0f, 255.0f, 0.0f);
			else
				color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
		}
		norm = get_normal(shape[id], inter, t1, *ray);
		color = get_color(shape[id], spot, norm, inter, color, *ray);
	}
	return (color);
}

static int get_shadow(float4 inter, float4 spot, __constant t_sphere *shape,
					uint num_shapes, uint id)
{
	t_ray tmp;
	uint id2;
	float t;

	t = -1.0f;
	tmp.origin = spot;
	tmp.dir = fast_normalize(inter - spot);
	id2 = intersect_all(&tmp, shape, num_shapes, &t);
	return (id2 != id);

}

static float4 raytrace(t_ray *ray, __constant t_sphere *shape, uint num_shapes,
		__constant int *tex)
{
	float4 		color;
	float		t1;
	uint		i;
	t_ray tmp;
	float4		norm;
	float4		inter;
	float4		spot;
	uint id;

	spot = (float4)(-50.0f, 100.0f, 0.0f, 0.0f);
	i = 0;
	t1 = -1.0f;
	id = intersect_all(ray, shape, num_shapes, &t1);
	color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	if (t1 > 0.0f)
	{
		color = shape[id].color;
		inter = get_intersection(ray, t1);
		norm = get_normal(shape[id], inter, t1, *ray);
		if (id == 3)
		{
			int n = (abs((int)inter.y) % tex[0]) * tex[1] + (int)(abs((int)inter.x) % 64) + (int)2;
			if (n < tex[0] * tex[1])
			{
				color.x = (float)((tex[n] & 0xFF0000) >> 16);
				color.y = (float)((tex[n] & 0xFF00) >> 8);
				color.z = (float)((tex[n] & 0xFF));
			}
		}
		if (id == 4 || id == 5)
		{
			int jump = ((int)inter.x / (int)shape[id].pos.x + (int)inter.y / (int)shape[id].pos.y) % 2;
			if (jump)
				color = (float4)(255.0f, 255.0f, 255.0f, 0.0f);
			else
				color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
		}
		color = get_color(shape[id], spot, norm, inter, color, *ray);
		if (get_shadow(inter, spot, shape, num_shapes, id))
				color = shadow_color(color);
		tmp.origin = get_intersection(ray, t1 - 0.001f);
		tmp.dir = ray->dir - 2.0f * (dot(norm, ray->dir)) * norm;
		color = (color + 0.2f * reflect(&tmp, shape, num_shapes, tex));

		color = clamp_color(color);
	}
	return (color);
}

static	float4	get_dir(float4 dir, float4 down, float4 right,
						float x, float y, float width, float height,
						float aspect_ratio)
{
	t_ray ray;
	float4 vp_right;
	float4 vp_down;
	float xamnt;
	float yamnt;

	xamnt = ((x + 0.5f) / width) * aspect_ratio
		- (((width - height) / height) / 2.0f);
	yamnt = ((height - y) + 0.5f) / height;
	vp_down = (yamnt - 0.5f) * down;
	vp_right = (xamnt - 0.5f) * right;
	ray.dir = (vp_right + vp_down) + dir;
	ray.dir = fast_normalize(ray.dir);
	return (ray.dir);
}

static	float4	moy_rgb(float4 *color, uint len)
{
	uint i = 0;
	float4 tmp;

	tmp = (float4)(0.0f,0.0f,0.0f,0.0f);
	while (i < len)
	{
		tmp.x += color[i].x;
		tmp.z += color[i].z;
		tmp.y += color[i].y;
		i++;
	}
	tmp = tmp / (float)i;
	return (tmp);
}

__kernel void generate_ray(__global char* data, float height, float width,
							__global t_ray* cam,
							__constant t_sphere *shape, uint num_shapes,
							__constant t_img *img, __constant int *tex)
{
	t_ray r;
	float4 color[4];
	float4 tmp;
	float w = width;
	float h = height;
	float id;
	float x;
	float y;

/*
	int   xi = get_global_id(0) % (int)width;
	int   yi = get_global_id(0) / (int)width;
*/
	id = get_global_id(0);
	y = id / width;
	x = fmod(id, width);
	r.origin = (float4)(cam->origin.x, cam->origin.y, cam->origin.z, 0.0f);
	r.dir = get_dir(cam->dir, cam->down, cam->right, x, y, w, h, cam->ratio);
	color[0] = raytrace(&r, shape, num_shapes, tex);
	//r.dir = get_dir(cam->dir, cam->down, cam->right, x + 0.5, y, w, h, cam->ratio);
	//color[1] = raytrace(&r, shape, num_shapes);
	//r.dir = get_dir(cam->dir, cam->down, cam->right, x, y + 0.5, w, h, cam->ratio);
	//color[2] = raytrace(&r, shape, num_shapes);
	//r.dir = get_dir(cam->dir, cam->down, cam->right, x + 0.5, y + 0.5, w, h, cam->ratio);
	//color[3] = raytrace(&r, shape, num_shapes);
	tmp = moy_rgb(color, 1);
/*
	data[(yi * img->size_line) + (xi * 32) / 8] =
			(uchar)((int)(color.z) & 0xFF);
	data[(yi * img->size_line) + (xi * 32) / 8 + 1] =
			(uchar)((int)(color.y) & 0xFF);
	data[(yi * img->size_line) + (xi * 32) / 8 + 2] =
			(uchar)((int)(color.x) & 0xFF);
*/
	data[(int)y * img->size_line + ((int)x * img->bpp) / 8] =
			(uchar)((int)(tmp.z) & 0xFF);
	data[(int)y * img->size_line + ((int)x * img->bpp) / 8 + 1] =
			(uchar)((int)(tmp.y) & 0xFF);
	data[(int)y * img->size_line + ((int)x * img->bpp) / 8 + 2] =
			(uchar)((int)(tmp.x) & 0xFF);
}
