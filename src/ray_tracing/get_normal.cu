/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:39 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/03 16:03:48 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Updates the normal at hitpoint (nhit and n_dir).
*/

__device__
void		get_normal(t_ray *ray, t_object *obj)
{
	if (ray->hit_type == T_SPHERE)
		get_sphere_normal(ray, obj);
	if (ray->hit_type == T_PLANE || ray->hit_type == T_DISK)
		get_plane_normal(ray, obj);
	if (ray->hit_type == T_CYLINDER)
		get_cylinder_normal(ray, obj);
	if (obj->type == T_CONE)
		get_cone_normal(ray, obj);
	if (obj->type == T_TORUS)
		get_torus_normal(ray, obj);
	if (obj->type == T_PARABOLOID)
		get_paraboloid_normal(ray, obj);
	ray->n_dir = v_dot(ray->nhit, ray->dir) < 0 ? 1 : -1;
}

__device__
void		get_torus_normal(t_ray *ray, t_object *obj)
{
	t_vec3	a;
	float	k;
	float	m;
	t_vec3	tmp;

	k = v_dot(v_sub(ray->hit, obj->pos), obj->dir);
	a = v_sub(ray->hit, v_scale(obj->dir, k));
	m = sqrt((obj->rad * obj->rad) - (k * k));
	tmp = v_scale(v_sub(obj->pos, a), m);
	ray->nhit = v_norm(v_sub(v_sub(ray->hit, a),
			v_scale(tmp, (1 / (obj->rad_torus + m)))));
	if (obj->normal_map)
		ray->nhit = get_normal_at_normal_map(obj, ray);
}

__device__
void		get_sphere_normal(t_ray *ray, t_object *obj)
{
	ray->nhit = (v_sub(ray->hit, obj->pos));
	ray->nhit = v_norm(ray->nhit);
	if (obj->normal_map)
		ray->nhit = get_normal_at_normal_map(obj, ray);
}

__device__
void		get_plane_normal(t_ray *ray, t_object *obj)
{
	ray->nhit = v_norm(obj->dir);
	if (obj->normal_map)
		ray->nhit = get_normal_at_normal_map(obj, ray);
}

/*
** Gets the normal from a normal map if a normal map is used.
*/

__device__
t_vec3		get_normal_at_normal_map(t_object *obj, t_ray *ray)
{
	t_vec3	tangt;
	t_vec3	bitangt;
	t_vec3	color;
	t_vec3	res;
	t_pt2	coord;

	tangt = v_norm(v_cross(ray->dir, ray->nhit));
	bitangt = v_norm(v_cross(ray->nhit, tangt));
	coord = get_uv_coord(obj, ray, &obj->normal_map_dim);
	color = col_to_vec(obj->normal_map[(int)obj->normal_map_dim.x *
		coord.y + coord.x]);
	color.x = (color.x / 255.0f) * 2.0 - 1;
	color.y = (color.y / 255.0f) * 2.0 - 1;
	color.z = (color.z / 255.0f) * 2.0 - 1;
	res.x = (tangt.x * color.x + bitangt.x * color.y + ray->nhit.x * color.z);
	res.y = (tangt.y * color.x + bitangt.y * color.y + ray->nhit.y * color.z);
	res.z = (tangt.z * color.x + bitangt.z * color.y + ray->nhit.z * color.z);
	return (res);
}
