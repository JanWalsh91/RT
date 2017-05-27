/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new_rotate_axis.cu                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 11:32:07 by tgros             #+#    #+#             */
/*   Updated: 2017/05/26 12:21:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Rotates a vector around an arbitrary axis intersecting with the origin
*/

__host__ __device__
void	m_new_rotate_axis(t_matrix *mat, t_vec3 u, float angle)
{
	m_new_identity(mat);
	(*mat)[0][0] = cos(angle) + (u.x * u.x) * (1 - cos(angle));
	(*mat)[0][1] = u.x * u.y * (1 - cos(angle)) - u.z * sin(angle);
	(*mat)[0][2] = u.x * u.z * (1 - cos(angle)) + u.y * sin(angle);
	(*mat)[1][0] = u.y * u.x * (1 - cos(angle)) + u.z * sin(angle);
	(*mat)[1][1] = cos(angle) + u.y * u.y * (1 - cos(angle));
	(*mat)[1][2] = u.y * u.z * (1 - cos(angle)) - u.x * sin(angle);
	(*mat)[2][0] = u.z * u.x * (1 - cos(angle)) - u.y * sin(angle);
	(*mat)[2][1] = u.z * u.y * (1 - cos(angle)) + u.x * sin(angle);
	(*mat)[2][2] = cos(angle) + u.z * u.z * (1 - cos(angle));
}