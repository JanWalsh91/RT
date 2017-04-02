/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:11:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/02 18:24:22 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

/*
** Checks for a ray-object intersection.
*/

__device__
bool	intersects(t_scene *scene, t_ray *ray, int index)
{
	if (scene->objects[index].type == T_SPHERE)
		return (get_sphere_intersection(scene, ray, index));
	else if (scene->objects[index].type == T_PLANE)
		return (get_plane_intersection(scene, ray, index));
	else if (scene->objects[index].type == T_DISK)
		return (get_disk_intersection(scene, ray, index));
	else if (scene->objects[index].type == T_CYLINDER)
		return (get_cylinder_intersection(scene, ray, index));
	else if (scene->objects[index].type == T_CONE)
		return (get_cone_intersection(scene, ray, index));
	return (false);
}
