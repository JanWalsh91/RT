/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:19:19 by talemari          #+#    #+#             */
/*   Updated: 2017/05/10 16:12:56 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/objparser.h"
#include <stdio.h>

static void			del(void *c, size_t s)
{
	(void)s;
	free(c);
}

static t_vec3f		*set_array(t_list **v, int j)
{
	t_list		*tmp;
	t_vec3f		*array;
	int			i;

	tmp = *v;
	i = 0;
	if (!(array = (t_vec3f *)malloc(sizeof(t_vec3d) * j)))
		return (NULL);
	while (tmp)
	{
		array[i] = *(t_vec3f *)tmp->content;
		i++;
		tmp = tmp->next;
	}
	ft_lstdel(v, &del);
	return (array);
}

char				*set_obj(t_obj *obj, t_list **v, t_list **n, t_ti ind)
{
	if (ind.i > 0)
		if (!(obj->vertex = set_array(v, ind.i)))
			return ("Failed to set vertex array");
	if (ind.j > 0)
		if (!(obj->normal = set_array(n, ind.j)))
			return ("Failed to set normal array");
	return (NULL);
}
