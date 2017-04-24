/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_global.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:18:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/22 11:45:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the global lighting value of the color at hitpoint.
*/

__device__
t_color	get_global(t_scene *scene, t_ray *primary_ray,
		t_ray *shadow_ray, t_light *light)
{
	t_color	new_col;
	double	r2;

	r2 = (!v_isnan(light->pos)) ?
		pow(v_length(v_sub(shadow_ray->origin, light->pos)), 2.0) :
		1 / (4 * M_PI);
	new_col = vec_to_col(v_scale(v_mult(light->col, v_scale(scene->objects[primary_ray->hit_obj].col,
		light->intensity / (4 * M_PI * r2))), ft_clampd(v_dot(shadow_ray->dir,
		v_scale(primary_ray->nhit, primary_ray->n_dir)), 0, 1)));
	new_col = c_scale(new_col, scene->objects[primary_ray->hit_obj].kd);
	// new_col = c_clamp(new_col, 0, 255);
	return (new_col);
}

t_vec3	get_random_ray()
{
	t_vec3	ray;
	int		angle_x; // 0 - 90
	int		angle_y; // 0 - 359

	ray = v_new(0, 1, 0);
	
}