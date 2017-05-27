/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_scale.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:25:08 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 11:17:15 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Scales a vector by i.
*/

__host__ __device__
t_vec3	v_scale(t_vec3 v, float i)
{
	t_vec3	vec;

	vec.x = v.x * i;
	vec.y = v.y * i;
	vec.z = v.z * i;
	return (vec);
}
