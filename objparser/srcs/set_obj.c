/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:19:19 by talemari          #+#    #+#             */
/*   Updated: 2017/04/29 12:53:35 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objparser.h"
#include <stdio.h>

void		del(void *c, size_t s)
{
	(void)s;
	free(c);
}

t_vec3d		*set_array(t_list **v, int j)
{
	t_list		*tmp;
	t_vec3d		*array;
	int			i;

	tmp = *v;
	i = 0;
	if (!(array = (t_vec3d *)malloc(sizeof(t_vec3d) * j)))
		return(NULL);
	while (tmp)
	{
		array[i] = *(t_vec3d *)tmp->content;
		i++;
		tmp = tmp->next;
	}
	ft_lstdel(v, &del);
	return (array);
}

t_obj		*set_obj(t_list **v, t_list **n, t_ti ind)
{
	t_obj		*res;

	if (!(res = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	if (ind.i > 0)
		res->vertex = set_array(v, ind.i);
	if (ind.j > 0)
		res->normal = set_array(n, ind.j);
	return (res);
}
