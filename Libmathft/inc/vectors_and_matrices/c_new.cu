/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_new.cu                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 14:22:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/19 13:26:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Creates and returns a new color with values r, g, and b.
*/

__host__ __device__
t_color	c_new(int r, int g, int b)
{
	t_color	col;

	if (r > 255)
		col.r = 255;
	else if (r < 0)
		col.r = 0;
	else
		col.r = r;
	if (g > 255)
		col.g = 255;
	else if (g < 0)
		col.g = 0;
	else
		col.g = g;
	if (b > 255)
		col.b = 255;
	else if (b < 0)
		col.b = 0;
	else
		col.b = b;
	return (col);
}
