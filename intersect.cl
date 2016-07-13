typedef struct	s_ray
{
	float4		origin;
	float4		dir;
}				t_ray;

typedef struct s_shape
{
	float4		type;
	float4		pos;
	float4		radius;
	float4		color;
	float4		axis;
	float4		axe_decoupe;
	int			mat_id;
}				t_shape;

typedef struct	s_inter
{
	int			id;
	float		dist;
	float4		normal;
	t_ray		from;
	int			in_shape;
}				t_inter;

static void swap(float *a, float *b)
{
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

bool intersect_disque(t_ray *ray, t_shape obj, float *t)
{
	float4 diff;
	float4 pt;
	float t1 = -(dot(obj.radius, ray->origin - obj.pos) / dot(obj.radius, ray->dir));
	if (t1 < 0)
		return 0;
	pt = ray->origin + t1 * ray->dir;
	diff = pt - obj.pos;
	if (sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) <= obj.axis.x)
	{
		t[0] = t1;
		t[1] = 0;
		return 1;
	}
	return 0;
}

bool intersect_plan_eq(t_ray *ray, t_shape obj, float *t)
{
	float t1;

	t1 = -ray->origin.x / (ray->dir.x - 5);
	if (t1 < 0)
		return (0);
	return (1);
}

bool intersect_triangle(t_ray *ray, t_shape obj, float *tada)
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
		return (0);
	inv_det = 1 / det;
	T = ray->origin - pt1;
	u = dot(T, P) * inv_det;
	if (u < 0.0f || u > 1.0f)
		return (0);
	Q = cross(T, e1);
	v = dot(ray->dir, Q) * inv_det;
	if (v < 0.0f || u + v > 1.0f)
		return (0);
	t = dot(e2, Q) * inv_det;
	if (t > 0.00001)
	{
		tada[0] = t;
		tada[1] = 0;
		return (1);
	}
	return 0;
}

bool intersect_sph(t_ray *ray, t_shape sph, float *t)
{
	float4 x = ray->origin - sph.pos;
	float a = dot(ray->dir, ray->dir);
	float b = 2.0f * (dot(ray->dir, x));
	float c = (dot(x, x)) - (sph.radius.x * sph.radius.x);
	float d = (b * b) - (4.0f * a * c);
	if (d < 0.0f)
		return (0);
	d = sqrt(d);
	float t1 = (-b + d) / (2.0f * a);
	float t2 = (-b - d) / (2.0f * a);
	t[0] = t1;
	t[1] = t2;
	if (t2 >= 0.0f && t2 < t1)
	{
		t[0] = t2;
		t[1] = t1;
		t1 = t2;
	}
	if (t1 < 0.0f)
		return (0);
	return (1);
}

bool intersect_plan(t_ray *ray, t_shape obj, float *t)
{
	float t1 = -(dot(obj.radius, ray->origin - obj.pos)
				  / dot(obj.radius, ray->dir));
	if (t1 < 0.0f)
		return 0;
	t[0] = t1;
	t[1] = 0;
	return (1);
}

bool intersect_cyl(t_ray *ray, t_shape cyl, float *t)
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
		return (0);
	d = sqrt(d);
	float t1 = (-b + d) / (2.0f * a);
	float t2 = (-b - d) / (2.0f * a);
	t[0] = t1;
	t[1] = t2;
	if (t2 >= 0.0f && t2 < t1)
	{
		t[0] = t2;
		t[1] = t1;
		t1 = t2;
	}
	if (t1 < 0.0f)
		return (0);
	return (1);
}

bool intersect_ellips(t_ray *ray, t_shape e)
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

bool intersect_cone(t_ray *ray, t_shape cyl, float *t)
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
		return (0);
	d = sqrt(d);
	float t1 = (-b + d) / (2.0f * a);
	float t2 = (-b - d) / (2.0f * a);
	t[0] = t1;
	t[1] = t2;
	if (t2 >= 0.0f && t2 < t1)
	{
		t[0] = t2;
		t[1] = t1;
		t1 = t2;
	}
	if (t1 < 0.0f)
		return (0);
	return (1);
}

