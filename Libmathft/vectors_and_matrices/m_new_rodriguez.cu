/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new_rodriguez.cu                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:18:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/09 09:31:24 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Calculates and returns the roation matrix from vector b to vector a.
*/

__host__ __device__
void	get_value_rodriguez(t_matrix n, t_vec3 v)
{
	n[1][0] = v.z;
	n[2][0] = -v.y;
	n[0][1] = -v.z;
	n[2][1] = v.x;
	n[0][2] = v.y;
	n[1][2] = -v.x;
}

__host__ __device__
void	m_new_rodriguez(t_matrix *m, t_vec3 a, t_vec3 b)
{
	t_matrix	n;
	t_matrix	identity;
	t_vec3		v;
	double		angle;
	int			i;

	v = v_norm(v_cross(a, b));
	angle = acos(v_dot(a, b) / ((v_length(a) * v_length(b))));
	m_new_identity(&n);
	m_new_identity(&identity);
	get_value_rodriguez(n, v);
	m_scale(&n, sin(angle));
	m_add(&n, &identity);
	memcpy(m, &n, sizeof(t_matrix));
	m_mult(&n, &n);
	m_scale(&n, 1 - cos(angle));
	m_add(m, &n);
	i = -1;
	while (++i < 3)
	{
		(*m)[3][i] = 0;
		(*m)[i][3] = 0;
	}
	(*m)[3][3] = 1;
}
