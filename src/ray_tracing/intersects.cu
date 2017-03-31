/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:11:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 16:50:45 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

/*
** Checks for a ray-object intersection.
*/

__device__
bool	intersects(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	if (obj->type == T_SPHERE)
		return (get_sphere_intersection(r, ray, obj));
	else if (obj->type == T_PLANE)
		return (get_plane_intersection(r, ray, obj));
	else if (obj->type == T_DISK)
		return (get_disk_intersection(r, ray, obj));
	else if (obj->type == T_CYLINDER)
		return (get_cylinder_intersection(r, ray, obj));
	else if (obj->type == T_CONE)
		return (get_cone_intersection(r, ray, obj));
	return (false);
}