static	float4 get_intersection(t_ray *ray, float t1)
{
	float4 inter;
	inter = ray->origin + (ray->dir * t1);
	inter.w = 0.0f;
	return (inter);
}

static float4 get_normal_cone(t_shape cone, t_ray ray, float t, float *sol)
{
	float m = (dot(ray.dir, cone.axis) * t) +
		dot(ray.origin - cone.pos, cone.axis);
	float4 norm;

	norm = (ray.dir * t) + (ray.origin - cone.pos) -
		(1.0f + cone.radius * cone.radius) * (cone.axis * m);
	if ((sol[0] > 0 && sol[1] < 0) || (sol[1] > 0 && sol[0] < 0))
		return (-norm);
	return (norm);
}

static float4 get_normal_sphere(t_shape obj, float4 inter, float *sol)
{
	float4 norm;

	norm = inter - obj.pos;
	if ((sol[0] > 0 && sol[1] < 0) || (sol[1] > 0 && sol[0] < 0))
		return (-norm);
	return(norm);
}

static float4 get_normal_plan(t_shape obj, float4 inter)
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

static float4 get_normal_cyl(t_shape cyl, float4 inter, float t, t_ray ray, float *sol)
{
	float4 norm;
	float m;

	m = dot(ray.dir, cyl.axis) * t + dot(ray.origin - cyl.pos, cyl.axis);
	norm = (ray.dir * t) + (ray.origin - cyl.pos) - (cyl.axis * m);
	if ((sol[0] > 0 && sol[1] < 0) || (sol[1] > 0 && sol[0] < 0))
		return (-norm);
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

static float4 get_normal(t_shape obj, float4 inter_pt, t_inter *inter, t_ray ray, float *sol)
{
	float4 norm;

	if ((sol[0] >= 0 && sol[1] < 0) || (sol[1] >= 0 && sol[0] < 0))
		inter->in_shape = 1;
	else
		inter->in_shape = 0;
	if (obj.type.x == 1.0f)
		norm = get_normal_sphere(obj, inter_pt, sol);
	if (obj.type.x == 2.0f)
		norm = get_normal_plan(obj, inter_pt);
	if (obj.type.x == 3.0f)
		norm = get_normal_cyl(obj, inter_pt, inter->dist, ray, sol);
	if (obj.type.x == 4.0f)
		norm = get_normal_cone(obj, ray, inter->dist, sol);
	if (obj.type.x == 5.0f)
		norm = get_normal_ellips(obj, inter_pt);
	norm = fast_normalize(norm);
	return (norm);
}
void	copy_tab(float *dst, float *src, int len)
{
	int count;

	count = 0;
	while (count < len)
	{
		dst[count] = src[count];
		count++;
	}
}

int	cut_obj(t_shape shape, t_ray *ray, float *end, int type)
{
	float tplan;
	float m;
	float4 dir_perp;

	if (type == 1.0f)
	{
		tplan= -(dot(shape.axe_decoupe, ray->origin - shape.pos)
				/ dot(shape.axe_decoupe, ray->dir));
		if (dot(shape.axe_decoupe, (ray->origin + end[0] * ray->dir) - shape.pos) > 0.0f)
		{
			if (tplan < 0)
			{
				end[0] = -1;
				return 0;
			}
			else if ((tplan > end[0] && tplan < end[1] && end[1] > 0))
			{
					end[0] = tplan;
					end[2] = 1;
					return 1;
			}
			else
			{
					end[0] = -1;
					return 0;
			}
		}
	}
	else
	{
		m = dot(ray->dir, shape.axis) * end[0] + dot(ray->origin - shape.pos, shape.axis);
		dir_perp = normalize(cross(shape.axe_decoupe, shape.axis));
		tplan= -(dot(dir_perp, ray->origin - shape.pos)
				/ dot(dir_perp, ray->dir));
		if (dot(dir_perp, (ray->origin + end[0] * ray->dir) - shape.pos) > 0.0f)
		{
			if (tplan < 0)
			{
				end[0] = -1;
				end[1] = -1;
				return 0;
			}
			else if ((tplan > end[0] && tplan < end[1] && end[1] > 0))
			{
					end[0] = tplan;
					end[2] = 1;
					return 1;
			}
			else
			{
					end[0] = -1;
					return 0;
			}
		}
	}
	return 0;
}

static int intersect_all(t_ray *ray,
		__global t_shape *shape, int num_shapes, float *t1, float *sol)
{
	int	i;
	int	j;
	int	k;
	float	tmp;
	float	save[3];
	float	end[3];
	float	tplan;


	i = 0;
	j = -1;
	k = -1;
	while (i < num_shapes)
	{
		end[0] = -1;
		end[1] = 0;
		end[2] = 0;
		save[0] = 0;
		save[1] = 0;
		save[2] = 0;
		if (shape[i].type.x == 1.0f && intersect_sph(ray, shape[i], save))
			copy_tab(end, save, 3);
		if (shape[i].type.x == 2.0f && intersect_plan(ray, shape[i], save))
			copy_tab(end, save, 3);
		if (shape[i].type.x == 3.0f && intersect_cyl(ray, shape[i], save))
			copy_tab(end, save, 3);
		if (shape[i].type.x == 4.0f && intersect_cone(ray, shape[i], save))
			copy_tab(end, save, 3);
		//if (shape[i].type.x == 5.0f && intersect_ellips(ray, shape[i]))
		//	tmp = sol[0];
		if (shape[i].type.x == 7.0f && intersect_disque(ray, shape[i], save))
			copy_tab(end, save, 3);
		if (shape[i].type.x == 8.0f && intersect_triangle(ray, shape[i], save))
			copy_tab(end, save, 3);
		if (fast_length(shape[i].axe_decoupe) != 0 && end[0] != -1)
		{
			cut_obj(shape[i], ray, end, (int)shape[i].axe_decoupe.w);
		}
			tmp = end[0];
		if (tmp != -1.0f && (*t1 == -1.0f || tmp < *t1))
		{
			*t1 = tmp;
			j = i;
			copy_tab(sol, end, 3);
		}
		i++;
	}
	if (j != -1 && shape[j].type.y > 0 && (sol[0] > 0 || sol[1] > 0))
	{
		ray->origin = ray->origin + (fmax(sol[1], sol[0]) + 0.005f) * ray->dir;
		sol[0] = -1;
		sol[1] = 0;
		sol[2] = 0;
		*t1 = -1;
		return (intersect_all(ray, shape, num_shapes, t1, sol));
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
	float	sol[3];
	sol[0] = 0;
	sol[1] = 0;
	sol[2] = 0;

	global_addr = get_global_id(0);

	r = ray[global_addr];
	//printf("%f %f %f\n", r.dir.x, r.dir.y, r.dir.z);
	inter.dist = -1.0f;
	inter.normal = (float4)(0.0f, 0.0f, 0.0f ,0.0f);
	if (fast_length(r.dir) != 0.0f)
	{
		inter.id = intersect_all(&r, shape, num_shapes, &inter.dist, sol);
		if (inter.id != -1)
		{
			sh = shape[inter.id];
			if (sol[2] != -1.0) // WTF ?
			{
				inter.normal = get_normal(sh, get_intersection(&r, inter.dist),
							&inter, r, sol);
			}
			else if (sh.axe_decoupe.w)
			{
				inter.normal = normalize(cross(sh.axe_decoupe, sh.axis));
				inter.in_shape = 0;
			}
			else
				inter.normal = sh.axe_decoupe;
			inter.from = r;
		}
	}
	else
		inter.id = -1;
	out[global_addr] = inter;
}
