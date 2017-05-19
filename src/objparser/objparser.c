/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:26:15 by tgros             #+#    #+#             */
/*   Updated: 2017/05/19 09:57:50 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/objparser.h"
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static char			*set_triangle(char *line, t_list **triangle, t_ti *ti)
{
	t_obj_triangle	tri;
	char			*err;

	if ((err = get_vector_i(line, &tri.v, 0)) != NULL)
		return (err);
	ti->k = ti->k + 1;
	if (ti->j > 0)
	{
		if ((err = get_vector_i(line, &tri.n, 3)) != NULL)
			return (err);
	}
	if (*triangle == NULL)
		*triangle = ft_lstnew(&tri, sizeof(tri));
	else
		ft_lstadd_end(triangle, ft_lstnew(&tri, sizeof(tri)));
	return (NULL);
}

static char			*set_vec(char *line, t_list **vertex, int *i)
{
	t_vec3f		vec;
	char		*err;

	if ((err = get_vector_f(line, &vec)) != NULL)
		return (err);
	if (*vertex == NULL)
		*vertex = ft_lstnew(&vec, sizeof(vec));
	else
		ft_lstadd_end(vertex, ft_lstnew(&vec, sizeof(vec)));
	*i = *i + 1;
	return (NULL);
}

static char			*line_parser(int fd, t_objlist *olist, t_ti *ind)
{
	char		*err;
	int			lbuf;
	char		*l;

	err = NULL;
	while ((lbuf = get_next_line(fd, &l)) > 0)
	{
		if (ft_strlen(l) < 1)
			continue;
		if (ft_strncmp(l, "v ", 2) == 0)
			err = set_vec(l, &olist->vertex, &ind->i);
		else if (ft_strncmp(l, "vn ", 3) == 0)
			err = set_vec(l, &olist->normal, &ind->j);
		else if (ft_strncmp(l, "f ", 2) == 0)
			err = set_triangle(l, &olist->triangle, ind);
		else
			err = "Format mismatch";
		ft_strdel(&l);
		if (err)
			return (err);
	}
	return (NULL);
}

char				*objparser(char *file, t_obj *obj)
{
	int			fd;
	t_ti		ind;
	char		*err;
	t_objlist	olist;

	olist = (t_objlist){NULL, NULL, NULL};
	if ((fd = open(file, O_RDONLY)) < 0)
		return ("Failed to open file");
	ind = (t_ti){0, 0, 0};
	err = line_parser(fd, &olist, &ind);
	if (err)
		return (err);
	if ((err = set_obj(obj, &olist.vertex, &olist.normal, ind)) != NULL)
		return (err);
	obj->triangle = olist.triangle;
	return (NULL);
}
