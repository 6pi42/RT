typedef struct s_sphere
{
	float4		pos;
	float4		radius;
	float4		color;
}				t_sphere;

typedef struct	s_ray
{
	float4		origin;
	float4		dir;
}				t_ray;

static float	dot3(float3 a, float3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static float4 vec_sub(float4 a, float4 b)
{
	float4 c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = 0.0;
	return (c);
}

static int	intersect_sph(t_ray *ray, t_sphere sph)
{
	//printf("sphere pos %f %f %f\n", sph->pos.x, sph->pos.y, sph->pos.z);	
	//printf("sphere col %f %f %f\n", sph->color.x, sph->color.y, sph->color.z);
	//printf("sphere radius %f\n", sph->radius.x);

	float a = dot(ray->dir, ray->dir);
	float b = 2.0 * (dot(ray->dir, vec_sub(ray->origin, sph.pos)));
	float c = (dot(vec_sub(ray->origin, sph.pos),
			 vec_sub(ray->origin, sph.pos))) -
			(sph.radius.x * sph.radius.x);
	float d = (b * b) - (4 * a * c);
	if (d >= 0.0)
	{
		float t1 = (-b + sqrt(b)) / (2 * a);
		float t2 = (-b - sqrt(b)) / (2 * a);
		if (t2 >= 0 && t2 < t1)
			t1 = t2;
		if (t1 < 0)
			return (-1);
		return (t1);
	}
	else
		return (-1);
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


static float4 raytrace(t_ray *ray, __global t_sphere *sph, uint num_spheres)
{
	float4 	color;
	int		t;
	uint	i;
	int		tmp;

	i = 0;
	tmp = -1;
	color = init_float4(0.0, 0.0, 0.0, 0.0);
	while (i < num_spheres)
	{
		t = intersect_sph(ray, sph[i]);
		if (t != -1 && t > tmp)
		{
			t = tmp;
			color = sph[i].color;
		}
		i++;
	}
	return (color);
}

__kernel void generate_ray(__global float4* data, uint height, uint width,
							__global t_sphere* spheres, uint num_spheres) {	
	t_ray r;
	uint i;
	float4 color;
	//t_sphere sph;
	r.origin.x = 0.0;
	r.origin.y = 0.0;
	r.origin.z = 200.0;
	r.origin.w = 0.0;
	//sph = get_sphere(spheres, num_spheres, 0);
	//printf("sphere pos %f %f %f\n", spheres->pos.x, spheres->pos.y, spheres->pos.z);
	r.dir.x = (float)(get_global_id(0) % width - (float)(width / 2));
	r.dir.y = (float)(height-(get_global_id(0) / width)) - (float)(height / 2);
	r.dir.z = -((float)width / (float)(2 * tan((50 / 2) * M_PI / 180)));
	r.dir = normalize(r.dir);
	color = raytrace(&r, spheres, num_spheres);	
	data[get_global_id(0)] = color;
}
