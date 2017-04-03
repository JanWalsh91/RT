/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_scale.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 14:20:16 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/03 12:23:51 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Scales a matrix by i.
*/

__host__ __device__
t_matrix	*m_scale(t_matrix *m, double i)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			(*m)[y][x] *= i;
	}
	return (m);
}
