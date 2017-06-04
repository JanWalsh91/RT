/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:11:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/04 14:44:55 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Checks for a ray-object intersection.
*/

__device__
bool	intersects(t_raytracing_tools *r, t_ray *ray, int index)
{
	if (r->scene->objects[index].type == T_SPHERE)
		return (get_sphere_intersection(r, ray, index));
	else if (r->scene->objects[index].type == T_PLANE)
		return (get_plane_intersection(r, ray, index));
	else if (r->scene->objects[index].type == T_DISK)
		return (get_disk_intersection(r, ray, index));
	else if (r->scene->objects[index].type == T_CYLINDER)
		return (get_cylinder_intersection(r, ray, index));
	else if (r->scene->objects[index].type == T_CONE)
		return (get_cone_intersection(r, ray, index));
	else if (r->scene->objects[index].type == T_PARABOLOID)
		return (get_paraboloid_intersection(r, ray, index));
	else if (r->scene->objects[index].type == T_TORUS)
		return (get_torus_intersection(r, ray, index));
	else if (r->scene->objects[index].type == T_CUBE_TROUE)
		return (get_torus_intersection(r, ray, index));
	else if (r->scene->objects[index].type == T_OBJ)
		return (get_obj_intersection(r, ray, index));
	return (false);
}
