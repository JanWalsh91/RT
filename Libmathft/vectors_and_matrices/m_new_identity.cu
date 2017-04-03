/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new_identity.cu                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:17:57 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/03 12:18:25 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Creates a new 4 by 4 identity matrix.
** Mulpitplying a matrix by an identity matrix does not modify it.
*/

extern __host__ __device__
t_matrix	*m_new_identity(void)
{
	t_matrix	*p_m;

	p_m = m_new();
	(*p_m)[0][0] = 1;
	(*p_m)[1][1] = 1;
	(*p_m)[2][2] = 1;
	(*p_m)[3][3] = 1;
	return (p_m);
}
