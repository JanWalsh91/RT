/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specular.cu                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:13:51 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/21 16:56:46 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the specular value of the color at hitpoint.
*/

__device__
t_color	get_specular(t_scene *scene, t_ray *primary_ray, t_ray *shadow_ray, t_light *light)
{
	t_color	new_col;
	float	specular_intensity;
	t_vec3	reflection;
	float 	r2;
	 
	r2 = v_isnan(light->dir) ? v_dist(primary_ray->hit, light->pos) : 1;
	reflection = reflect(primary_ray->dir, v_scale(primary_ray->nhit,
		primary_ray->n_dir));
	specular_intensity = pow((ft_clampf(v_dot(reflection,
		shadow_ray->dir), 0, 1)), scene->objects[primary_ray->hit_obj].specular_exp);
	specular_intensity *= (light->intensity / r2) * scene->objects[primary_ray->hit_obj].ks;
	new_col = c_scale(vec_to_col(light->col), specular_intensity);
	// new_col = v_clamp(new_col, 0, 255);
	return (new_col);
}
