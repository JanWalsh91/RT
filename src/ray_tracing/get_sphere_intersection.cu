/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere_intersection.cu                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:26:41 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/01 15:50:23 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Checks for a ray-sphere intersection.
*/

__device__
bool	get_sphere_intersection(t_raytracing_tools *r, t_ray *ray, int index)
{
	t_intersection_tools	i;

	i.v1 = v_sub(ray->origin, r->scene->objects[index].pos);
	i.q.x = v_dot(ray->dir, ray->dir);
	i.q.y = 2 * v_dot(i.v1, ray->dir);
	i.q.z = v_dot(i.v1, i.v1) - pow(r->scene->objects[index].rad, 2);
	if (!solve_quadratic(i.q, &i.r1, &i.r2))
		return (false);
	if (i.r2 < i.r1)
		ft_swapf(&i.r1, &i.r2);
	(i.r1 < 0) ? i.r1 = i.r2 : 0;
	if (i.r1 < 0)
		return (false);
	r->t > i.r1 ? ray->t = i.r1 : 0;
	if (ray->type == R_PRIMARY && r->t > i.r1)
	{
		ray->hit_obj = index;
		ray->hit_type = T_SPHERE;
	}
	return (true);
}

__device__
t_pt2	get_uv_sphere(t_object *obj, t_ray *ray)
{
	t_pt2	coord;
	t_vec3	hit_center;

	hit_center = v_scale(ray->nhit, -1);

	coord.x = (0.5 + (atan2f(hit_center.z, hit_center.x) / (float)(2 * M_PI))) * obj->texture_dim.x;
	coord.y = (0.5 - (asinf(hit_center.y) / M_PI)) * obj->texture_dim.y;


	return (coord);
}
