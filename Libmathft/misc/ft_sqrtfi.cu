/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrtfi.cu                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 13:36:57 by tgros             #+#    #+#             */
/*   Updated: 2017/05/10 13:57:16 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

__host__ __device__
t_im	ft_sqrtfi(t_im im)
{
	float	r;
	float	x;
	float	y;
	t_im	res;

	r = sqrtf(im.r * im.r + im.i * im.i);
	y = sqrtf((r - im.r) / 2.0);
	x = im.i / (2.0 * y);
	res.r = x;
	res.i = y;
	return (res);
}

