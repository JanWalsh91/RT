/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_radian.cu                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 17:30:27 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 15:26:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Converts degrees to radians.
*/

__host__ __device__
double	to_radian(double a)
{
	return (a * M_PI / 180);
}
