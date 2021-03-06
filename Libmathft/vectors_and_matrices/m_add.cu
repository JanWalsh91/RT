/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_add.cu                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:19:07 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 13:05:39 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Adds two matrices together.
*/

__host__ __device__
void	m_add(t_matrix *m1, t_matrix *m2)
{
	int			y;
	int			x;

	y = -1;
	while (++y < 3)
	{
		x = -1;
		while (++x < 3)
			(*m1)[y][x] = (*m1)[y][x] + (*m2)[y][x];
	}
}
