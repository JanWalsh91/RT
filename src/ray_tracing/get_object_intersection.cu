/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_intersection.cu                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <talemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:26:41 by talemari          #+#    #+#             */
/*   Updated: 2017/05/18 15:28:58 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../../inc/objparser.h"
/*
** Checks for a object-sphere intersection.
*/

__device__
bool	get_obj_intersection(t_obj *o, t_ray *ray, int index, t_vec3 *norm)
{
	t_triangle		triangle;
	t_obj_triangle	*lst_triangle;

	while (o->triangle)
	{
		lst_triangle = (t_obj_triangle *)o->triangle->content;
		triangle.v1 = o->vertex[lst_triangle->v.x];
		triangle.v2 = o->vertex[lst_triangle->v.y];
		triangle.v3 = o->vertex[lst_triangle->v.z];
		if (get_triangle_intersection(&triangle, ray, index, norm))
			return (true);
		o->triangle = o->triangle->next;
	}
	return (false);
}
