/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_reflected_and_refracted.cu                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 13:49:42 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/19 16:53:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the reflected value of the color at hitpoint.
*/

__device__
t_color	get_reflected_and_refracted(t_raytracing_tools *r, t_scene *scene, t_ray *ray)
{
	double	f;
	t_ray	reflection;
	t_ray	refraction;
	t_color	col;

	if (r->pix.x == 50 && r->pix.y == 50)
		printf("get_reflected_and_refracted\n");
	f = 1;
	col = c_new(0, 0, 0);
	reflection.type = R_PRIMARY;
	reflection.origin = v_add(ray->hit, v_scale(ray->nhit, ray->n_dir * BIAS));
	reflection.dir = reflect(ray->dir, v_scale(ray->nhit, ray->n_dir));
	reflection.ior = ray->ior;
	if (scene->objects[ray->hit_obj].reflection > 0 && scene->objects[ray->hit_obj].transparency < 0.0001)
	{
		if (r->pix.x == 50 && r->pix.y == 50)
			C(1);
		col = c_scale(cast_primary_ray(r, &reflection), scene->objects[ray->hit_obj].reflection);
	}
	else if (scene->objects[ray->hit_obj].transparency > 0)
	{
		f = get_fresnel_ratio(ray->dir, v_scale(ray->nhit, ray->n_dir), scene->objects[ray->hit_obj].ior);
		if (r->pix.x == 500 && r->pix.y == 500)
			printf("fresnel: [%f]\n", f);
		refraction = reflection;
		refraction.ior = scene->objects[ray->hit_obj].ior;
		refraction.origin = v_add(ray->hit, v_scale(ray->nhit, -ray->n_dir * BIAS));
		refraction.dir = refract(ray->dir, ray->nhit, refraction.ior);
		col = c_add(c_scale(cast_primary_ray(r, &reflection), scene->objects[ray->hit_obj].reflection * f),
		
		c_scale(cast_primary_ray(r, &refraction), 1 * (1 - f)));
	}
	return (col);
}