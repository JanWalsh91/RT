/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_reflected_and_refracted.cu                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 13:49:42 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/06 11:25:11 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the reflected value of the color at hitpoint.
*/

__device__
static t_color	get_refracted(t_raytracing_tools *r, t_scene *scene,
				t_ray *ray);
__device__
static t_color	get_reflected(t_raytracing_tools *r, t_scene *scene,
				t_ray *ray, float f);
__device__
static t_color	get_beer_lambert_color(t_raytracing_tools *r, t_ray *ray,
				t_color col, float kt);

__device__
t_color			get_reflected_and_refracted(t_raytracing_tools *r,
				t_scene *scene, t_ray *ray)
{
	if (scene->objects[ray->hit_obj].transparency > 0.0001)
		return (get_refracted(r, scene, ray));
	else if (scene->objects[ray->hit_obj].reflection > 0.0001)
		return (get_reflected(r, scene, ray, 0));
	else
		return (c_new(0, 0, 0));
}

__device__
static t_color	get_refracted(t_raytracing_tools *r, t_scene *scene,
				t_ray *ray)
{
	t_ray		refr;
	float		n1;
	float		n2;
	float		f;
	t_object	*o;

	update_ior(&n1, &n2, r, ray);
	o = &scene->objects[ray->hit_obj];
	refr.t = INFINITY;
	refr.type = R_PRIMARY;
	refr.depth = ray->depth;
	refr.ior = n2;
	refr.origin = v_add(ray->hit, v_scale(ray->nhit, -ray->n_dir * BIAS));
	refr.dir = refract(ray->dir, v_scale(ray->nhit, ray->n_dir), n1, n2);
	if (v_isnan(refr.dir))
		return (get_reflected(r, scene, ray, o->transparency - o->reflection));
	f = scene->is_fresnel ? get_fresnel_ratio(ray->dir,
		v_scale(ray->nhit, ray->n_dir), n1, n2) : 0;
	if (scene->is_fresnel || o->reflection > 0.0)
		return (c_add(c_scale(get_beer_lambert_color(r, &refr,
		cast_primary_ray(r, &refr), o->transparency), (1 - f) *
		o->transparency), get_reflected(r, scene, ray, f)));
	return (c_scale(get_beer_lambert_color(r, &refr,
		cast_primary_ray(r, &refr), o->transparency), o->transparency));
}

/*
** Changes color based on Beer Lambert formula, reducing transmitted color based
** on coefficient and distance.
*/

__device__
static t_color	get_beer_lambert_color(t_raytracing_tools *r, t_ray *ray,
				t_color col, float kt)
{
	if (ray->t != INFINITY)
		return (c_scale(col, exp(-0.3 * ray->t * (1.0 - kt))));
	return (col);
}

__device__
static t_color	get_reflected(t_raytracing_tools *r, t_scene *scene,
				t_ray *ray, float f)
{
	t_ray	reflected;

	reflected.type = R_PRIMARY;
	reflected.origin = v_add(ray->hit, v_scale(ray->nhit, ray->n_dir * BIAS));
	reflected.dir = reflect(ray->dir, v_scale(ray->nhit, ray->n_dir));
	reflected.ior = ray->ior;
	reflected.depth = ray->depth;
	reflected.n_dir = 1;
	reflected.t = INFINITY;
	return (c_scale(cast_primary_ray(r, &reflected), f +
		scene->objects[ray->hit_obj].reflection));
}
