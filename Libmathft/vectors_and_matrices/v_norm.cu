/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_norm.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:16:25 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 11:17:11 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Returns the normal of vector vec.
*/

__host__ __device__
t_vec3	v_norm(t_vec3 v)
{
	float	len;

	len = v_length(v);
	if (len > 0)
	{
		v.x *= 1 / len;
		v.y *= 1 / len;
		v.z *= 1 / len;
	}
	return (v);
}
