/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_photon.cu                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 15:50:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/07 14:20:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include <curand.h>
#include <curand_kernel.h>

__device__
static void		save_photon(t_photon *photon_list, t_ray *ray, t_object *obj);
__device__
static float 	get_probability(float *p, t_vec3 o_col, float k, t_vec3 p_col);

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
	if (r->scene->objects[ray->hit_obj].kd > 0.0 && ray->type == r->scene->is_raytracing ? R_INDIRECT_PHOTON : R_DIRECT_PHOTON)
		save_photon(r->scene->photon_list + r->idx * PHOTON_BOUNCE_MAX, ray, &r->scene->objects[ray->hit_obj]);
	rand_f = curand_uniform(r->devStates);
	tmp = 0;
	p = NAN;
	ray->type = R_INDIRECT_PHOTON;
	if ((tmp += get_probability(&p, r->scene->objects[ray->hit_obj].col, r->scene->objects[ray->hit_obj].kd / 3.0, col_to_vec(ray->col))) > rand_f)
		redirect_photon_diffuse(r, ray, p);
	else if ((tmp += get_probability(&p, r->scene->objects[ray->hit_obj].col, r->scene->objects[ray->hit_obj].reflection / 3.0, col_to_vec(ray->col))) > rand_f)
		redirect_photon_specular(r, ray, p);
	else if ((tmp += get_probability(&p, r->scene->objects[ray->hit_obj].col, r->scene->objects[ray->hit_obj].transparency / 3.0, col_to_vec(ray->col))) > rand_f)
	{
		if (fresnel_reflect(r, ray))
			redirect_photon_specular(r, ray, p);
		else
			redirect_photon_transmit(r, ray, p);
	}
	else
		return (c_new(0, 0, 0));
	if ((ray->col.r + ray->col.g + ray->col.b) > 10)
		return (cast_primary_ray(r, ray));
	return (c_new(0, 0, 0));
}

__device__
static void		save_photon(t_photon *photon_list, t_ray *ray, t_object *obj)
{
	int i;

	i = 0;                                         
	while (!v_isnan(photon_list[i].pos) && i < PHOTON_BOUNCE_MAX)
		++i;
	photon_list[i].pos = ray->hit;
	photon_list[i].dir = ray->dir;
	photon_list[i].col = ray->type == R_INDIRECT_PHOTON ? ray->col : vec_to_col(get_object_color(obj, ray));
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
int			fresnel_reflect(t_raytracing_tools *r, t_ray *ray)
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
