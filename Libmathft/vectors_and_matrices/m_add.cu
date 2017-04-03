/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_add.cu                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:19:07 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/03 12:26:59 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Adds two matrices together.
*/

__host__ __device__
t_matrix	*m_add(t_matrix *m1, t_matrix *m2)
{
	int			y;
	int			x;
	t_matrix	*m;

	m = m_new_identity();
	y = -1;
	while (++y < 3)
	{
		x = -1;
		while (++x < 3)
			(*m)[y][x] = (*m1)[y][x] + (*m2)[y][x];
	}
	return (m);
}
