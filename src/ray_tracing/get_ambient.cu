/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:04:10 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/12 12:13:24 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the ambient value of the color.
*/

__device__
t_color	get_ambient(t_scene *scene, t_vec3 obj_col)
{
	return (vec_to_col(v_sub(v_scale(obj_col, scene->ka),
			v_scale(v_sub(v_new(255, 255, 255),
			scene->ambient_light_color), scene->ka))));
}
