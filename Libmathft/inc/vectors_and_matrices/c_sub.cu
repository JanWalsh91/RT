/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_sub.cu                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:22:17 by tgros             #+#    #+#             */
/*   Updated: 2017/05/16 16:23:29 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Returns the sub of col1 and col2.
*/

__host__ __device__
t_color	c_sub(t_color col1, t_color col2)
{
	t_color	col;

	col.r = (col1.r - col2.r < 0) ? 0 : 
	col1.r - col2.r;
	col.g = (col1.g - col2.g < 0) ? 0 : 
	col1.g - col2.g;
	col.b = (col1.b - col2.b < 0) ? 0 : 
	col1.b - col2.b;
	return (col);
}
