/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_clamp.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 12:02:26 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 11:16:43 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libmathft.cuh"

/*
** Limits the values of the coords of a vec within the range of min and max.
*/

__host__ __device__
t_vec3	v_clamp(t_vec3 v, float min, float max)
{
	v.x < min ? v.x = min : 0;
	v.x > max ? v.x = max : 0;
	v.y < min ? v.y = min : 0;
	v.y > max ? v.y = max : 0;
	v.z < min ? v.z = min : 0;
	v.z > max ? v.z = max : 0;
	return (v);
}
