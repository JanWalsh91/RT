/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:28:17 by tgros             #+#    #+#             */
/*   Updated: 2017/05/04 14:28:18 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJPARSER_H
# define OBJPARSER_H

# include "../Libft/inc/libft.h"
# include <stdbool.h>

typedef struct		s_ti
{
	int				i;
	int				j;
	int				k;
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

typedef struct		s_triangle
{
	t_vec3i			v;
	t_vec3i			n;
}					t_triangle;

typedef struct		s_obj
{
	t_vec3d			*vertex;
	t_vec3d			*normal;
	t_list			*triangle;
}					t_obj;

typedef struct		s_objlist
{
	t_list			*vertex;
	t_list			*normal;
	t_list			*triangle;
}					t_objlist;

int					get_number(char *str, int n);
int					ft_isnumeric(char c);
char				*objparser(char *file, t_obj *obj);
t_obj				*set_obj(t_list **v, t_list **n, t_ti ind);
void				ft_freetab(char **tab);

#endif
