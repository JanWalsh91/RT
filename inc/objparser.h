/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:28:17 by tgros             #+#    #+#             */
/*   Updated: 2017/05/30 14:02:48 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJPARSER_H
# define OBJPARSER_H

# include "../Libft/inc/libft.h"
# include "../Libmathft/inc/libmathft.cuh"
# include <stdbool.h>
# include <stdio.h>

typedef struct		s_ti
{
	int				i;
	int				j;
	int				k;
	int				l;
}					t_ti;

typedef struct		s_vec3i
{
	int				x;
	int				y;
	int				z;
}					t_vec3i;

typedef struct		s_vec3d
{
	double			x;
	double			y;
	double			z;
}					t_vec3d;

typedef struct		s_vec3f
{
	float			x;
	float			y;
	float			z;
}					t_vec3f;

typedef struct		t_vec2f
{
	float			x;
	float			y;
}					t_vec2f;

typedef struct		s_obj_triangle
{
	t_vec3i			v;
	t_vec3i			n;
	t_vec3i			t;
}					t_obj_triangle;

typedef struct		s_obj
{
	t_vec3			*vertex;
	t_vec3			*normal;
	t_vec2f			*texture;
	t_list			*triangle;
	t_vec3			far_point1;
}					t_obj;

typedef struct		s_objlist
{
	t_list			*vertex;
	t_list			*normal;
	t_list			*texture;
	t_list			*triangle;
}					t_objlist;

int					ft_isnumeric(char c);
char				*check_line(char *l);
char				*get_float(char *str, float *f, int n);
char				*get_number(char *str, int *res, int n);
char				*get_vector_f(char *l, t_vec3f *v);
char				*get_vector_2f(char *l, t_vec2f *v);
char				*get_vector_i(char *l, t_vec3i *v, int start, int s);
char				*objparser(char *file, t_obj **obj);
char				*objparser_error(char *err, int l);
char				*set_obj(t_obj *obj, t_objlist *olist, t_ti ind);
void				ft_freetab(char **tab);
void				print_triangles(t_obj *obj);

#endif
