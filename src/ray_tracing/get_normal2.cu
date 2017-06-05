/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:39 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 15:25:36 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

__device__
void		get_cylinder_normal(t_ray *ray, t_object *obj)
{
	t_vec3	x;
	float	m;

	x = v_sub(ray->origin, obj->pos);
	m = v_dot(ray->dir, v_scale(obj->dir, ray->t)) + v_dot(x, obj->dir);
	x = v_add(obj->pos, v_scale(obj->dir, m));
	ray->nhit = v_norm(v_sub(ray->hit, x));
	if (obj->normal_map)
		ray->nhit = get_normal_at_normal_map(obj, ray);
}

__device__
void		get_cone_normal(t_ray *ray, t_object *obj)
{
	t_vec3	x;

	x = v_sub(ray->hit, obj->pos);
	ray->nhit = v_sub(x, v_scale(obj->dir,
		(v_length(x) / cos(obj->angle))));
	ray->nhit = v_norm(ray->nhit);
	if (obj->normal_map)
		ray->nhit = get_normal_at_normal_map(obj, ray);
}

__device__
void		get_paraboloid_normal(t_ray *ray, t_object *obj)
{
	float	m;

	m = v_dot(v_sub(ray->hit, obj->pos), obj->dir);
	ray->nhit = v_norm(v_sub(v_sub(ray->hit, obj->pos),
		v_scale(obj->dir, obj->height + m)));
	if (obj->normal_map)
		ray->nhit = get_normal_at_normal_map(obj, ray);
}
