/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new_identity.cu                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:17:57 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/09 09:26:50 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Creates a new 4 by 4 identity matrix.
** Multiplying a matrix by an identity matrix does not modify it.
*/

extern __host__ __device__
void	m_new_identity(t_matrix	*m)
{
	m_new(m);
	(*m)[0][0] = 1;
	(*m)[1][1] = 1;
	(*m)[2][2] = 1;
	(*m)[3][3] = 1;
}
