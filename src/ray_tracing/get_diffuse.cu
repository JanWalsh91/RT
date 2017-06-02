/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_diffuse.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:18:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/02 15:14:33 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the diffuse value of the color at hitpoint.
*/

__device__
t_color	get_diffuse(t_scene *scene, t_ray *primary_ray,
		t_ray *shadow_ray, t_light *light)
{
	t_color	new_col;
	float	r2;

	r2 = (!v_isnan(light->pos)) ? powf(v_length(v_sub(shadow_ray->origin, light->pos)), 2.0) : 1 / (4 * M_PI);
	new_col = vec_to_col(v_scale(v_mult(light->col, v_scale(get_object_color(&scene->objects[primary_ray->hit_obj], primary_ray),
		(v_isnan(light->pos) ? light->intensity / 10000 : light->intensity) / (4 * M_PI * r2))), ft_clampf(v_dot(shadow_ray->dir,
		v_scale(primary_ray->nhit, primary_ray->n_dir)), 0, 1)));
	new_col = c_scale(new_col, scene->objects[primary_ray->hit_obj].kd);
	// new_col = c_clamp(new_col, 0, 255);
	return (new_col);
}
