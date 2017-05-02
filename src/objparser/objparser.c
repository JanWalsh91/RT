/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 11:30:06 by talemari          #+#    #+#             */
/*   Updated: 2017/05/02 15:46:59 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void			set_triangle(char *line, t_list **triangle, t_ti *ti)
{
	t_triangle	tri;

	tri.v = (t_vec3i){get_number(line, 0), get_number(line, 1),
		get_number(line, 2)};
	ti->k = ti->k + 1;
	if (ti->j > 0)
	{
		tri.n = (t_vec3i){get_number(line, 3), get_number(line, 4),
			get_number(line, 5)};
	}
	if (triangle == NULL)
		*triangle = ft_lstnew(&tri, sizeof(tri));
	else
		ft_lstadd_end(triangle, ft_lstnew(&tri, sizeof(tri)));
}

void			set_vec(char *line, t_list **vertex, int *i)
{
	t_vec3d		vec;
	char		**tab;

	tab = ft_strsplit(line, ' ');
	vec = (t_vec3d){ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3])};
	if (vertex == NULL)
		*vertex = ft_lstnew(&vec, sizeof(vec));
	else
		ft_lstadd_end(vertex, ft_lstnew(&vec, sizeof(vec)));
	*i = *i + 1;
	ft_freetab(tab);
}

char			*objparser(char *file, t_obj *obj)
{
	int			fd;
	char		*l;
	t_ti		ind;
	t_objlist	olist;

	olist = (t_objlist){NULL, NULL, NULL};
	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	ind = (t_ti){0, 0, 0};
	while (get_next_line(fd, &l) > 0)
	{
		if (ft_strncmp(l, "v ", 2) == 0)
			set_vec(l, &olist.vertex, &ind.i);
		if (ft_strncmp(l, "vn", 2) == 0)
			set_vec(l, &olist.normal, &ind.j);
		if (ft_strncmp(l, "f ", 2) == 0)
			set_triangle(l, &olist.triangle, &ind);
		ft_strdel(&l);
	}
	if (!(obj = set_obj(&olist.vertex, &olist.normal, ind)))
		return ("Error");
	obj->triangle = olist.triangle;
	return (NULL);
}
