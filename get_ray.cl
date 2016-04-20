typedef struct	s_shape
{
	float4		type;
	float4		pos;
	float4		radius;
	float4		color;
	float4		axis;
}				t_shape;

typedef	struct	s_ray
{
	float4		origin;
	float4		dir;
}				t_ray;

typedef struct	s_mat
{
	float		ka;
	float		ks;
	float		kd;
}				t_mat;

typedef struct	s_cam
{
	float4		origin;
	float4		dir;
	float4		down;
	float4		right;
	float		ratio;
}				t_cam;

static float diffuse(float4 spot, float4 norm, float4 inter)
{
	float4 light;
	float d_intensity;

	//printf("spot: %f %f %f %f\n", spot.x, spot.y, spot.z, spot.w);
	//printf("norm: %f %f %f %f\n", norm.x, norm.y, norm.z, norm.w);
	//printf("inter: %f %f %f %f\n", inter.x, inter.y, inter.z, inter.w);
	light = spot - inter;
	light = fast_normalize(light);
	d_intensity = fmax(0.0f, dot(light, norm));
	if(d_intensity != 0.0f)
		printf("d: %f\n", d_intensity);
	return (d_intensity);
}

static float specular(float4 spot, float4 norm, float4 inter, t_ray ray)
{
	float4 eye;
	float4 light;
	float4 halfvec;
	float s_intensity;

	eye = fast_normalize(ray.origin - inter);
	light = fast_normalize(spot - inter);
	halfvec = fast_normalize(eye + light);
	s_intensity = fmax(0.0f, dot(halfvec, norm));
	s_intensity = pow(s_intensity, 42.0f);
	return (s_intensity);
}

static float4 get_color(t_shape obj, float4 spot, float4 norm,
								float4 inter, float4 color, t_ray ray)
{
	float4 ambient;
	float4 dif;
	float4 spec;
	float4 lightcolor;
	float4 c;
	t_mat mat;

	mat.kd = 0.6f;
	mat.ka = 0.2f;
	mat.ks = 0.8f;
	c = obj.color;
	lightcolor = (float4)(255.0f, 255.0f, 255.0f, 255.0f);
	spec = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	ambient = (c * mat.ka);
	spec = lightcolor * (specular(spot, norm, inter, ray) * mat.ks);
	dif = c * (diffuse(spot, norm, inter) * mat.kd);
	color = ambient + spec + dif;
	//color.x = color.x > 0xFF ? 0xFF : color.x;
	//color.y = color.y > 0xFF ? 0xFF : color.y;
	//color.z = color.z > 0xFF ? 0xFF : color.z;
	return (color);
}

static float4 get_normal_sphere(t_shape obj, float4 inter)
{
	return (inter - obj.pos);
}

static float4 get_normal(t_shape obj, float4 inter, t_ray ray)
{
	float4 norm;

	if (obj.type.x == 1.0f)
		norm = get_normal_sphere(obj, inter);
	norm = fast_normalize(norm);
	return (norm);
}

__kernel void get_shading(__global uchar4 *out,
							const uint h, const uint w,
							__global float2 *inter,
							__global float4 *rays, const float4 origin,
							__global t_shape *shape, int nb_shape)
{
	t_ray r;
	uint global_addr = get_global_id(0);
	float4 normal;
	float2 i;
	float4 inter_pos;
	uchar4 c = (uchar4)(0, 0, 0, 0);
	t_shape s;

	float4 spot = (float4)(-100.0f, 100.0f, 0.0f, 0.0f);
	i = inter[global_addr];
	r.dir = rays[global_addr]; //TODO: Replace by ID index
	r.origin = origin;
	inter_pos = r.origin + (r.dir * i.y);
	inter_pos.w = 0.0f;
	if (i.x != -1.0f)
	{
	s = shape[(int)i.x];
	normal = get_normal(s, inter_pos, r);
	float4 color = get_color(s, spot, normal, inter_pos, s.color, r);
	c.x = (uchar)((int)(color.x) & 0xFF);
	c.y = (uchar)((int)(color.y) & 0xFF);
	c.z = (uchar)((int)(color.z) & 0xFF);
	}
	out[global_addr] = c;
}

static float intersect_sph(t_ray ray, t_shape sph)
{
	float a = dot(ray.dir, ray.dir);
	float b = 2.0f * (dot(ray.dir, ray.origin - sph.pos));
	float c = (dot(ray.origin - sph.pos, ray.origin - sph.pos)) -
			(sph.radius.x * sph.radius.x);
	float d = (b * b) - (4.0f * a * c);
	if (d < 0.0f)
		return (-1.0f);
	float t1 = (-b + sqrt(d)) / (2.0f * a);
	float t2 = (-b - sqrt(d)) / (2.0f * a);
	if (t2 >= 0.0f && t2 < t1)
		t1 = t2;
	if (t1 < 0.0f)
		return (-1.0f);
	return (t1);
}
static int iter(t_ray ray, __global t_shape *shape, int nb, float *t)
{
	int i;
	int id;
	float tmp;
	
	i = 0;
	id = -1;
	tmp = -1.0f;
	while (i < nb)
	{
		if (shape[i].type.x == 1.0f)
			tmp = intersect_sph(ray, shape[i]);
		if (tmp != -1.0f && (*t == -1.0f || tmp < *t))
		{
			*t = tmp;
			id = i;
		}
		i++;
	}
	return (id);
}

static float2	raytrace(t_ray ray, __global t_shape *shape, int nb)
{
	float2	out;
	float	t;

	t = -1.0f;
	out.x = (int)iter(ray, shape, nb, &t);
	out.y = t;
	//remove useless cell from out
	return (out);
}

__kernel void	get_intersection(__global float2* out,
								const uint h, const uint w,
								__global float4 *ray, const float4 origin,
								__global t_shape* shape, int nb_shape)
{
	t_ray r;
	uint global_addr;

	global_addr = get_global_id(0);
	r.origin = origin;
	r.dir = ray[global_addr];
	out[get_global_id(0)] = raytrace(r, shape, nb_shape);
}


static	float4	get_dir(float4 dir, float4 down, float4 right,
				float x, float y, float width,
				float height, float aspect_ratio)
{
	t_ray ray;
	float4 vp_right;
	float4 vp_down;
	float xamnt;
	float yamnt;

	xamnt = ((x + 0.5f) / width) * aspect_ratio -
				(((width - height) / height) / 2.0f);
	yamnt = ((height - y) + 0.5f) / height;
	vp_down = (yamnt - 0.5f) * down;
	vp_right = (xamnt - 0.5f) * right;
	ray.dir = (vp_right + vp_down) + dir;
	ray.dir = fast_normalize(ray.dir);
	return (ray.dir);
}

__kernel void get_ray(__global float4 *out, const uint h, const uint w,
						__global t_cam *cam)
{
	float4 ray;
	float id;
	float x;
	float y;
	float height = (float)h;
	float width = (float)w;

	id = (float)get_global_id(0);
	y = (int)id / (int)width;
	x = (float)fmod(id, width);
	ray = get_dir(cam->dir, cam->down, cam->right, x, y, width, height, cam->ratio);
	out[get_global_id(0)] = ray;
}
