/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 10:58:52 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 15:26:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns the absolute value of int n.
*/

#include "libmathft.cuh"

__host__ __device__
unsigned long	ft_abs(long n)
{
	unsigned long	result;

	result = (n < 0) ? -n : n;
	return (result);
}
