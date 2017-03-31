/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new.cu                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 17:06:27 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 15:26:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Creates a new 4 by 4 matrix and sets its values to 0;
*/

__host__ __device__
t_matrix	m_new(void)
{
	int			x;
	int			y;
	t_matrix	m;

	if (!(m = (t_matrix)malloc(sizeof(double *) * 4)))
		return (m);
	y = -1;
	while (++y < 4)
	{
		if (!(m[y] = (double *)malloc(sizeof(double) * 4)))
			return (m);
		x = -1;
		while (++x < 4)
			m[y][x] = 0;
	}
	return (m);
}
