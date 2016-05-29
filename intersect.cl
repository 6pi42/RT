typedef struct s_shape
{
	float4		type;
	float4		pos;
	float4		radius;
	float4		color;
	float4		axis;
}				t_shape;

typedef struct	s_inter
{
	int			id;
	float		dist;
	float4		normal;
}				t_inter;

typedef struct	s_ray
{
	float4		origin;
	float4		dir;
}				t_ray;

static void swap(float *a, float *b)
{
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

static float intersect_cube(t_ray *ray, t_shape obj)
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

static float intersect_disque(t_ray *ray, t_shape obj)
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

static float intersect_plan_eq(t_ray *ray, t_shape obj)
{
	float t1;

	t1 = -ray->origin.x / (ray->dir.x - 5);
	if (t1 < 0)
		return (-1);
	return (t1);
}

static float intersect_triangle(t_ray *ray, t_shape obj)
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

static float intersect_sph(t_ray *ray, t_shape sph)
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

static float intersect_plan(t_ray *ray, t_shape obj)
{
	float t1 = -(dot(obj.radius, ray->origin - obj.pos)
				  / dot(obj.radius, ray->dir));
	return (t1 < 0.0f ? -1.0f : t1);
}

static float intersect_cyl(t_ray *ray, t_shape cyl)
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

static float intersect_ellips(t_ray *ray, t_shape e)
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

static float intersect_cone(t_ray *ray, t_shape cyl)
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

static float4 get_normal_cone(t_shape cone, t_ray ray, float t)
{
	float m = (dot(ray.dir, cone.axis) * t) +
		dot(ray.origin - cone.pos, cone.axis);
	float4 norm;

	norm = (ray.dir * t) + (ray.origin - cone.pos) -
		(1.0f + cone.radius * cone.radius) * (cone.axis * m);
	return (norm);
}

static float4 get_normal_sphere(t_shape obj, float4 inter)
{
	float4 norm;

	norm = inter - obj.pos;
	return(norm);
}

static float4 get_normal_plan(t_shape obj)
{
	return(obj.radius);
}

static float4 get_normal_ellips(t_shape ellips, float4 inter)
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

static float4 get_normal_cyl(t_shape cyl, float4 inter, float t, t_ray ray)
{
	float4 norm;
	float m;

	m = dot(ray.dir, cyl.axis) * t + dot(ray.origin - cyl.pos, cyl.axis);
	norm = (ray.dir * t) + (ray.origin - cyl.pos) - (cyl.axis * m);
	return (norm);
}
static float4 get_normal_cube(t_shape cyl, float4 inter)
{
	float4 norm;
	norm.x = 1;
	norm.y = 0;
	norm.z = 0;
	norm.w = 0;
	return (norm);
}

static float4 get_normal(t_shape obj, float4 inter, float t1, t_ray ray)
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

static int intersect_all(t_ray *ray,
		__global t_shape *shape, int num_shapes, float *t1)
{
	int	i;
	int	j;
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
		if (shape[i].type.x == 6.0f)
			tmp = intersect_cube(ray, shape[i]);
		if (shape[i].type.x == 7.0f)
			tmp = intersect_disque(ray, shape[i]);
		if (shape[i].type.x == 8.0f)
			tmp = intersect_triangle(ray, shape[i]);
		if (shape[i].type.x == 99.0f)
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

__kernel void intersect(__global t_inter *out, __global t_ray* ray,
						__global t_shape *shape, int num_shapes)
{
	t_ray	r;
	t_shape sh;
	t_inter	inter;
	int		global_addr;
	int		id;

	global_addr = get_global_id(0);

	r = ray[global_addr];
	inter.dist = -1.0f;
	inter.id = intersect_all(&r, shape, num_shapes, &inter.dist);
	sh = shape[inter.id];
	inter.normal = get_normal(sh, get_intersection(&r, inter.dist),
							inter.dist, r);
	out[global_addr] = inter;
}
