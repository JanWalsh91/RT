/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_length.cu                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:24:51 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 15:26:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Returns the length of the vector.
*/

__host__ __device__
double	v_length(t_vec3 v)
{
	return (sqrt(v_dot(v, v)));
}
