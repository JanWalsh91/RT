/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new_rotate.cu                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:22:02 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 13:01:03 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

__host__ __device__
static void m_rot_x(t_matrix *m, float angle);
__host__ __device__
static void m_rot_y(t_matrix *m, float angle);
__host__ __device__
static void m_rot_z(t_matrix *m, float angle);

/*
** Creates a new rotation matrix of angle 'angle' around axis 'axis'
*/

__host__ __device__
void		m_new_rotate(t_matrix *m, float angle, char axis)
{
	if (axis == 'x' || axis == 'X')
		m_rot_x(m, angle);
	else if (axis == 'y' || axis == 'Y')
		m_rot_y(m, angle);
	else if (axis == 'z' || axis == 'Z')
		m_rot_z(m, angle);
}

__host__ __device__
static void m_rot_x(t_matrix *m, float angle)
{
	m_new(m);
	(*m)[0][0] = 1;
	(*m)[1][1] = cos(to_radian(angle));
	(*m)[1][2] = sin(to_radian(angle));
	(*m)[2][1] = -sin(to_radian(angle));
	(*m)[2][2] = cos(to_radian(angle));
}

__host__ __device__
static void m_rot_y(t_matrix *m, float angle)
{
	(*m)[0][0] = cos(to_radian(angle));
	(*m)[0][2] = -sin(to_radian(angle));
	(*m)[1][1] = 1;
	(*m)[2][0] = sin(to_radian(angle));
	(*m)[2][2] = cos(to_radian(angle));
}

__host__ __device__
static void m_rot_z(t_matrix *m, float angle)
{
	m_new(m);
	(*m)[0][0] = cos(to_radian(angle));
	(*m)[0][1] = sin(to_radian(angle));
	(*m)[1][0] = -sin(to_radian(angle));
	(*m)[1][1] = cos(to_radian(angle));
	(*m)[2][2] = 1;
}
