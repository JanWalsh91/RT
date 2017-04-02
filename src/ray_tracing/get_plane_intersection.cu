/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane_intersection.cu                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:25:30 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/02 18:24:58 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

/*
** Checks for a ray-plane intersection.
*/

__device__
bool	get_plane_intersection(t_scene *scene, t_ray *ray, int index)
{
	t_intersection_tools	i;

	i.n_dir = 1;
	if (v_dot(scene->objects[index].dir, ray->dir) > 0)
		i.n_dir = -1;
	i.d1 = v_dot(v_scale(scene->objects[index].dir, i.n_dir), ray->dir);
	if (i.d1 > -1e-6)
		return (false);
	i.v1 = v_sub(scene->objects[index].pos, ray->origin);
	i.r1 = v_dot(i.v1, v_scale(scene->objects[index].dir, i.n_dir)) / i.d1;
	if (i.r1 < 0)
		return (false);
	scene->t > i.r1 ? ray->t = i.r1 : 0;
	if (ray->type == R_PRIMARY && scene->t > i.r1)
	{
		ray->hit_obj = index;
		ray->hit_type = T_PLANE;
	}
	return (true);
}
