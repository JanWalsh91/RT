/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mult.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:17:19 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 13:18:09 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Combines two matrices.
*/

__host__ __device__
void	m_mult(t_matrix *m1, t_matrix *m2)
{
	int			x;
	int			y;
	t_matrix	res;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			res[y][x] = (*m1)[y][0] * (*m2)[0][x] +
				(*m1)[y][1] * (*m2)[1][x] +
				(*m1)[y][2] * (*m2)[2][x] +
				(*m1)[y][3] * (*m2)[3][x];
		}
	}
	memcpy(m1, &res, sizeof(t_matrix));
}
