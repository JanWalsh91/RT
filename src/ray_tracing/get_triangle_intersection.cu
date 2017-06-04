/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle_intersection.cu                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:26:41 by talemari          #+#    #+#             */
/*   Updated: 2017/06/04 14:16:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOT A LA NORME

#include "../../inc/rt.cuh"
#include "../../inc/objparser.h"
/*
** Checks for a ray-sphere intersection.
*/

// __device__
// static void		print_vec2(t_vec3 vec)
// {
// 	printf("x : %f, y : %f, z : %f\n", vec.x, vec.y, vec.z);
// }

/*__device__
bool	get_triangle_intersection(t_raytracing_tools *r, t_triangle *t, t_ray *ray, int index)
{
	t_intersection_tools	i;

	i.n_dir = (v_dot(r->scene->objects[index].dir, ray->dir) > 0) ? -1 : 1;
	i.p = v_sub(t->v2, t->v1);
	i.q = v_sub(t->v3, t->v1);
	i.v1 = v_cross(ray->dir, i.q);
	i.d1 = v_dot(i.p, i.v1);
	if (i.d1 > -0.000001 && i.d1 < 0.000001)
		return (false);
	i.d2 = 1 / i.d1;
	i.v2 = v_sub(ray->origin, t->v1);
	i.r1 = v_dot(i.v2, i.v1) * i.d2;
	if (i.r1 < 0 || i.r1 > 1)
		return (false);
	i.v3 = v_cross(i.v2, i.p);
	i.r2 = v_dot(ray->dir, i.v3) * i.d2;
	if (i.r2 < 0 || (i.r2 + i.r1) > 1)
		return (false);
	i.r2 = (v_dot(i.q, i.v3)) * i.d2;
	if (i.r2 < 0)
		return (false);
	r->t > i.r2 ? ray->t = i.r2 : 0.0;
	ray->hit_obj = index;
	ray->hit_type = T_TRIANGLE;
	ray->nhit = v_cross(i.q, i.p);
	return (true);
}*/

__device__
bool	get_triangle_intersection(t_raytracing_tools *r, t_triangle *t, t_ray *ray, int index)
{
	t_intersection_tools	i;
	float					tmp;

	i.p = v_sub(t->v2, t->v1);
	i.q = v_sub(t->v3, t->v1);
	i.v1 = v_cross(ray->dir, i.q);
	i.d1 = v_dot(i.p, i.v1);
	if (i.d1 < 1e-8 && i.d1 > -1e-8)
		return (false);
	i.d2 = 1 / i.d1;
	i.v2 = v_sub(ray->origin, t->v1);
	i.r1 = v_dot(i.v1, i.v2) * i.d2;
	if (i.r1 < 0 || i.r1 > 1)
		return (false);
	i.v3 = v_cross(i.v2, i.p);
	i.r2 = v_dot(ray->dir, i.v3) * i.d2;
	if (i.r2 < 0 || i.r1 + i.r2 > 1)
		return (false);
	tmp = v_dot(i.q, i.v3) * i.d2;
	if (tmp < r->t && tmp < ray->t)
	{
		ray->t = tmp;
		if (v_dot(ray->nhit, ray->dir) > 0)
			ray->n_dir = -1;
	}
	return (true);
}
