/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_translate.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:23:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/03 12:24:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Translates a matrix by vector v.
*/

__host__ __device__
t_matrix	*m_translate(t_matrix *m, t_vec3 v)
{
	(*m)[0][3] += v.x;
	(*m)[1][3] += v.y;
	(*m)[2][3] += v.z;
	return (m);
}
