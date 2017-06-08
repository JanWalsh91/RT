/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_photon.cu                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 16:00:41 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include <curand.h>
#include <curand_kernel.h>

__device__
static void		scale_color(t_ray *ray, float p, float k, t_vec3 obj_col);

__device__
void			redirect_photon_diffuse(t_raytracing_tools *r, t_ray *ray, float p)
{
	t_vec3	rand_dir;
	curandState state;
	ray->origin = v_add(ray->hit, v_scale(ray->nhit, ray->n_dir * BIAS));
	state = *r->devStates;
	rand_dir.x = r->rand_list[(r->idx + 3) % (r->scene->photon_count_per_pass * 3)];
	rand_dir.y = r->rand_list[(r->idx + 4) % (r->scene->photon_count_per_pass * 3)];
	rand_dir.z = r->rand_list[(r->idx + 5) % (r->scene->photon_count_per_pass * 3)];
	*r->devStates = state;
	rand_dir = v_norm(rand_dir);
	ray->dir = (v_dot(rand_dir, v_scale(ray->nhit, ray->n_dir)) < 0) ? v_scale(rand_dir, -1): rand_dir;
	scale_color(ray, p, r->scene->objects[ray->hit_obj].kd, r->scene->objects[ray->hit_obj].col);
}

__device__
void			redirect_photon_specular(t_raytracing_tools *r, t_ray *ray, float p)
{
	ray->origin = v_add(ray->hit, v_scale(ray->nhit, ray->n_dir * BIAS));
	ray->dir = reflect(ray->dir, v_scale(ray->nhit, ray->n_dir));
	scale_color(ray, p, r->scene->objects[ray->hit_obj].reflection, r->scene->objects[ray->hit_obj].col);
}

__device__
void			redirect_photon_transmit(t_raytracing_tools *r, t_ray *ray, float p)
{
	float n1;
	float n2;
	
	update_ior(&n1, &n2, r, ray);
	ray->ior = n2;
	ray->origin = v_add(ray->hit, v_scale(ray->nhit, -ray->n_dir * BIAS)); 
	ray->dir = refract(ray->dir, v_scale(ray->nhit, ray->n_dir), n1, n2);
	scale_color(ray, p, r->scene->objects[ray->hit_obj].transparency, r->scene->objects[ray->hit_obj].col);
}

/*
** ray: incoming ray.
** p: probability of particular redirection (diffuse, refelcted, refracted)
** k: coefficient of corresponding redirection (diffuse, reflection, transparency)
** obj_col: color of object hit
** P_refl = P_inc * k / p
*/

__device__
static void		scale_color(t_ray *ray, float p, float k, t_vec3 obj_col)
{
	t_color p_inc;

	p_inc = ray->col;
	ray->col.r = p_inc.r * k * (obj_col.x / (p * 255.0));
	ray->col.g = p_inc.g * k * (obj_col.y / (p * 255.0));
	ray->col.b = p_inc.b * k * (obj_col.z / (p * 255.0));
}