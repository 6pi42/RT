typedef struct s_sphere
{
	float4		type;
	float4		pos;
	float4		radius;
	float4		color;
}				t_sphere;

typedef struct	s_ray
{
	float4		origin;
	float4		dir;
}				t_ray;

static float4 vec_sub(float4 a, float4 b)
{
	float4 c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = 0.0;
	return (c);
}

static float to_rad(float a)
{
		return (a * M_PI / 180.0);
}

static float intersect_sph(t_ray *ray, t_sphere sph)
{
	//printf("sphere pos %f %f %f\n", sph->pos.x, sph->pos.y, sph->pos.z);
	//printf("sphere col %f %f %f\n", sph->color.x, sph->color.y, sph->color.z);
	//printf("sphere radius %f\n", sph->radius.x);

	float a = dot(ray->dir, ray->dir);
	float b = 2.0 * (dot(ray->dir, vec_sub(ray->origin, sph.pos)));
	float c = (dot(vec_sub(ray->origin, sph.pos),
			 vec_sub(ray->origin, sph.pos))) -
			(sph.radius.x * sph.radius.x);
	float d = (b * b) - (4.0 * a * c);
	if (d >= 0.0)
	{
		float t1 = (-b + sqrt(d)) / (2 * a);
		float t2 = (-b - sqrt(d)) / (2 * a);
		if (t2 >= 0 && t2 < t1)
			t1 = t2;
		if (t1 < 0)
			return (-1.0);
		//printf("%f\n", t1);
		return (t1);
	}
	else
		return ((float)-1.0);
}

static float intersect_plan(t_ray *ray, t_sphere obj)
{
	float t1 = -(dot(obj.radius, vec_sub(ray->origin, obj.pos)) / dot(obj.radius, ray->dir));
	return (t1 < 0.0 ? -1.0 : t1);
}

static float4 init_float4(float a, float b, float c, float d)
{
	float4 z;

	z.x = a;
	z.y = b;
	z.z = c;
	z.w = d;
	return (z);
}

static t_sphere cpy_struct(t_sphere sph)
{
	t_sphere	obj;

	obj.pos = init_float4(sph.pos.x, sph.pos.y, sph.pos.z, 0.0);
	obj.radius = init_float4(sph.radius.x, sph.radius.y, sph.radius.z, 0.0);
	obj.color = init_float4(sph.color.x, sph.color.y, sph.color.z, 0.0);
	obj.type = init_float4(sph.type.x, 0.0, 0.0, 0.0);
	return (obj);
}

static	float4 get_intersection(t_ray *ray, float t1)
{
	float4 inter;

	inter.x = ray->origin.x + (ray->dir.x * t1);
	inter.y = ray->origin.y + (ray->dir.y * t1);
	inter.z = ray->origin.z + (ray->dir.z * t1);
	inter.w = 0.0;
	return (inter);
}

static float4 get_normal_sphere(t_sphere obj, float4 inter)
{
	float4 norm;

	norm.x = inter.x - obj.pos.x;
	norm.y = inter.y - obj.pos.y;
	norm.z = inter.z - obj.pos.z;
	norm.w = 0.0;
	norm = normalize(norm);
	return(norm);
}

static float4 get_normal_plan(t_sphere obj)
{
	float4 norm;

	norm.x = obj.radius.x;
	norm.y = obj.radius.y;
	norm.z = obj.radius.z;
	norm.w = 0.0;
	norm = normalize(norm);
	return(norm);
}

static float4 get_normal(t_sphere obj, float4 inter)
{
	float4 norm;

	if (obj.type.x == 1)
		norm = get_normal_sphere(obj, inter);
	if (obj.type.x == 2)
		norm = get_normal_plan(obj);
	return (norm);
}

static float4 diffuse_lighting(float4 spot, float4 norm, float4 inter,
								float4 color)
{
	float4	light;
	float	angle;

	light.x = spot.x - inter.x;
	light.y = spot.y - inter.y;
	light.z = spot.z - inter.z;
	light.w = 0;
	light = normalize(light);
	angle = fmax((float)0.0, (float)dot(light, norm));;
	color.x *= angle;
	color.y *= angle;
	color.z *= angle;
	color.x = color.x > 0xFF ? 0xFF : color.x;
	color.y = color.y > 0xFF ? 0xFF : color.y;
	color.z = color.z > 0xFF ? 0xFF : color.z;
	color.w = 0.0;
	return (color);
}

static float4 raytrace(t_ray *ray, __global t_sphere *sph, uint num_spheres,
									__global t_sphere *plan, uint num_plans)
{
	float4 		color;
	float		t1;
	uint		i;
	float		tmp;
	t_sphere	obj;
	float4		norm;
	float4		inter;
	float4		spot;

	spot = init_float4(0.0, 100.0, 0.0, 0.0);
	i = 0;
	t1 = -1.0;
	color = init_float4(0.0, 0.0, 0.0, 0.0);
	while (i < num_spheres)
	{
		tmp = intersect_sph(ray, sph[i]);
		if (tmp != -1.0 && (t1 == -1.0 || tmp < t1))
		{
			t1 = tmp;
			obj = cpy_struct(sph[i]);
			color = sph[i].color;
		}
		i++;
	}
	i = 0;
	while (i < num_plans)
	{
		tmp = intersect_plan(ray, plan[i]);
		if (tmp != -1.0 && (t1 == -1.0 || tmp < t1))
		{
			t1 = tmp;
			obj = cpy_struct(plan[i]);
			color = plan[i].color;
		}
		i++;
	}
	if (t1 != -1.0)
	{
		inter = get_intersection(ray, t1);
		norm = get_normal(obj, inter);
		color = diffuse_lighting(spot, norm, inter, color);
	}
	return (color);
}

__kernel void generate_ray(__global float4* data, uint height, uint width,
							__global t_ray* cam,
							__global t_sphere* spheres, uint num_spheres,
							__global t_sphere* plans, uint num_plans)
{
	t_ray r;
	t_ray tmp;
	float4 color;
	float w = (float)width;
	float h = (float)height;
	float global_id = (float)get_global_id(0);
	r.origin = init_float4(cam->origin.x, cam->origin.y, cam->origin.z, 0.0);
	r.dir.x = (float)(fmod(global_id, w) - (w / 2.0));
	r.dir.y = (float)(h - ((global_id) / w)) - (h / 2.0);
	r.dir.z = (float)(-(w / (2.0 * tan((50.0 / 2.0) * M_PI / 180.0))));
	r.dir.w = 0.0;
	tmp = ray;
	ray.dir.x = tmp.origin.x * cos(to_rad(cam->dir.z)) - tmp.origin.y * sin(to_rad(cam->dir.z));
	ray.dir.y = tmp.origin.x * sin(to_rad(cam->dir..z)) + tmp.origin.y * cos(to_rad(cam->dir.z));
	tmp = ray;
	ray.dir.y = tmp.origin.y * cos(to_rad(cam->dir.x)) - tmp.origin.z * sin(to_rad(cam->dir.x));
	ray.dir.z = tmp.origin.y * sin(to_rad(cam->dir.x)) + tmp.origin.z * cos(to_rad(cam->dir.x));
	tmp = ray;
	ray.dir.z = tmp.origin.z * cos(to_rad(cam->dir.y)) - tmp.origin.x * sin(to_rad(cam->dir.y));
	ray.dir.x = tmp.origin.z * sin(to_rad(cam->dir.y)) + tmp.origin.x * cos(to_rad(cam->dir.y));
	r.dir = normalize(r.dir);
	color = raytrace(&r, spheres, num_spheres, plans, num_plans);
	data[get_global_id(0)] = color;
}
