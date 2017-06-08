/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_view_pane_intersection.cu                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 15:41:24 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 14:14:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "../../inc/cuda_call.cuh"

__device__
bool		get_view_pane_intersection(t_ray *ray, t_camera *cam)
{
	float	d1;
	t_vec3	v1;
	float	r1;

	d1 = v_dot(v_scale(cam->dir, -1), ray->dir);
	if (d1 > -1e-20)
		return (false);
	v1 = v_sub(v_add(cam->pos, cam->dir), cam->pos);
	r1 = v_dot(v1, v_scale(cam->dir, -1)) / d1;
	if (r1 < 0)
		return (false);
	ray->t = r1;
	return (true);
}
