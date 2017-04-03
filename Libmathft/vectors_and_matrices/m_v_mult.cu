/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_v_mult.cu                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:10:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/03 12:27:59 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Returns a new vector which is the application of matrix m on vector v.
*/

__host__ __device__
t_vec3	m_v_mult(t_vec3 v, t_matrix *m)
{
	t_vec3	new_m;

	new_m.x = v.x * (*m)[0][0] + v.y * (*m)[1][0] + v.z * (*m)[2][0];
	new_m.y = v.x * (*m)[0][1] + v.y * (*m)[1][1] + v.z * (*m)[2][1];
	new_m.z = v.x * (*m)[0][2] + v.y * (*m)[1][2] + v.z * (*m)[2][2];
	return (new_m);
}
