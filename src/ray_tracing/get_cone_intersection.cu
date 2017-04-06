/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cone_intersection.cu                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:30:04 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

__device__
static void	get_finite_cone_intersection(t_ray *ray,
	t_object *object, t_intersection_tools *i);
static bool	lower_than_min(double r, t_intersection_tools *i, t_object *obj,
	t_ray *ray);
static bool	higher_than_max(double r, t_intersection_tools *i, t_object *obj,
	t_ray *ray);

/*
** Checks for a ray-cone intersection.
*/

__device__
bool		get_cone_intersection(t_raytracing_tools *r, t_ray *ray,
			int index)
{
	t_intersection_tools i;

	i.d1 = tan(r->scenes->objects[index].angle);
	i.v1 = v_sub(ray->origin, r->scenes->objects[index].pos);
	i.q.x = v_dot(ray->dir, ray->dir) - (1.0 + i.d1 * i.d1) *
		pow(v_dot(ray->dir, r->scenes->objects[index].dir), 2.0);
	i.q.y = 2 * (v_dot(ray->dir, i.v1) - (1.0 + i.d1 * i.d1) *
		v_dot(ray->dir, r->scenes->objects[index].dir) * v_dot(i.v1, r->scenes->objects[index].dir));
	i.q.z = v_dot(i.v1, i.v1) - (1.0 + i.d1 * i.d1) * pow(v_dot(i.v1,
		r->scenes->objects[index].dir), 2.0);
	if (!solve_quadratic(i.q, &i.r1, &i.r2) || (i.r1 < 0 && i.r2 < 0))
		return (false);
	if (i.r2 < i.r1)
		ft_swapd(&i.r1, &i.r2);
	get_finite_cone_intersection(ray, &r->scenes->objects[index], &i);
	(i.r1 < 0 || isnan(i.r1)) ? i.r1 = i.r2 : 0;
	if (i.r1 < 0 || isnan(i.r1))
		return (false);
	r->t > i.r1 ? ray->t = i.r1 : 0;
	if (ray->type == R_PRIMARY && r->t > i.r1)
	{
		ray->hit_obj = index;
		ray->hit_type = T_CONE;
	}
	return (true);
}

__device__
static void	get_finite_cone_intersection(t_ray *ray,
	t_object *obj, t_intersection_tools *i)
{
	bool	r1_too_low;
	bool	r1_too_high;
	bool	r2_too_low;
	bool	r2_too_high;

	r1_too_low = lower_than_min(i->r1, i, obj, ray) || i->r1 == -1;
	r1_too_high = higher_than_max(i->r1, i, obj, ray) || i->r1 == -1;
	r2_too_low = lower_than_min(i->r2, i, obj, ray) || i->r2 == -1;
	r2_too_high = higher_than_max(i->r2, i, obj, ray) || i->r2 == -1;
	if (r1_too_low || r1_too_high)
	{
		i->r1 = NAN;
		if (r2_too_low || r2_too_high)
			i->r2 = NAN;
	}
	else if (!r1_too_low && !r1_too_high)
		i->r2 = NAN;
}

__device__
static bool	lower_than_min(double r, t_intersection_tools *i, t_object *obj,
	t_ray *ray)
{
	if (r > 0)
	{
		if (v_dot(obj->dir, v_sub(v_add(ray->origin,
			v_scale(ray->dir, r)), obj->pos)) < 0.0)
			return (true);
	}
	else
		return (true);
	return (false);
}

__device__
static bool	higher_than_max(double r, t_intersection_tools *i, t_object *obj,
	t_ray *ray)
{
	if (r > 0)
	{
		if (v_dot(obj->dir, v_sub(v_add(ray->origin, v_scale(ray->dir, r)),
			v_add(obj->pos, v_scale(obj->dir, obj->height)))) > 0.0)
			return (true);
	}
	else
		return (true);
	return (false);
}
