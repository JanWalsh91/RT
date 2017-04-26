/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new.cu                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 17:06:27 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 12:55:39 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"
#include <stdio.h>

/*
** Creates a new 4 by 4 matrix and sets its values to 0;
*/

__host__ __device__
void	m_new(t_matrix *m)
{
	int			x;
	int			y;

	printf("m_new\n");
	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			(*m)[y][x] = 0;
	}
	y = -1;
	while(++y < 4)
	{
		x = -1;
		while (++x < 4)
			printf("%f ", (*m)[y][x]);
		printf("\n");
	}
	printf("end of m_new\n");
}
