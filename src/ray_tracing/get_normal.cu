/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:39 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/18 14:35:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

__device__
static void	get_sphere_normal(t_ray *ray, t_object *obj);
__device__
static void	get_plane_normal(t_ray *ray, t_object *obj);
__device__
static void	get_cylinder_normal(t_ray *ray, t_object *obj);
__device__
static void	get_cone_normal(t_ray *ray, t_object *obj);

__device__
t_vec3		get_normal_at_normal_map(t_object *obj, t_ray *ray)
{
	t_vec3	tangente;
	t_vec3	bitangente;
	t_vec3	color;
	t_vec3	res;
	t_pt2	coord;

	tangente = v_norm(v_cross(ray->dir, ray->nhit));
	bitangente = v_norm(v_cross(ray->nhit, tangente));
	coord = get_uv_coord(obj, ray, &obj->normal_map_dim);
	color = col_to_vec(obj->normal_map[obj->normal_map_dim.x * coord.y + coord.x]);
	color.x = (color.x / 255.0f) * 2.0 - 1;
	color.y = (color.y / 255.0f) * 2.0 - 1;
	color.z = (color.z / 255.0f) * 2.0 - 1;
	res.x = (tangente.x * color.x + bitangente.x * color.y + ray->nhit.x * color.z);
	res.y = (tangente.y * color.x + bitangente.y * color.y + ray->nhit.y * color.z);
	res.z = (tangente.z * color.x + bitangente.z * color.y + ray->nhit.z * color.z);
	return (res);
}

/*
** Updates the normal at hitpoint (nhit and n_dir).
*/

__device__
void		get_normal(t_ray *ray, t_object *obj)
{
	// if (ray->type > 1)
	// 	printf("photon: get_normal. nhit: [%f, %f, %f]\n", ray->nhit.x, ray->nhit.y, ray->nhit.z);
	if (ray->hit_type == T_SPHERE)
		get_sphere_normal(ray, obj);
	if (ray->hit_type == T_PLANE || ray->hit_type == T_DISK)
		get_plane_normal(ray, obj);
	if (ray->hit_type == T_CYLINDER)
		get_cylinder_normal(ray, obj);
	if (obj->type == T_CONE)
		get_cone_normal(ray, obj);
	ray->n_dir = v_dot(ray->nhit, ray->dir) < 0 ? 1 : -1;
}

__device__
static void	get_sphere_normal(t_ray *ray, t_object *obj)
{
	ray->nhit = (v_sub(ray->hit, obj->pos));
	ray->nhit = v_norm(ray->nhit);
	if (obj->normal_map)
		ray->nhit = get_normal_at_normal_map(obj, ray);
}

__device__
static void	get_plane_normal(t_ray *ray, t_object *obj)
{
	ray->nhit = v_norm(obj->dir);
	if (obj->normal_map)
		ray->nhit = get_normal_at_normal_map(obj, ray);
}

__device__
static void	get_cylinder_normal(t_ray *ray, t_object *obj)
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
static void	get_cone_normal(t_ray *ray, t_object *obj)
{
	t_vec3	x;

	x = v_sub(ray->hit, obj->pos);
	ray->nhit = v_sub(x, v_scale(obj->dir, (v_length(x) / cos(obj->angle))));
	ray->nhit = v_norm(ray->nhit);
	if (obj->normal_map)
		ray->nhit = get_normal_at_normal_map(obj, ray);
}
