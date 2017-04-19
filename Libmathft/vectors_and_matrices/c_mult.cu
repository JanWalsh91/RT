/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_mult.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:27:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/19 13:27:33 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Multiplies color col1 by col col2.
*/

__host__ __device__
t_color	c_mult(t_color col1, t_color col2)
{
	t_color	col;

	col.r = (col1.r * col2.r > 255) ? 255 :
	col1.r * col2.r;
	col.g = (col1.g * col2.g > 255) ? 255 :
	col1.g * col2.g;
	col.b = (col1.b * col2.b > 255) ? 255 :
	col1.b * col2.b;
	return (col);
}
