typedef struct s_sphere
{
	float4		type;
	float4		pos;
	float4		radius;
	float4		color;
	float4		axis;
}				t_sphere;

typedef struct	s_mat
{
	float4		ka;
	float4		kd;
	float4		ks;
}				t_mat;

typedef struct	s_ray
{
	float4		origin;
	float4		dir;
}				t_ray;

static t_sphere cpy_struct(t_sphere sph)
{
	t_sphere	obj;
	obj.pos = (float4)(sph.pos.x, sph.pos.y, sph.pos.z, 0.0f);
	obj.radius = (float4)(sph.radius.x, sph.radius.y, sph.radius.z, 0.0f);
	obj.color = (float4)(sph.color.x, sph.color.y, sph.color.z, 0.0f);
	obj.type = (float4)(sph.type.x, 0.0f, 0.0f, 0.0f);
	obj.axis = (float4)(sph.axis.x, sph.axis.y, sph.axis.z, 0.0f);
	return (obj);
}

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

	light = spot - inter;
	light = normalize(light);
	angle = fmax((float)0.0f, (float)dot(light, norm));;
	return (angle);
}


static float	spec_lighting(float4 spot, float4 norm, float4 inter, t_ray ray)
{
	float4	eye;
	float4	light;
	float4	halfvec;
	float	coef;

	eye = ray.origin - inter;
	eye = normalize(eye);
	light = spot - inter;
	light = normalize(light);
	if (dot(light, norm) > 0.0f)
	{
		halfvec = eye + light;
		halfvec = normalize(halfvec);
		coef = fmax(0.0f, (float)dot(halfvec, norm));
		coef = pow((float)coef, (float)42.0f);
		return (coef);
	}
	return (0.0f);
}

static float intersect_sph(t_ray *ray, t_sphere sph)
{
	float a = dot(ray->dir, ray->dir);
	float b = 2.0f * (dot(ray->dir, ray->origin - sph.pos));
	float c = (dot(ray->origin - sph.pos, ray->origin - sph.pos)) -
			(sph.radius.x * sph.radius.x);
	float d = (b * b) - (4.0f * a * c);
	if (d >= 0.0f)
	{
		float t1 = (-b + sqrt(d)) / (2.0f * a);
		float t2 = (-b - sqrt(d)) / (2.0f * a);
		if (t2 >= 0.0f && t2 < t1)
			t1 = t2;
		if (t1 < 0.0f)
			return (-1.0f);
		return (t1);
	}
	else
		return (-1.0f);
}

static float intersect_plan(t_ray *ray, t_sphere obj)
{
	float t1 = -(dot(obj.radius, ray->origin - obj.pos) / dot(obj.radius, ray->dir));
	return (t1 < 0.0f ? -1.0f : t1);
}

static float intersect_cyl(t_ray *ray, t_sphere cyl)
{
	float a = dot(ray->dir, ray->dir) - dot(ray->dir, cyl.axis) * dot(ray->dir, cyl.axis);
	float b = 2.0f * (dot(ray->dir, ray->origin - cyl.pos) - (dot(ray->dir, cyl.axis) *
		dot(ray->origin - cyl.pos, cyl.axis)));
	float c = dot(ray->origin - cyl.pos, ray->origin - cyl.pos) -
		(dot(ray->origin - cyl.pos, cyl.axis) *
		dot(ray->origin - cyl.pos, cyl.axis)) -
		cyl.radius.x * cyl.radius.x;
	float d = (b * b) - (4.0f * a * c);
	if (d >= 0.0f)
	{
		float t1 = (-b + sqrt(d)) / (2.0f * a);
		float t2 = (-b - sqrt(d)) / (2.0f * a);
		if (t2 >= 0.0f && t2 < t1)
			t1 = t2;
		if (t1 < 0.0f)
			return (-1.0f);
		return (t1);
	}
	else
		return (-1.0f);
}

static float intersect_ellips(t_ray *ray, t_sphere ellips)
{
	/*float a = (ray->dir.x * ray->dir.x) / (ellips.radius.x * ellips.radius.x)
			+ (ray->dir.y * ray->dir.y) / (ellips.radius.y * ellips.radius.y)
			+ (ray->dir.z * ray->dir.z) / (ellips.radius.z * ellips.radius.z);
	float b = ((2.0f * ellips.pos.x * ray->dir.x) / (ellips.radius.x * ellips.radius.x))
			+ ((2.0f * ellips.pos.y * ray->dir.y) / (ellips.radius.y * ellips.radius.y))
			+ ((2.0f * ellips.pos.z * ray->dir.z) / (ellips.radius.z * ellips.radius.z));
	float c = ((ellips.pos.x * ellips.pos.x) / (ellips.radius.x * ellips.radius.x))
				+ ((ellips.pos.y * ellips.pos.y) / (ellips.radius.y * ellips.radius.y))
				+ ((ellips.pos.z * ellips.pos.z) / (ellips.radius.z * ellips.radius.z));
	float d = (b * b) + 4.0f * a * c;
	if (d >= 0.0f)
	{
		float t1 = (-b + sqrt(d)) / (2.0f * a);
		float t2 = (-b - sqrt(d)) / (2.0f * a);
		if (t2 >= 0.0f && t2 < t1)
			t1 = t2;
		if (t1 < 0.0f)
			return (-1.0f);
		return (t1);
	}
	else */
		return (-1.0f);
}

