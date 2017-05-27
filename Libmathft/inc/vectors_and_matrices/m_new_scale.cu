/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_new_scale.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 17:10:07 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 12:58:05 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Creates a new scaling matrix which will scale a matrix or vector of all
** coordinates by i.
*/

__host__ __device__
void	m_new_scale(t_matrix *m, float i)
{
	(*m)[0][0] = i;
	(*m)[1][1] = i;
	(*m)[2][2] = i;
}
