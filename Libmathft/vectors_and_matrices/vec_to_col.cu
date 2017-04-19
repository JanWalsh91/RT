/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_col.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:29:54 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/19 13:34:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Converts a t_vec3 to a t_color
*/

__host__ __device__
t_color		vec_to_col(t_vec3 vec)
{
	t_color	col;

	if (vec.x > 255)
		col.r = 255;
	else if (vec.x < 0 || isnan(vec.x))
		col.r = 0;
	else
		col.r = (uint8_t)vec.x;
	if (vec.y > 255)
		col.g = 255;
	else if (vec.y < 0 || isnan(vec.y))
		col.g = 0;
	else
		col.g = (uint8_t)vec.y;
	if (vec.z > 255)
		col.b = 255;
	else if (vec.z < 0 || isnan(vec.z))
		col.b = 0;
	else
		col.b = (uint8_t)vec.z;
	return (col);
}