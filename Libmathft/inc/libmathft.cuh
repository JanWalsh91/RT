/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmathft.cuh                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 15:36:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 15:27:45 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATHFT_H
# define LIBMATHFT_H

# include <math.h>
# include <stdlib.h>

# include <cuda/cuda.h>

typedef struct	s_pt2
{
	int			x;
	int			y;
}				t_pt2;

typedef struct	s_dpt2
{
	double		x;
	double		y;
}				t_dpt2;

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef double	**t_matrix;

__host__ __device__
unsigned long	ft_abs(long n);
__host__ __device__
long			ft_power(int n, int p);
__host__ __device__
double			to_radian(double a);
__host__ __device__
int				ft_round(float i);
__host__ __device__
int				ft_rgb_mix(int *colors, int n);
__host__ __device__
void			ft_swap(int *a, int *b);
__host__ __device__
void			ft_swapd(double *a, double *b);

/*
** 3 x 3 Vector functions
*/

__host__ __device__
t_vec3			v_add(t_vec3 vec1, t_vec3 vec2);
__host__ __device__
t_vec3			v_cross(t_vec3 vec1, t_vec3 vec2);
__host__ __device__
double			v_dot(t_vec3 vec1, t_vec3 vec2);
__host__ __device__
int				v_isnan(t_vec3 v);
__host__ __device__
double			v_length(t_vec3 vec);
__host__ __device__
double			v_dist(t_vec3 p1, t_vec3 p2);
__host__ __device__
t_vec3			v_clamp(t_vec3 v, double min, double max);
__host__ __device__
t_vec3			v_mult(t_vec3 vec, t_vec3 i);
__host__ __device__
t_vec3			v_new(double x, double y, double z);
__host__ __device__
t_vec3			v_norm(t_vec3 vec);
__host__ __device__
t_vec3			v_scale(t_vec3 vec1, double i);
__host__ __device__
t_vec3			v_sub(t_vec3 vec1, t_vec3 vec2);


/*
** 4 x 4 Matrix functions
*/

__host__ __device__
t_matrix		m_add(t_matrix m1, t_matrix m2);
__host__ __device__
t_matrix		m_inverse(t_matrix m);
__host__ __device__
t_matrix		m_mult(t_matrix m1, t_matrix m2);
__host__ __device__
t_matrix		m_new_identity(void);
__host__ __device__
t_matrix		m_new_rodriguez(t_vec3 a, t_vec3 b);
__host__ __device__
t_matrix		m_new_rotate(float angle, char axis);
__host__ __device__
t_matrix		m_new_scale(double i);
__host__ __device__
t_matrix		m_new(void);
__host__ __device__
t_vec3			m_p_mult(t_vec3 p, t_matrix m);
__host__ __device__
t_matrix		m_scale(t_matrix m, double i);
__host__ __device__
t_matrix		m_translate(t_matrix m, t_vec3 v);
__host__ __device__
t_vec3			m_v_mult(t_vec3 v, t_matrix m);

#endif
