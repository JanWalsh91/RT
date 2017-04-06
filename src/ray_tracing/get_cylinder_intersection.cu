/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder_intersection.cu                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:27:49 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

static void	get_finite_cylinder_intersection(t_raytracing_tools *r, t_ray *ray,
	int index, t_intersection_tools *i);

/*
** Checks for a cylinder-ray intersection.
*/

__device__
bool		get_cylinder_intersection(t_raytracing_tools *r, t_ray *ray,
	int index)
{
	t_intersection_tools	i;

	i.v3 = v_sub(ray->origin, r->scenes->objects[index].pos);
	i.v1 = v_sub(ray->dir, v_scale(r->scenes->objects[index].dir, v_dot(ray->dir, r->scenes->objects[index].dir)));
	i.q.x = v_dot(i.v1, i.v1);
	i.v2 = v_sub(i.v3, v_scale(r->scenes->objects[index].dir, v_dot(i.v3, r->scenes->objects[index].dir)));
	i.q.y = 2 * v_dot(i.v1, i.v2);
	i.q.z = v_dot(i.v2, i.v2) - pow(r->scenes->objects[index].rad, 2);
	if (!solve_quadratic(i.q, &i.r1, &i.r2))
		return (false);
	if (i.r2 < i.r1)
		ft_swapd(&i.r1, &i.r2);
	get_finite_cylinder_intersection(r, ray, index, &i);
	(i.r1 < 0 || isnan(i.r1)) ? i.r1 = i.r2 : 0;
	if (i.r1 < 0 || isnan(i.r1))
		return (false);
	r->t > i.r1 ? ray->t = i.r1 : 0;
	if (ray->type == R_PRIMARY && r->t > i.r1)
	{
		ray->hit_obj = index;
		ray->hit_type = T_CYLINDER;
	}
	return (true);
}

__device__
static void	get_finite_cylinder_intersection(t_raytracing_tools *r, t_ray *ray,
	int index, t_intersection_tools *i)
{
	if (i->r1 > 0)
	{
		i->p = v_add(ray->origin, v_scale(ray->dir, i->r1));
		if (v_dot(r->scenes->objects[index].dir, v_sub(i->p, r->scenes->objects[index].pos)) < 0 ||
			v_dot(r->scenes->objects[index].dir, v_sub(i->p, v_add(r->scenes->objects[index].pos,
			v_scale(r->scenes->objects[index].dir, r->scenes->objects[index].height)))) > 0)
			i->r1 = NAN;
	}
	if (i->r2 > 0)
	{
		i->p = v_add(ray->origin, v_scale(ray->dir, i->r2));
		if (v_dot(r->scenes->objects[index].dir, v_sub(i->p, r->scenes->objects[index].pos)) < 0 ||
			v_dot(r->scenes->objects[index].dir, v_sub(i->p, v_add(r->scenes->objects[index].pos,
			v_scale(r->scenes->objects[index].dir, r->scenes->objects[index].height)))) > 0)
			i->r2 = NAN;
	}
}
