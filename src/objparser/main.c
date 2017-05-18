/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:26:15 by tgros             #+#    #+#             */
/*   Updated: 2017/05/10 16:08:41 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/objparser.h"
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (int ac, char **av)
{
	t_obj		*obj;
	t_triangle	*tmp2;
	char		*file;
	char		*ret;

	file = av[1];
	if (ac != 2)
		return (0);
	obj = (t_obj *)malloc(sizeof(t_obj));
	ret = objparser(file, obj);
	if (ret)
	{
		ft_putendl(ret);
		return (0);
	}
	while (obj->triangle != NULL)
	{
		ft_putendl("------TRIANGLE------");
		tmp2 = (t_triangle *)obj->triangle->content;
		printf("v1 = %f, %f, %f\n", obj->vertex[tmp2->v.x].x, obj->vertex[tmp2->v.x].y, obj->vertex[tmp2->v.x].z);
		printf("v2 = %f, %f, %f\n", obj->vertex[tmp2->v.y].x, obj->vertex[tmp2->v.y].y, obj->vertex[tmp2->v.y].z);
		printf("v3 = %f, %f, %f\n", obj->vertex[tmp2->v.z].x, obj->vertex[tmp2->v.z].y, obj->vertex[tmp2->v.z].z);
		obj->triangle = obj->triangle->next;
	}
	return (0);
}
