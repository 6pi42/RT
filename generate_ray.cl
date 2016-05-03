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
	short		multi;
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

static float4 get_texture(t_sphere shape, float4 inter, float4 norm)
{
    float4 color;

    color = shape.color;
    if (shape.type.x == 1.0f)
    {
        int jump = ((int)shape.pos.x / (int)inter.x + (int)shape.pos.y / (int)inter.y) % (int)2;
        if (jump)
            color = shape.color;
        else
        {
            color.x = shape.color.y;
            color.y = shape.color.z;
            color.z = shape.color.x;
        }
    }
    else if (shape.type.x == 5.0f)
    {
        int jump = ((int)shape.pos.y / (int)inter.y) % (int)2;
        if (jump)
            color = shape.color;
        else
        {
            color.x = shape.color.y;
            color.y = shape.color.z;
            color.z = shape.color.x;
        }
    }
    else if (shape.type.x == 2.0f)
    {
        int jump = ((int)inter.x + (int)inter.y + (int)inter.z) % (int)2;
        if (jump)
            color = shape.color;
        else
        {
            color.x = shape.color.y;
            color.y = shape.color.z;
            color.z = shape.color.x;
        }
    }
    else
    {
        int jump = ((int)norm.x / (int)inter.x +
            (int)norm.y / (int)inter.y + (int)norm.z / (int)inter.z) % (int)2;
        if (jump)
            color = shape.color;
        else
        {
            color.x = shape.color.y;
            color.y = shape.color.z;
            color.z = shape.color.x;
        }
    }
    return (color);
}

static void swap(float *a, float *b)
{
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

static float intersect_cube(t_ray *ray, t_sphere obj)
{
	float tmin = (obj.radius.x - ray->origin.x) / ray->dir.x;
	float tmax = (obj.pos.x - ray->origin.x) / ray->dir.x;
	if (tmin > tmax)
		swap(&tmin, &tmax);
	float tymin = (obj.radius.y - ray->origin.y) / ray->dir.y;
	float tymax = (obj.pos.y - ray->origin.y) / ray->dir.y;
	if (tymin > tymax)
		swap(&tymin, &tymax);
	if ((tmin > tymax) || (tymin > tmax))
		return -1;
	tmin = fmax(tymin, tmin);
	tmax = fmin(tymax, tmax);
	float tzmin = (obj.radius.z - ray->origin.z) / ray->dir.z;
	float tzmax = (obj.pos.z - ray->origin.z) / ray->dir.z;
	if (tzmin > tzmax)
		swap(&tzmin, &tzmax);
	if ((tmin > tzmax) || (tzmin > tmax) || tmin <= 0)
		return -1;
	tmin = fmin(tzmin, tmin);
	return (tmin);
}


static float intersect_disque(t_ray *ray, t_sphere obj)
{
	float4 diff;
	float4 pt;
	float t1 = -(dot(obj.radius, ray->origin - obj.pos) / dot(obj.radius, ray->dir));
	if (t1 < 0)
		return -1;
	pt = ray->origin + t1 * ray->dir;
	diff = pt - obj.pos;
	if (sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) <= obj.axis.x)
		return t1;
	return -1;
}

static float intersect_plan_eq(t_ray *ray, t_sphere obj)
{
	float t1, t2, t3;

	t1 = -ray->origin.x / (ray->dir.x - 5);
	if (t1 < 0)
		return (-1);
	return (t1);
	return (-1);
}

static float intersect_triangle(t_ray *ray, t_sphere obj)
{
	float4 pt1, pt2, pt3; // 3 vertex
	float4 e1, e2; // 2 edge (autour de pt1)
	float4 P, Q, T;
	
	float det, inv_det, u, v, t;

	pt1 = obj.pos;
	pt2 = obj.radius;
	pt3 = obj.axis;
	e1 = pt2 - pt1;
	e2 = pt3 - pt1;
	P = cross(ray->dir, e2);
	det = dot(e1, P);
	if (det > -0.00001 && det < 0.00001)
		return (-1);
	inv_det = 1 / det;
	T = ray->origin - pt1;
	u = dot(T, P) * inv_det;
	if (u < 0.0f || u > 1.0f)
		return (-1);
	Q = cross(T, e1);
	v = dot(ray->dir, Q) * inv_det;
	if (v < 0.0f || u + v > 1.0f)
		return (-1);
	t = dot(e2, Q) * inv_det;
	if (t > 0.00001)
		return (t);
	return -1;
}

static float intersect_sph(t_ray *ray, t_sphere sph)
{
	float4 x = ray->origin - sph.pos;
	float a = dot(ray->dir, ray->dir);
	float b = 2.0f * (dot(ray->dir, x));
	float c = (dot(x, x)) - (sph.radius.x * sph.radius.x);
	float d = (b * b) - (4.0f * a * c);
	if (d < 0.0f)
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
	if (d < 0.0f)
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
	float t = 0.0f;
	if (t1 <= 0.0f)
		t = t2;
	else
	{
		if (t2 <= 0.0f)
			t = t1;
		else
			t = (t1 < t2) ? t1 : t2;
	}
	if (t < 0.0f)
		return (-1.0f);
	return (t);
}

