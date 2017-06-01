/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:26:15 by tgros             #+#    #+#             */
/*   Updated: 2017/05/30 15:28:19 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/objparser.h"
#include "../../inc/rt.cuh"
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void print_triangles(t_obj *obj)
{
	t_obj_triangle	*tmp2;
	t_list			*tmp;

	tmp = obj->triangle;
	while (tmp != NULL)
	{
		printf("------TRIANGLE------\n");
		tmp2 = (t_obj_triangle *)tmp->content;
		printf("Adresse : %p\n", tmp);
//		printf("Faces : %d/%d/%d, %d/%d/%d, %d/%d/%d\n", tmp2->v.x, tmp2->n.x, tmp2->t.x, tmp2->v.y, tmp2->n.y,
//				tmp2->t.y, tmp2->v.z, tmp2->n.z, tmp2->t.z);
		printf("v1 = %f, %f, %f\n", obj->vertex[tmp2->v.x].x, obj->vertex[tmp2->v.x].y, obj->vertex[tmp2->v.x].z);
		printf("v2 = %f, %f, %f\n", obj->vertex[tmp2->v.y].x, obj->vertex[tmp2->v.y].y, obj->vertex[tmp2->v.y].z);
		printf("v3 = %f, %f, %f\n", obj->vertex[tmp2->v.z].x, obj->vertex[tmp2->v.z].y, obj->vertex[tmp2->v.z].z);
		if (obj->normal != NULL)
		{
			printf("vn1 = %f, %f, %f\n", obj->normal[tmp2->n.x].x, obj->vertex[tmp2->n.x].y, obj->vertex[tmp2->n.x].z);
			printf("vn2 = %f, %f, %f\n", obj->normal[tmp2->n.y].x, obj->vertex[tmp2->n.y].y, obj->vertex[tmp2->n.y].z);
			printf("vn3 = %f, %f, %f\n", obj->normal[tmp2->n.z].x, obj->vertex[tmp2->n.z].y, obj->vertex[tmp2->n.z].z);
		}
		if (obj->texture != NULL)
		{
			printf("vt1 = %f, %f\n", obj->texture[tmp2->t.x].x, obj->texture[tmp2->t.x].y);
			printf("vt2 = %f, %f\n", obj->texture[tmp2->t.y].x, obj->texture[tmp2->t.y].y);
			printf("vt3 = %f, %f\n", obj->texture[tmp2->t.z].x, obj->texture[tmp2->t.z].y);
		}
		tmp = tmp->next;
	}
	printf("Further point : %f, %f, %f\n", obj->far_point1.x, obj->far_point1.y, obj->far_point1.z);
}
