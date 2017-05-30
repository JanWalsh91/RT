/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:26:15 by tgros             #+#    #+#             */
/*   Updated: 2017/05/30 14:08:38 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/objparser.h"
#include "../../inc/rt.cuh"
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cuda.h>
#include <cuda_runtime.h>

static t_list		*lstnew_cuda(void const *content, size_t content_size)
{
	t_list	*list;
	void	*new_content;

	if (cudaMallocHost((void **)&new_content, content_size) != 0)
		return (NULL);
	if (!content)
	{
		new_content = NULL;
		content_size = 0;
	}
	else
		ft_memcpy(new_content, content, content_size);
	if (cudaMallocHost((void **)&list, sizeof(t_list)) != 0)
		return (NULL);
	list->content = new_content;
	list->content_size = content_size;
	list->next = NULL;
	return (list);
}

static char			*set_triangle(char *line, t_list **triangle, t_ti *ti)
{
	t_obj_triangle	tri;
	char			*err;
	int				s;

	s = 1;
	s = (ti->j > 0) ? s + 1 : s;
	s = (ti->l > 0) ? s + 1 : s;
	if ((err = get_vector_i(line, &tri.v, 0, s)) != NULL)
		return (err);
	ti->k = ti->k + 1;
	if (ti->j > 0)
	{
		if ((err = get_vector_i(line, &tri.n, 1, s)) != NULL)
			return (err);
	}
	if (ti->l > 0)
	{
		if ((err = get_vector_i(line, &tri.t, 2, s)) != NULL)
			return (err);
	}
	if (*triangle == NULL)
		*triangle = lstnew_cuda(&tri, sizeof(tri));
	else
		ft_lstadd_end(triangle, lstnew_cuda(&tri, sizeof(tri)));
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

static char			*set_vt(char *line, t_list **texture, int *i)
{
	t_vec2f		vec;
	char		*err;

	if ((err = get_vector_2f(line, &vec)) != NULL)
		return (err);
	if (*texture == NULL)
		*texture = ft_lstnew(&vec, sizeof(vec));
	else
		ft_lstadd_end(texture, ft_lstnew(&vec, sizeof(vec)));
	*i = *i + 1;
	return (NULL);
}

static char			*line_parser(int fd, t_objlist *olist, t_ti *ind)
{
	char		*err;
	int			lbuf;
	char		*l;
	int			i;

	err = NULL;
	i = 0;
	while (i++ >= 0 && (lbuf = get_next_line(fd, &l)) > 0)
	{
		ft_putendl(l);
		if (ft_strlen(l) < 1)
			continue;
		if (ft_strncmp(l, "v ", 2) == 0)
			err = set_vec(l, &olist->vertex, &ind->i);
		else if (ft_strncmp(l, "vn ", 3) == 0)
			err = set_vec(l, &olist->normal, &ind->j);
		else if (ft_strncmp(l, "vt ", 3) == 0)
			err = set_vt(l, &olist->texture, &ind->l);
		else if (ft_strncmp(l, "f ", 2) == 0)
			err = set_triangle(l, &olist->triangle, ind);
		ft_strdel(&l);
		if (err)
			return (objparser_error(err, i));
	}
	return (NULL);
}

char				*objparser(char *file, t_obj **res)
{
	int			fd;
	t_ti		ind;
	char		*err;
	t_objlist	olist;
	t_obj		*obj;

	olist = (t_objlist){NULL, NULL, NULL};
	ft_putendl("Allocating obj");
	if (cudaMallocHost((void **)&obj, sizeof(t_obj)) != 0)
			return ("CudaMalloc failed");
	if ((fd = open(file, O_RDONLY)) < 0)
		return ("Failed to open file");
	ind = (t_ti){0, 0, 0};
	err = line_parser(fd, &olist, &ind);
	if (err)
		return (err);
	if ((err = set_obj(obj, &olist, ind)) != NULL)
		return (err);
	obj->triangle = olist.triangle;
	*res = obj;
	printf("ad : %p\n", obj);
	print_triangles(*res);
	return (NULL);
}