static float intersect_cone(t_ray *ray, t_sphere cyl)
{
	float4 x = ray->origin - cyl.pos;
	float dir_axis = dot(ray->dir, cyl.axis);
	float x_axis = dot(x, cyl.axis);
	float k = (1.0f + cyl.radius.x * cyl.radius.x);
	float a = dot(ray->dir, ray->dir) - k * dir_axis *
		dir_axis;
	float b = 2.0f * (dot(ray->dir, x) - k * dir_axis *
		x_axis);
	float c = dot(x, x) - k * (x_axis * x_axis);
	float d = (b * b) - (4.0f * a * c);
	if (d < 0.0f)
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

static	float4 get_intersection(t_ray *ray, float t1)
{
	float4 inter;
	inter = ray->origin + (ray->dir * t1);
	inter.w = 0.0f;
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
static float4 get_normal_cube(t_sphere cyl, float4 inter)
{
	float4 norm;
	norm.x = 1;
	norm.y = 0;
	norm.z = 0;
	norm.w = 0;
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
	if (obj.type.x == 6.0f)
		norm = get_normal_cube(obj, inter);
	if (obj.type.x == 7.0f)
		norm = get_normal_plan(obj);
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
		if (shape[i].type.x == 6.0)
			tmp = intersect_cube(ray, shape[i]);
		if (shape[i].type.x == 7.0)
			tmp = intersect_disque(ray, shape[i]);
		if (shape[i].type.x == 8.0)
			tmp = intersect_triangle(ray, shape[i]);
		if (shape[i].type.x == 99.0)
			tmp = intersect_plan_eq(ray, shape[i]);
		if (tmp != -1.0f && (*t1 == -1.0f || tmp < *t1))
		{
			*t1 = tmp;
			j = i;
		}
		i++;
	}
	return (j);
}

static float4 get_color(float4 color, float4 spot, float4 norm,
								 float4 inter, t_ray ray, uint id)
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
	if (id != (uint)2)
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

static	float4	reflect(t_ray *ray, __constant t_sphere *shape, uint num_shapes)
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
		if (shape[id].type.y)
			color = get_texture(shape[id], inter, norm);
		norm = get_normal(shape[id], inter, t1, *ray);
		color = get_color(color, spot, norm, inter, *ray, id);
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

static float4 raytrace(t_ray *ray, __constant t_sphere *shape, uint num_shapes)
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
	color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	id = intersect_all(ray, shape, num_shapes, &t1);
	if (t1 > 0.0f)
	{
		color = shape[id].color;
		inter = get_intersection(ray, t1);
		norm = get_normal(shape[id], inter, t1, *ray);
		if (shape[id].type.y)
			color = get_texture(shape[id], inter, norm);
		color = get_color(color, spot, norm, inter, *ray, id);
		if (get_shadow(inter, spot, shape, num_shapes, id))
				color = shadow_color(color);
		tmp.origin = get_intersection(ray, t1 - 0.001f);
		tmp.dir = ray->dir - 2.0f * (dot(norm, ray->dir)) * norm;
		color = (color + 0.2f * reflect(&tmp, shape, num_shapes));
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

static float4	get_value(int i, int x, int y)
{
	float4 vec;

	if (i == 3)
		vec.x = x + 1.00f;
	else if (i == 6 || i == 7)
		vec.x = x + 0.75f;
	else if (i == 1 || i == 2)
		vec.x = x + 0.50f;
	else if (i == 4 || i == 5)
		vec.x = x + 0.25f;
	else
		vec.x = x;
	if (i == 2)
		vec.y = y + 1.00f;
	else if (i == 5 || i == 7)
		vec.y = y + 0.75f;
	else if (i == 0 || i == 3)
		vec.y = y + 0.50f;
	else if (i == 4 || i == 6)
		vec.y = y + 0.25f;
	else
		vec.y = y;
	return (vec);
}

static float4 moy_rgb(float4 *color, short len)
{
	short i = 0;
	float4 tmp;
	tmp = (0.0f, 0.0f, 0.0f, 0.0f);
	while (i < len)
	{
		tmp.x += color[i].x;
		tmp.y += color[i].y;
		tmp.z += color[i].z;
		i++;
	}
	tmp /= (float)i;
	return (tmp);
}

__kernel void generate_ray(__global char* data, float height, float width,
							__global t_ray* cam,
							__constant t_sphere *shape, uint num_shapes,
							__constant t_img *img, const short multi)
{
	t_ray r;
	float4 color[2];
	float id;
	float x;
	float y;
	short	i;

	i = 0;
	id = get_global_id(0);
	y = id / width;
	x = fmod(id, width);
	r.origin = (float4)(cam->origin.x, cam->origin.y, cam->origin.z, 0.0f);
	if (multi)
	{
		while (i < multi)
		{
			r.dir = get_dir(cam->dir, cam->down, cam->right, get_value((int)i, x, y).x,
				get_value((int)i, x, y).y, width, height, cam->ratio);
			color[i] = raytrace(&r, shape, num_shapes);
			i++;
		}
		color[0] = moy_rgb(color, multi);
	}
	else
	{
		r.dir = get_dir(cam->dir, cam->down, cam->right, x,
		y, width, height, cam->ratio);
		color[0] = raytrace(&r, shape, num_shapes);
	}
	data[(int)y * img->size_line + ((int)x * img->bpp) / 8] =
		(uchar)((int)(color[0].z) & 0xFF);
	data[(int)y * img->size_line + ((int)x * img->bpp) / 8 + 1] =
		(uchar)((int)(color[0].y) & 0xFF);
	data[(int)y * img->size_line + ((int)x * img->bpp) / 8 + 2] =
		(uchar)((int)(color[0].x) & 0xFF);
}
