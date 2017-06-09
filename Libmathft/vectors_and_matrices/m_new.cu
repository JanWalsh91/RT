/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new.cu                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 17:06:27 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/09 09:26:55 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Creates a new 4 by 4 matrix and sets its values to 0;
*/

__host__ __device__
void	m_new(t_matrix *m)
{
	int			x;
	int			y;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			(*m)[y][x] = 0;
	}
}
