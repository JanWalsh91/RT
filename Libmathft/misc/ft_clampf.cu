/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clampf.cu                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:13:21 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 11:28:43 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Changes the value of int i to max if i > max, or to min if i < min.
*/

#include "libmathft.cuh"

__host__ __device__
float	ft_clampf(float i, float min, float max)
{
	i < min ? i = min : 0;
	i > max ? i = max : 0;
	return (i);
}
