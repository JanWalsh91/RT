/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new_identity.cu                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:17:57 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 12:56:06 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"
#include <stdio.h>
/*
** Creates a new 4 by 4 identity matrix.
** Multiplying a matrix by an identity matrix does not modify it.
*/

extern __host__ __device__
void	m_new_identity(t_matrix	*m)
{
	printf("new identity matrix:\n");
	m_new(m);
	int x, y = -1;
	printf("back in m_new-identities\n");
	while(++y < 4)
	{
		x = -1;
		while (++x < 4)
			printf("%f ", (*m)[y][x]);
		printf("\n");
	}
	(*m)[0][0] = 1;
	(*m)[1][1] = 1;
	(*m)[2][2] = 1;
	(*m)[3][3] = 1;
	y = -1;
	printf("after putting middle earth values to 1\n");
	while(++y < 4)
	{
		x = -1;
		while (++x < 4)
			printf("%f ", (*m)[y][x]);
		printf("\n");
	}
	printf("n_new_identity end\n");
}
