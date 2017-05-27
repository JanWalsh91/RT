/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_add.cu                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:24:09 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/19 13:09:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Returns the sum of col1 and col2.
*/

__host__ __device__
t_color	c_add(t_color col1, t_color col2)
{
	t_color	col;

	col.r = (col1.r + col2.r > 255) ? 255 : 
	col1.r + col2.r;
	col.g = (col1.g + col2.g > 255) ? 255 : 
	col1.g + col2.g;
	col.b = (col1.b + col2.b > 255) ? 255 : 
	col1.b + col2.b;
	return (col);
}
