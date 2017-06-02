/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_photon.cu                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 15:50:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/02 15:16:36 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "photon_mapping.h"
#include "rt.cuh"
#include <curand.h>
#include <curand_kernel.h>

__device__
static void		save_photon(t_photon *photon_list, t_ray *ray, t_object *obj);
__device__
static float 	get_probability(float *p, t_vec3 o_col, float k, t_vec3 p_col);
__device__
static void		redirect_photon_diffuse(t_raytracing_tools *r, t_ray *ray);
__device__
static void		redirect_photon_specular(t_raytracing_tools *r, t_ray *ray);
__device__
static void		redirect_photon_transmit(t_raytracing_tools *r, t_ray *ray);
__device__
static int		fresnel_reflect(t_raytracing_tools *r, t_ray *ray);
__device__
static void		get_iors(float *n1, float *n2, t_raytracing_tools *r, t_ray *ray);
__device__
static void		scale_color(t_ray *ray, float p, float k, t_vec3 obj_col);

//put scale_color in redirect_... functions
__device__
t_color			update_photon(t_raytracing_tools *r, t_ray *ray)
{
	float	rand_f;
	float	tmp;
	float 	p;
	
	
	// printf("update_photon: type: [%d],  diffuse: [%f], reflection: [%f], transparency: [%f]\n",
	// ray->type,
	// r->scene->objects[ray->hit_obj].kd,
	// r->scene->objects[ray->hit_obj].reflection,
	// r->scene->objects[ray->hit_obj].transparency);
	
	if (r->scene->objects[ray->hit_obj].kd > 0.0 /*&& ray->type == R_DIRECT_PHOTON*/)
		save_photon(r->scene->photon_list + r->idx * PHOTON_BOUNCE_MAX, ray, &r->scene->objects[ray->hit_obj]);
	rand_f = curand_uniform(r->devStates);
	tmp = 0;
	p = NAN;
	ray->type = R_INDIRECT_PHOTON;
	// printf("update photon: rand_f: [%f]\n", rand_f);
	if ((tmp += get_probability(&p, r->scene->objects[ray->hit_obj].col, r->scene->objects[ray->hit_obj].kd / 3.0, col_to_vec(ray->col))) > rand_f)
	{
		// printf("[%d] cast as diffuse. Rand: [%f] tmp: [%f]\n", r->idx, rand_f, tmp);
		redirect_photon_diffuse(r, ray);
		scale_color(ray, p, r->scene->objects[ray->hit_obj].kd, r->scene->objects[ray->hit_obj].col);
		// printf("new dir: [%f, %f, %f]\n", ray->dir.x, ray->dir.y, ray->dir.z);
	}
	else if ((tmp += get_probability(&p, r->scene->objects[ray->hit_obj].col, r->scene->objects[ray->hit_obj].reflection / 3.0, col_to_vec(ray->col))) > rand_f)
	{
		// printf("[%d] cast as reflection. Rand: [%f] tmp: [%f]\n", r->idx, rand_f, tmp);
		redirect_photon_specular(r, ray);
		scale_color(ray, p, r->scene->objects[ray->hit_obj].reflection, r->scene->objects[ray->hit_obj].col);
	}
	else if ((tmp += get_probability(&p, r->scene->objects[ray->hit_obj].col, r->scene->objects[ray->hit_obj].transparency / 3.0, col_to_vec(ray->col))) > rand_f)
	{
		if (fresnel_reflect(r, ray))
		{
			// printf("[%d] cast as reflection due to fresnel. Rand: [%f] tmp: [%f]\n", r->idx, rand_f, tmp);
			redirect_photon_specular(r, ray);
			scale_color(ray, p, r->scene->objects[ray->hit_obj].reflection, r->scene->objects[ray->hit_obj].col);
		}
		else
		{
			// printf("[%d] cast as refraction. Rand: [%f] tmp: [%f]\n", r->idx, rand_f, tmp);
			redirect_photon_transmit(r, ray);
			scale_color(ray, p, r->scene->objects[ray->hit_obj].transparency, r->scene->objects[ray->hit_obj].col);
		}
	} 
	else
	{
		// printf("[%d] absorbed. Rand: [%f] tmp: [%f]\n", r->idx, rand_f, tmp);
		return (c_new(0, 0, 0));
	}
	// if energy high enough, shoot photon again: cast_primary_ray();
	if ((ray->col.r + ray->col.g + ray->col.b) > 10)
		return (cast_primary_ray(r, ray));
	else
		return (c_new(0, 0, 0));
	// printf("------cast again with type[%d]\n", ray->type);
}

__device__
static void		save_photon(t_photon *photon_list, t_ray *ray, t_object *obj)
{
	int i;

	i = 0;           
	// printf("0: [%f] - 1: [%f] - 3: [%f] - 3: [%f] - \n", photon_list[0].pos.x, photon_list[1].pos.x, photon_list[2].pos.x, photon_list[3].pos.x);                               
	while (!v_isnan(photon_list[i].pos) && i < PHOTON_BOUNCE_MAX)
		++i;
	// printf("save photon: at %d [%f, %f, %f]\n", i, photon_list[i].pos.x, photon_list[i].pos.y, photon_list[i].pos.z);
	// printf("found: [%d]: [%f, %f, %f]\n", i, photon_list[i].pos.x, photon_list[i].pos.y, photon_list[i].pos.z);
	photon_list[i].pos = ray->hit;
	photon_list[i].dir = ray->dir;
	photon_list[i].col = vec_to_col(get_object_color(obj, ray));
	photon_list[i].n = v_scale(ray->nhit, ray->n_dir);
	// printf("save photon[%d]: pos: [%f, %f, %f] dir: [%f, %f, %f] col: [%d, %d, %d]\n", i,
		// photon_list[i].pos.x, photon_list[i].pos.y, photon_list[i].pos.z,
		// photon_list[i].dir.x, photon_list[i].dir.y, photon_list[i].dir.z,
		// photon_list[i].col.r, photon_list[i].col.g, photon_list[i].col.b);
}