static float intersect_cone(t_ray *ray, t_sphere cyl)
{
	float k = (1.0f + cyl.radius.x * cyl.radius.x);
	float a = dot(ray->dir, ray->dir) - k * dot(ray->dir, cyl.axis) *
		dot(ray->dir, cyl.axis);
	float b = 2.0f * (dot(ray->dir, ray->origin - cyl.pos) - k * (dot(ray->dir, cyl.axis) *
		dot(ray->origin - cyl.pos, cyl.axis)));
	float c = dot(ray->origin - cyl.pos, ray->origin - cyl.pos) -
		k * (dot(ray->origin - cyl.pos, cyl.axis) *
		dot(ray->origin - cyl.pos, cyl.axis)) -
		cyl.radius.x * cyl.radius.x;
	float d = (b * b) - (4.0f * a * c);
	if (d >= 0.0f)
	{
		float t1 = (-b + sqrt(d)) / (2.0f * a);
		float t2 = (-b - sqrt(d)) / (2.0f * a);
		if (t2 >= 0.0f && t2 < t1)
			t1 = t2;
		if (t1 < 0.0f)
			return (-1.0f);
		return (t1);
	}
	else
		return (-1.0f);
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
	norm = normalize(norm);
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
	norm = 2.0f * norm;
	norm /= ellips.radius * ellips.radius;
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
	norm = normalize(norm);
	return (norm);
}

static t_sphere intersect_all(t_ray *ray,
		__global t_sphere *shape, uint num_shapes,
									float *t1)
{
	uint	i;
	uint	j;
	t_sphere obj;
	float	tmp;

	i = 0;
	while (i < num_shapes)
	{
		if (shape[i].type.x == 1.0)
			tmp = intersect_sph(ray, shape[i]);
		if (shape[i].type.x == 2.0)
			tmp = intersect_plan(ray, shape[i]);
		if (shape[i].type.x == 3.0)
			tmp = intersect_cyl(ray, shape[i]);
		if (shape[i].type.x == 4.0)
			tmp = intersect_cone(ray, shape[i]);
		if (shape[i].type.x == 5.0)
			tmp = intersect_ellips(ray, shape[i]);
		if (tmp != -1.0f && (*t1 == -1.0f || tmp < *t1))
		{
			*t1 = tmp;
			j = i;
		}
		i++;
	}
	if (*t1 != -1.0f)
		obj = cpy_struct(shape[j]);
	return (obj);
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
	ambient = (obj.color * mat.ka);
	if (obj.type.x != 2.0f)
		spec = lightcolor * (spec_lighting(spot, norm, inter, ray) * mat.ks);
	diffuse = obj.color* (diffuse_lighting(spot, norm, inter) * mat.kd);
	color = ambient + spec + diffuse;
	color = clamp_color(color);
	return (color);
}

static float4 raytrace(t_ray *ray, __global t_sphere *shape, uint num_shapes)
{
	float4 		color;
	float		t1;
	uint		i;
	t_sphere	obj;
	float4		norm;
	float4		inter;
	float4		spot;

	spot = (float4)(-100.0f, 100.0f, 0.0f, 0.0f);
	i = 0;
	t1 = -1.0f;
	color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	obj = intersect_all(ray, shape, num_shapes, &t1);
	if (t1 > 0.0f)
	{
		inter = get_intersection(ray, t1);
		norm = get_normal(obj, inter, t1, *ray);
		color = get_color(obj, spot, norm, inter, color, *ray);
	}
	return (color);
}

__kernel void generate_ray(__global float4* data, uint height, uint width,
							__global t_ray* cam,
							__global t_sphere *shape, uint num_shapes)
{
	t_ray r;
	t_ray tmp;
	float4 color;
	float rad = M_PI / 180.0f;
	float w = (float)width;
	float h = (float)height;
	float global_id = (float)get_global_id(0);
	r.origin = (float4)(cam->origin.x, cam->origin.y, cam->origin.z, 0.0f);
	r.dir.x = (float)(fmod(global_id, w) - (w / 2.0f));
	r.dir.y = (float)(h - ((global_id) / w)) - (h / 2.0f);
	r.dir.z = (float)(-(w / (2.0f * 0.466307f)));
	r.dir.w = 0.0f;
	/*tmp = r;
	r.dir.x = tmp.dir.x * cos(rad * cam->dir.z) - tmp.dir.y * sin(rad * cam->dir.z);
	r.dir.y = tmp.dir.x * sin(rad * cam->dir.z) + tmp.dir.y * cos(rad * cam->dir.z);
	tmp = r;
	r.dir.y = tmp.dir.y * cos(rad * cam->dir.x) - tmp.dir.z * sin(rad * cam->dir.x);
	r.dir.z = tmp.dir.y * sin(rad * cam->dir.x) + tmp.dir.z * cos(rad * cam->dir.x);
	tmp = r;
	r.dir.z = tmp.dir.z * cos(rad * cam->dir.y) - tmp.dir.x * sin(rad * cam->dir.y);
	r.dir.x = tmp.dir.z * sin(rad * cam->dir.y) + tmp.dir.x * cos(rad * cam->dir.y);
	*/r.dir = normalize(r.dir);
	color = raytrace(&r, shape, num_shapes);
	data[get_global_id(0)] = color;
}
