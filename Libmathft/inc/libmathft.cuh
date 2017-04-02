/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmathft.cuh                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 15:36:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/01 12:24:44 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATHFT_H
# define LIBMATHFT_H

# include <math.h>
# include <stdlib.h>

# include <cuda.h>

#ifdef __CUDACC__
#define CUDA_HOSTDEV __host__ __device__
#define EXT extern "C" {
#define EXT_END }
#else
#define CUDA_HOSTDEV
#define EXT
#define EXT_END
#endif

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

EXT
CUDA_HOSTDEV
unsigned long	ft_abs(long n);
CUDA_HOSTDEV
long			ft_power(int n, int p);
CUDA_HOSTDEV
double			to_radian(double a);
CUDA_HOSTDEV
int				ft_round(float i);
CUDA_HOSTDEV
int				ft_rgb_mix(int *colors, int n);
CUDA_HOSTDEV
void			ft_swap(int *a, int *b);
CUDA_HOSTDEV
void			ft_swapd(double *a, double *b);
CUDA_HOSTDEV
double			ft_clampd(double i, double min, double max);

/*
** 3 x 3 Vector functions
*/

CUDA_HOSTDEV
t_vec3			v_add(t_vec3 vec1, t_vec3 vec2);
CUDA_HOSTDEV
t_vec3			v_cross(t_vec3 vec1, t_vec3 vec2);
CUDA_HOSTDEV
double			v_dot(t_vec3 vec1, t_vec3 vec2);
CUDA_HOSTDEV
int				v_isnan(t_vec3 v);
CUDA_HOSTDEV
double			v_length(t_vec3 vec);
CUDA_HOSTDEV
double			v_dist(t_vec3 p1, t_vec3 p2);
CUDA_HOSTDEV
t_vec3			v_clamp(t_vec3 v, double min, double max);
CUDA_HOSTDEV
t_vec3			v_mult(t_vec3 vec, t_vec3 i);
CUDA_HOSTDEV
t_vec3			v_new(double x, double y, double z);
CUDA_HOSTDEV
t_vec3			v_norm(t_vec3 vec);
CUDA_HOSTDEV
t_vec3			v_scale(t_vec3 vec1, double i);
CUDA_HOSTDEV
t_vec3			v_sub(t_vec3 vec1, t_vec3 vec2);


/*
** 4 x 4 Matrix functions
*/

CUDA_HOSTDEV
t_matrix		m_add(t_matrix m1, t_matrix m2);
CUDA_HOSTDEV
t_matrix		m_inverse(t_matrix m);
CUDA_HOSTDEV
t_matrix		m_mult(t_matrix m1, t_matrix m2);
CUDA_HOSTDEV
t_matrix		m_new_identity(void);
CUDA_HOSTDEV
t_matrix		m_new_rodriguez(t_vec3 a, t_vec3 b);
CUDA_HOSTDEV
t_matrix		m_new_rotate(float angle, char axis);
CUDA_HOSTDEV
t_matrix		m_new_scale(double i);
CUDA_HOSTDEV
t_matrix		m_new(void);
CUDA_HOSTDEV
t_vec3			m_p_mult(t_vec3 p, t_matrix m);
CUDA_HOSTDEV
t_matrix		m_scale(t_matrix m, double i);
CUDA_HOSTDEV
t_matrix		m_translate(t_matrix m, t_vec3 v);
CUDA_HOSTDEV
t_vec3			m_v_mult(t_vec3 v, t_matrix m);
EXT_END

#endif
