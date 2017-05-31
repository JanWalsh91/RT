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
bool	get_sphere_intersection_obj(t_raytracing_tools *r, t_ray *ray, int index)
{
	t_intersection_tools	i;

	i.v1 = v_sub(ray->origin, r->scene->objects[index].pos);
	i.q.x = v_dot(ray->dir, ray->dir);
	i.q.y = 2 * v_dot(i.v1, ray->dir);
	i.q.z = v_dot(i.v1, i.v1) - pow(r->scene->objects[index].rad, 2);
	if (!solve_quadratic(i.q, &i.r1, &i.r2))
		return (false);
	if (i.r2 < i.r1)
		ft_swapf(&i.r1, &i.r2);
	(i.r1 < 0) ? i.r1 = i.r2 : 0;
	if (i.r1 < 0)
		return (false);
	return (true);
}

__device__
bool	get_triangle_intersection_obj(t_raytracing_tools *r, t_triangle *t, t_ray *ray)
{
	t_intersection_tools	i;
	float					tmp;

	i.p = v_sub(t->v2, t->v1);
	i.q = v_sub(t->v3, t->v1);
	i.v1 = v_cross(ray->dir, i.q);
	i.d1 = v_dot(i.p, i.v1);
	if (i.d1 < 1e-8 && i.d1 > -1e-8)
		return (false);
	i.d2 = 1 / i.d1;
	i.v2 = v_sub(ray->origin, t->v1);
	i.r1 = v_dot(i.v1, i.v2) * i.d2;
	if (i.r1 < 0 || i.r1 > 1)
		return (false);
	i.v3 = v_cross(i.v2, i.p);
	i.r2 = v_dot(ray->dir, i.v3) * i.d2;
	if (i.r2 < 0 || i.r1 + i.r2 > 1)
		return (false);
	tmp = v_dot(i.q, i.v3) * i.d2;
	if (tmp < ray->t)
	{
		ray->t = tmp;
		if (v_dot(ray->nhit, ray->dir) > 0)
			ray->n_dir = -1;
	}
	return (true);
}

__device__
bool	get_obj_intersection(t_raytracing_tools *r, t_ray *ray, int index)
{
	t_triangle		triangle;
	t_obj_triangle	*lst_triangle;
	t_obj			*o;
	t_list			*tmp;
	float			t;
	float			raytmp;

	// if (r->idx != 0)
	// 	return (0);
	raytmp = ray->t;
	printf("obj inter\n");
	if (!(get_sphere_intersection_obj(r, ray, index)))
		return (false);
	t = INFINITY;
	ray->t = raytmp;
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
		if (get_triangle_intersection_obj(r, &triangle, ray))
		{
			if (ray->t < t)
			{
				t = ray->t;
				ray->nhit = v_cross(v_sub(triangle.v2, triangle.v1),
						v_sub(triangle.v3, triangle.v1));
			}
		}
		//if (r->pix.x == 600 && r->pix.y < 200)
			//printf("addr %p\n", o->triangle->next);
		tmp = tmp->next;
	}
	if (t != INFINITY)
	{
		ray->t = t;
		ray->hit_obj = index;
		ray->hit_type = T_OBJ;
		return (true);
	}
	// if (r->idx == 0)
	// printf("Exit obj_intersection\n");
	return (false);
}
