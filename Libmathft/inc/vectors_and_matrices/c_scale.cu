/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_scale.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:25:08 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 11:57:02 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Scales a color by i.
*/

__host__ __device__
t_color	c_scale(t_color v, float i)
{
	t_color	col;

	if (v.r * i > 255)
		col.r = 255;
	else if (v.r * i < 0)
		col.r = 0;
	else
		col.r = v.r * i;
	if (v.g * i > 255)
		col.g = 255;
	else if (v.g * i < 0)
		col.g = 0;
	else
		col.g = v.g * i;
	if (v.b * i > 255)
		col.b = 255;
	else if (v.b * i < 0)
		col.b = 0;
	else
		col.b = v.b * i;
	return (col);
}
