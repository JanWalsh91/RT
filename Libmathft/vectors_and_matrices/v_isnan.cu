/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_isnan.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 13:25:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 15:26:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Checks if a vector's coordinates are numbers.
** Returns 1 if all coords are NAN.
*/

__host__ __device__
int	v_isnan(t_vec3 v)
{
	return (isnan(v.x) && isnan(v.y) && isnan(v.z));
}
