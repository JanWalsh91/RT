/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:21:02 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Given a ray direction and normal at hit point, returns the direction of the
** reflected ray.
*/

__device__
t_vec3	reflect(t_vec3 ray_dir, t_vec3 nhit)
{
	return (v_sub(ray_dir, v_scale(nhit, 2 * v_dot(ray_dir, nhit))));
}
