/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_sub.cu                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:25:19 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 15:26:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Subtracts vec2 from vec1.
*/

__host__ __device__
t_vec3	v_sub(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	vec;

	vec.x = vec1.x - vec2.x;
	vec.y = vec1.y - vec2.y;
	vec.z = vec1.z - vec2.z;
	return (vec);
}
