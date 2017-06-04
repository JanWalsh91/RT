/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_reflected_and_refracted.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 13:49:42 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/03 17:00:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the reflected value of the color at hitpoint.
*/

__device__
static t_color	get_refracted(t_raytracing_tools *r, t_scene *scene, t_ray *ray);
__device__
static t_color	get_reflected(t_raytracing_tools *r, t_scene *scene, t_ray *ray, float f);


__device__
t_color			get_reflected_and_refracted(t_raytracing_tools *r, t_scene *scene, t_ray *ray)
{
	if (scene->objects[ray->hit_obj].transparency > 0.0001)
		return (get_refracted(r, scene, ray));
	else if (scene->objects[ray->hit_obj].reflection > 0.0001)
		return (get_reflected(r, scene, ray, 0));
	else
		return (c_new(0, 0, 0));
}

__device__
static t_color	get_beer_lambert_color(t_raytracing_tools *r, t_ray *ray, t_color col, float kt, float t)
{
	return (c_scale(col, exp(-0.3 * t * (1.0 - kt))));
}

__device__
static t_color	get_refracted(t_raytracing_tools *r, t_scene *scene, t_ray *ray)
{
	t_ray	refracted;
	float	n1;
	float 	n2;
	float	f;

	update_ior(&n1, &n2, r, ray);
	refracted.type = R_PRIMARY;
	refracted.depth = ray->depth;
	refracted.ior = n2;
	refracted.origin = v_add(ray->hit, v_scale(ray->nhit, -ray->n_dir * BIAS)); 
	refracted.dir = refract(ray->dir, v_scale(ray->nhit, ray->n_dir), n1, n2);
	if (v_isnan(refracted.dir))
		return (get_reflected(r, scene, ray, scene->objects[ray->hit_obj].transparency - scene->objects[ray->hit_obj].reflection));
	f = scene->is_fresnel ? get_fresnel_ratio(ray->dir, v_scale(ray->nhit, ray->n_dir), n1, n2) : 0;
	if (scene->is_fresnel || scene->objects[ray->hit_obj].reflection > 0.0)
		return (c_add(c_scale(get_beer_lambert_color(r, &refracted, cast_primary_ray(r, &refracted), scene->objects[ray->hit_obj].transparency, refracted.t), (1 - f) * scene->objects[ray->hit_obj].transparency), get_reflected(r, scene, ray, f)));
	else
		return (c_scale(get_beer_lambert_color(r, &refracted, cast_primary_ray(r, &refracted), scene->objects[ray->hit_obj].transparency, refracted.t), scene->objects[ray->hit_obj].transparency));
}

__device__
static t_color	get_reflected(t_raytracing_tools *r, t_scene *scene, t_ray *ray, float f)
{
	t_ray	reflected;

	reflected.type = R_PRIMARY;
	reflected.origin = v_add(ray->hit, v_scale(ray->nhit, ray->n_dir * BIAS));
	reflected.dir = reflect(ray->dir, v_scale(ray->nhit, ray->n_dir));
	reflected.ior = ray->ior;
	reflected.depth = ray->depth;
	reflected.n_dir = 1;
	return (c_scale(cast_primary_ray(r, &reflected), f + scene->objects[ray->hit_obj].reflection));
}

/*
** Updates the ior list and determines n1 and n2.
** n1: ior of volume of incoming ray
** n2: ior of volume of outgoing ray
*/

__device__
void			update_ior(float *n1, float *n2, t_raytracing_tools *r, t_ray *ray)
{
	int		i;
	float	ret;

	//ior list size: MAX_RAY_DEPTH + 1
	//but we don't want to go over ray_depth
	if (ray->n_dir == 1)
	{//case: ray entering object. Add ior to list unless no more place in list.
		i = 0;
		*n1 = ray->ior;
		while (r->ior_list[i] > 0.001 && i < r->scene->ray_depth && i < MAX_RAY_DEPTH)
			++i;
		if (i)
			r->ior_list[i] = r->scene->objects[ray->hit_obj].ior;
		*n2 = r->scene->objects[ray->hit_obj].ior;
	}
	else
	{//case: ray leaving object. Find matching ior. Else, use ior_list[0] and do not delete it.
		i = r->scene->ray_depth;
		//find last ior added to list
		while (i >= 0)
		{
			ret = r->ior_list[i] - r->scene->objects[ray->hit_obj].ior;
			if (ret < 0.001 && ret > -0.001)
				break;
			--i;
		}
		// if we did not find a match, find the last 
		if (!(ret < 0.001 && ret > -0.001))
		{
			i = 0;
			*n1 = ray->ior;
			while (r->ior_list[i] > 0.001 && i < r->scene->ray_depth)
				++i;
			*n2 = r->ior_list[i == r->scene->ray_depth || !i ? 0 : i - 1];
			return ;
		}
		//if we found a match, set it to zero in list, except if first one.
		//if first one, move all iors down.
		if (i)
		{
			r->ior_list[i] = 0;
			while (i < r->scene->ray_depth && r->ior_list[i] < 0.001)
			{
				r->ior_list[i] = r->ior_list[i + 1];
				r->ior_list[i + 1] = 0;
				++i;
			}
		}
		i = 0;
		while (r->ior_list[i] > 0.001)
			++i;
		*n2 = r->ior_list[i ? i - 1 : 0];
		*n1 = ray->ior;
	}
	i = -1;
}