__device__
static float 	get_probability(float *p, t_vec3 o_col, float k, t_vec3 p_col)
{
	*p = (max(o_col.x * p_col.x, max(o_col.y * p_col.y, o_col.z * p_col.z)) * k / 255) / 
	max(p_col.x, max(p_col.y, p_col.z)); 
	return (*p);
}

__device__
static void			redirect_photon_diffuse(t_raytracing_tools *r, t_ray *ray)
{
	t_vec3	rand_dir;
	curandState state;
	ray->origin = v_add(ray->hit, v_scale(ray->nhit, ray->n_dir * BIAS));

	state = *r->devStates;
	rand_dir.x = ray->dir.x * (curand_uniform(&state) - 0.5);
	rand_dir.y = ray->dir.y * (curand_uniform(&state) - 0.5);
	rand_dir.z = ray->dir.z * (curand_uniform(&state) - 0.5);
	*r->devStates = state;
	rand_dir = v_norm(rand_dir);
	ray->dir = (v_dot(rand_dir, v_scale(ray->nhit, ray->n_dir)) < 0) ? v_scale(rand_dir, -1): rand_dir;
}

__device__
static void			redirect_photon_specular(t_raytracing_tools *r, t_ray *ray)
{
	ray->origin = v_add(ray->hit, v_scale(ray->nhit, ray->n_dir * BIAS));
	ray->dir = reflect(ray->dir, v_scale(ray->nhit, ray->n_dir));
}

__device__
static void			redirect_photon_transmit(t_raytracing_tools *r, t_ray *ray)
{
	float n1;
	float n2;
	
	update_ior(&n1, &n2, r, ray);
	ray->ior = n2;
	ray->origin = v_add(ray->hit, v_scale(ray->nhit, -ray->n_dir * BIAS)); 
	ray->dir = refract(ray->dir, v_scale(ray->nhit, ray->n_dir), n1, n2);
}



/*
** ray: incoming ray.
** p: probability of particular redirection (diffuse, refelcted, refracted)
** k: coefficient of corresponding redirection (diffuse, reflection, transparency)
** obj_col: color of object hit
** P_refl = P_inc * k / p
*/

__device__
static void			scale_color(t_ray *ray, float p, float k, t_vec3 obj_col)
{
	t_color p_inc;

	// printf("scale color input: p: [%f] k : [%f]\n", p, k);
	p_inc = ray->col;
	ray->col.r = p_inc.r * k * (obj_col.x / (p * 255.0));
	ray->col.g = p_inc.g * k * (obj_col.y / (p * 255.0));
	ray->col.b = p_inc.b * k * (obj_col.z / (p * 255.0));
	// printf("scale color: old: [%d, %d, %d] new: [%d, %d, %d]\n", p_inc.r, p_inc.g, p_inc.b, ray->col.r, ray->col.g, ray->col.b);
}

__device__
static int			fresnel_reflect(t_raytracing_tools *r, t_ray *ray)
{
	float	n1;
	float 	n2;
	float	f;

	if (!r->scene->is_fresnel)
		return (0);
	get_iors(&n1, &n2, r, ray);
	f = get_fresnel_ratio(ray->dir, v_scale(ray->nhit, ray->n_dir), n1, n2);
	return (f > curand_uniform_double(r->devStates));
}



/*
** Same as update_ior function, but only to retrieve the iors, not to update the lists and ray iors.
*/

__device__
static void		get_iors(float *n1, float *n2, t_raytracing_tools *r, t_ray *ray)
{
		int	i;
	float ret;

	if (ray->n_dir == 1)
	{
		i = -1;
		*n1 = ray->ior;
		while (r->ior_list[++i] > 0.001);
		// r->ior_list[i] = r->scene->objects[ray->hit_obj].ior;
		*n2 = r->scene->objects[ray->hit_obj].ior;
	}
	else
	{
		i = r->scene->ray_depth;
		while (i >= 0)
		{
			ret = r->ior_list[i] - r->scene->objects[ray->hit_obj].ior;
			if (ret < 0.001 && ret > -0.001)
				break;
			--i;
		}
		if (!(ret < 0.001 && ret > -0.001))
		{
			*n1 = ray->ior;
			i = 0;
			while (r->ior_list[i] > 0.001)
				++i;
			*n2 = r->ior_list[i - 1];
			return ;
		}
		// r->ior_list[i] = 0;
		// while (i < r->scene->ray_depth && r->ior_list[i] < 0.001)
		// {
		// 	r->ior_list[i] = r->ior_list[i + 1];
		// 	r->ior_list[i + 1] = 0;
		// 	++i;
		// }
		i = 0;
		while (r->ior_list[i] > 0.001)
			++i;
		*n2 = r->ior_list[i - 1];
		*n1 = ray->ior;
	}
	i = -1;
}