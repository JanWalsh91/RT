/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:04:10 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/03 12:44:49 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the ambient value of the color.
*/

__device__
t_color	get_ambient(t_scene *scene, t_ray *ray)
{
	if (ray->depth != scene->ray_depth - 1)
		return (c_new(0, 0, 0));
	return (vec_to_col(v_sub(v_scale(
		get_object_color(&scene->objects[ray->hit_obj], ray), scene->ka),
		v_scale(v_sub(v_new(255, 255, 255),
		scene->ambient_light_color), scene->ka))));
}
