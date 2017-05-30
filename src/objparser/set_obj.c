/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:19:19 by talemari          #+#    #+#             */
/*   Updated: 2017/05/30 12:01:08 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/objparser.h"
#include <stdio.h>
#include <math.h>
#include <cuda_runtime.h>

static void			del(void *c, size_t s)
{
	(void)s;
	free(c);
}

static bool			further_dot(t_vec3 v1, t_vec3 v2)
{
	if (fabs(v1.x) > fabs(v2.x) || fabs(v1.y) > fabs(v2.y) ||
			fabs(v1.z) > fabs(v2.z))
		return (true);
	else
		return (false);
}

static t_vec3		*set_array(t_list **v, int j, t_obj *obj)
{
	t_list		*tmp;
	t_vec3		*array;
	t_vec3		temp;
	int			i;

	tmp = *v;
	i = 0;
	obj->far_point1 = (t_vec3){0, 0, 0};
	if (cudaMallocHost((void **)&array, sizeof(t_vec3) * j) != 0)
		return (NULL);
	while (tmp)
	{
		temp = *(t_vec3 *)tmp->content;
		if (further_dot(temp, obj->far_point1) == true)
			obj->far_point1 = temp;
		array[i] = *(t_vec3 *)tmp->content;
		i++;
		tmp = tmp->next;
	}
	ft_lstdel(v, &del);
	return (array);
}

static t_vec3		*set_normal_array(t_list **v, int j)
{
	t_list		*tmp;
	t_vec3		*array;
	int			i;

	tmp = *v;
	i = 0;
	if (cudaMallocHost((void **)&array, sizeof(t_vec3) * j) != 0)
		return (NULL);
	while (tmp)
	{
		array[i] = *(t_vec3 *)tmp->content;
		i++;
		tmp = tmp->next;
	}
	ft_lstdel(v, &del);
	return (array);
}

static t_vec2f		*set_texture_array(t_list **v, int j)
{
	t_list		*tmp;
	t_vec2f		*array;
	int			i;

	tmp = *v;
	i = 0;
	if (cudaMallocHost((void **)&array, sizeof(t_vec2f) * j) != 0)
		return (NULL);
	while (tmp)
	{
		array[i] = *(t_vec2f *)tmp->content;
		i++;
		tmp = tmp->next;
	}
	ft_lstdel(v, &del);
	return (array);
}

char				*set_obj(t_obj *obj, t_objlist *olist, t_ti ind)
{
	if (ind.i > 0)
		if (!(obj->vertex = set_array(&olist->vertex, ind.i, obj)))
			return ("Failed to set vertex array");
	if (ind.j > 0)
		if (!(obj->normal = set_normal_array(&olist->normal, ind.j)))
			return ("Failed to set normal array");
	if (ind.l > 0)
		if (!(obj->texture = set_texture_array(&olist->texture, ind.l)))
			return ("Failed to set texture array");
	return (NULL);
}
