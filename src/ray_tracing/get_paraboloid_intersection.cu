/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paraboloid_intersection.cu                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 13:05:58 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 11:21:47 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

__device__
void	init_paraboloid_roots(t_raytracing_tools *r, t_ray *ray,
			int index, t_intersection_tools *i);

__device__
void		get_finite_paraboloid_intersection(t_raytracing_tools *r, t_ray *ray,
			int index, t_intersection_tools *i)
{
	if (i->r1 > 0)
	{
		i->p = v_add(ray->origin, v_scale(ray->dir, i->r1));
		if (v_dot(r->scene->objects[index].dir,
			v_sub(i->p, r->scene->objects[index].pos)) < 0 ||
			v_dot(r->scene->objects[index].dir,
			v_sub(i->p, v_add(r->scene->objects[index].pos,
			v_scale(r->scene->objects[index].dir,
			r->scene->objects[index].height)))) > 0)
			i->r1 = NAN;
	}
	if (i->r2 > 0)
	{
		i->p = v_add(ray->origin, v_scale(ray->dir, i->r2));
		if (v_dot(r->scene->objects[index].dir,
			v_sub(i->p, r->scene->objects[index].pos)) < 0 ||
			v_dot(r->scene->objects[index].dir,
			v_sub(i->p, v_add(r->scene->objects[index].pos,
			v_scale(r->scene->objects[index].dir,
			r->scene->objects[index].height)))) > 0)
			i->r2 = NAN;
	}
}

__device__
bool		get_paraboloid_intersection(t_raytracing_tools *r, t_ray *ray,
			int index)
{
	t_intersection_tools	i;

	init_paraboloid_roots(r, ray, index, &i);
	if (!solve_quadratic(i.q, &i.r1, &i.r2))
		return (false);
	if (i.r2 < i.r1)
		ft_swapf(&i.r1, &i.r2);
	get_finite_paraboloid_intersection(r, ray, index, &i);
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
void	init_paraboloid_roots(t_raytracing_tools *r, t_ray *ray,
			int index, t_intersection_tools *i)
{
	i->v1 = v_sub(ray->origin, r->scene->objects[index].pos);
	i->q.x = v_dot(ray->dir, ray->dir) - v_dot(ray->dir,
		r->scene->objects[index].dir) *
		v_dot(ray->dir, r->scene->objects[index].dir);
	i->q.y = 2 * (v_dot(ray->dir, i->v1) - v_dot(ray->dir,
		r->scene->objects[index].dir) *
		(v_dot(i->v1, r->scene->objects[index].dir) + 2 *
		r->scene->objects[index].rad));
	i->q.z = v_dot(i->v1, i->v1) - v_dot(i->v1,
		r->scene->objects[index].dir) * (v_dot(i->v1,
		r->scene->objects[index].dir) + 4 * r->scene->objects[index].rad);
}
