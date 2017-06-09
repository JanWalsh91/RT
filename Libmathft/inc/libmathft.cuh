/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmathft.cuh                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 15:36:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/09 09:49:03 by jwalsh           ###   ########.fr       */
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

typedef struct	s_color
{
	uint8_t 	r;
	uint8_t		g;
	uint8_t		b;
}				t_color;

typedef struct	s_pt2
{
	int			x;
	int			y;
}				t_pt2;

typedef struct	s_dpt2
{
	float		x;
	float		y;
}				t_dpt2;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;


typedef float	t_matrix[4][4];

EXT
CUDA_HOSTDEV
unsigned long	ft_abs(long n);
CUDA_HOSTDEV
long			ft_power(int n, int p);
CUDA_HOSTDEV
float			to_radian(float a);
CUDA_HOSTDEV
int				ft_round(float i);
CUDA_HOSTDEV
int				ft_rgb_mix(int *colors, int n);
CUDA_HOSTDEV
void			ft_swap(int *a, int *b);
CUDA_HOSTDEV
void			ft_swapf(float *a, float *b);
CUDA_HOSTDEV
float			ft_clampf(float i, float min, float max);

/*
** Colors
*/

CUDA_HOSTDEV
t_color			c_add(t_color col1, t_color col2);
CUDA_HOSTDEV
t_color			c_sub(t_color col1, t_color col2);
CUDA_HOSTDEV
t_color			c_min(t_color col1, t_color col2);
CUDA_HOSTDEV
t_color			c_mult(t_color col1, t_color col2);
CUDA_HOSTDEV
t_color			c_new(int r, int g, int b);
CUDA_HOSTDEV
t_color			c_scale(t_color v, float i);
CUDA_HOSTDEV
t_color			vec_to_col(t_vec3 vec);
CUDA_HOSTDEV
t_vec3			col_to_vec(t_color col);

/*
** 3 x 3 Vector functions
*/

CUDA_HOSTDEV
t_vec3			v_add(t_vec3 vec1, t_vec3 vec2);
CUDA_HOSTDEV
t_vec3			v_cross(t_vec3 vec1, t_vec3 vec2);
CUDA_HOSTDEV
float			v_dot(t_vec3 vec1, t_vec3 vec2);
CUDA_HOSTDEV
int				v_isnan(t_vec3 v);
CUDA_HOSTDEV
float			v_length(t_vec3 vec);
CUDA_HOSTDEV
float			v_dist(t_vec3 p1, t_vec3 p2);
CUDA_HOSTDEV
t_vec3			v_clamp(t_vec3 v, float min, float max);
CUDA_HOSTDEV
t_vec3			v_mult(t_vec3 vec, t_vec3 i);
CUDA_HOSTDEV
t_vec3			v_new(float x, float y, float z);
CUDA_HOSTDEV
t_vec3			v_norm(t_vec3 vec);
CUDA_HOSTDEV
t_vec3			v_scale(t_vec3 vec1, float i);
CUDA_HOSTDEV
t_vec3			v_sub(t_vec3 vec1, t_vec3 vec2);


/*
** 4 x 4 Matrix functions
*/

CUDA_HOSTDEV
void			m_add(t_matrix *m1, t_matrix *m2);
CUDA_HOSTDEV
t_matrix		*m_inverse(t_matrix *m);
CUDA_HOSTDEV
void			m_mult(t_matrix *m1, t_matrix *m2);
CUDA_HOSTDEV
void			m_new_identity(t_matrix *m);
CUDA_HOSTDEV
void			m_new_rodriguez(t_matrix *m, t_vec3 a, t_vec3 b);
CUDA_HOSTDEV
void			m_new_rotate(t_matrix *m, float angle, char axis);
CUDA_HOSTDEV
void			m_new_rotate_axis(t_matrix *mat, t_vec3 u, float angle);
CUDA_HOSTDEV
t_vec3			p_rotate_axis(t_vec3 d1, t_vec3 d2, t_vec3 rot_p, t_vec3 point);
CUDA_HOSTDEV
void			m_new_scale(t_matrix *m, float i);
CUDA_HOSTDEV
void			m_new(t_matrix *m);
CUDA_HOSTDEV
t_vec3			m_p_mult(t_vec3 p, t_matrix *m);
CUDA_HOSTDEV
void			m_scale(t_matrix *m, float i);
CUDA_HOSTDEV
t_matrix		*m_translate(t_matrix *m, t_vec3 v);
CUDA_HOSTDEV
t_vec3			m_v_mult(t_vec3 v, t_matrix *m);
EXT_END

#endif
