/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder_intersection.cu                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:27:49 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/18 14:35:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

__device__
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

	i.v3 = v_sub(ray->origin, r->scene->objects[index].pos);
	i.v1 = v_sub(ray->dir, v_scale(r->scene->objects[index].dir, v_dot(ray->dir, r->scene->objects[index].dir)));
	i.q.x = v_dot(i.v1, i.v1);
	i.v2 = v_sub(i.v3, v_scale(r->scene->objects[index].dir, v_dot(i.v3, r->scene->objects[index].dir)));
	i.q.y = 2 * v_dot(i.v1, i.v2);
	i.q.z = v_dot(i.v2, i.v2) - pow(r->scene->objects[index].rad, 2);
	if (!solve_quadratic(i.q, &i.r1, &i.r2))
		return (false);
	if (i.r2 < i.r1)
		ft_swapf(&i.r1, &i.r2);
	get_finite_cylinder_intersection(r, ray, index, &i);
	(i.r1 < 0 || isnan(i.r1)) ? i.r1 = i.r2 : 0;
	if (i.r1 < 0 || isnan(i.r1))
		return (false);
	r->t > i.r1 ? ray->t = i.r1 : 0;
	if (ray->type != R_SHADOW && r->t > i.r1)
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
		if (v_dot(r->scene->objects[index].dir, v_sub(i->p, r->scene->objects[index].pos)) < 0 ||
			v_dot(r->scene->objects[index].dir, v_sub(i->p, v_add(r->scene->objects[index].pos,
			v_scale(r->scene->objects[index].dir, r->scene->objects[index].height)))) > 0)
			i->r1 = NAN;
	}
	if (i->r2 > 0)
	{
		i->p = v_add(ray->origin, v_scale(ray->dir, i->r2));
		if (v_dot(r->scene->objects[index].dir, v_sub(i->p, r->scene->objects[index].pos)) < 0 ||
			v_dot(r->scene->objects[index].dir, v_sub(i->p, v_add(r->scene->objects[index].pos,
			v_scale(r->scene->objects[index].dir, r->scene->objects[index].height)))) > 0)
			i->r2 = NAN;
	}
}

__device__
t_pt2	get_uv_cylinder(t_object *obj, t_ray *ray, t_pt2 *dim)
{
	t_pt2	coord;
	t_vec3	hit_center;

	hit_center = v_scale(ray->nhit, -1);
	coord.x = (0.5 + (atan2f(hit_center.z, hit_center.x) / (float)(2 * M_PI))) * dim->x + obj->texture_translate.x;
	coord.y = (sqrtf(v_dist(ray->hit, obj->pos) * v_dist(ray->hit, obj->pos) - (obj->rad * obj->rad)) / obj->height) * dim->y + obj->texture_translate.y;
	coord.x %= dim->x;
	coord.y %= dim->y;
	return (coord);
}
