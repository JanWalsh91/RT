/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 13:00:35 by tgros             #+#    #+#             */
/*   Updated: 2017/05/08 12:32:10 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

__device__
t_vec3		get_texture_at_uv_coord(t_object *obj, t_pt2 coord)
{
	t_vec3		ret;

	ret = v_new(0, 0, 0);
	if (coord.x == -1 || coord.y == -1)
		return (ret);
	return (col_to_vec(obj->texture[obj->texture_dim.x * coord.y + coord.x]));
}

__device__
t_pt2		get_uv_coord(t_object *obj, t_ray *ray, t_pt2 *dim)
{
	t_pt2	ret;

	ret.x = -1;
	ret.y = -1;
	if (obj->type == T_PLANE)
		return (get_uv_plane(obj, ray, dim));
	else if (obj->type == T_CONE)
		return (get_uv_cone(obj, ray, dim));
	else if (obj->type == T_SPHERE)
		return (get_uv_sphere(obj, ray, dim));
	else if (obj->type == T_CYLINDER)
		return (get_uv_cylinder(obj, ray, dim));
	return (ret);
}

__device__
t_vec3		get_object_color(t_object *obj, t_ray *ray)
{
	if (obj->texture)
		return (get_texture_at_uv_coord(obj, get_uv_coord(obj, ray, &obj->texture_dim)));
	else
		return (obj->col);
}