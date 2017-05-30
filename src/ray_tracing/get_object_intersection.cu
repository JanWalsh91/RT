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
#include <stdio.h>
/*
** Checks for a object-sphere intersection.
*/

__device__
static void		print_triangles_dev(t_obj *obj)
{
	t_obj_triangle		*tmp2;
	t_list				*tmp;

	tmp = obj->triangle;	
	printf("Printing triangles\n");
	while (tmp != NULL)
	{
		printf("-----TRIANGLE----- %p\n", tmp);
		tmp2 = (t_obj_triangle *)tmp->content;
		printf("v1 = %f, %f, %f\n", obj->vertex[tmp2->v.x].x, obj->vertex[tmp2->v.x].y, obj->vertex[tmp2->v.x].z);
		printf("v2 = %f, %f, %f\n", obj->vertex[tmp2->v.y].x, obj->vertex[tmp2->v.y].y, obj->vertex[tmp2->v.y].z);
		printf("v3 = %f, %f, %f\n", obj->vertex[tmp2->v.z].x, obj->vertex[tmp2->v.z].y, obj->vertex[tmp2->v.z].z);
		tmp = tmp->next;
	}
}

__device__
bool	get_obj_intersection(t_raytracing_tools *r, t_ray *ray, int index)
{
	t_triangle		triangle;
	t_obj_triangle	*lst_triangle;
	t_obj			*o;
	t_list			*tmp;

	// if (r->idx != 0)
	// 	return (0);
//	if (!(get_sphere_intersection(r, ray, index)))
//		return (false);
	o = r->scene->objects[index].obj;
	tmp = o->triangle;
	//printf("Check\n");
	//if (r->pix.x == 0 && r->pix.y == 0)
		//print_triangles_dev(o);
	while (tmp)
	{
		//printf("Triangle check\n");
	
		lst_triangle = (t_obj_triangle *)tmp->content;
		triangle.v1 = o->vertex[lst_triangle->v.x];
		triangle.v2 = o->vertex[lst_triangle->v.y];
		triangle.v3 = o->vertex[lst_triangle->v.z];
		if (get_triangle_intersection(r, &triangle, ray, index))
				return (true);
		//if (r->pix.x == 600 && r->pix.y < 200)
			//printf("addr %p\n", o->triangle->next);
		tmp = tmp->next;
	}
	// if (r->idx == 0)
	// printf("Exit obj_intersection\n");
	return (false);
}
