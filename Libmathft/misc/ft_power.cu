/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.cu                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 15:10:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 15:26:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns n to the power of p.
*/

#include "libmathft.cuh"

__host__ __device__
long	ft_power(int n, int p)
{
	long n1;

	n1 = n;
	if (!p || !n || p < 0)
		return (0);
	if (p == 0)
		return (1);
	while (p != 1)
	{
		n1 *= n;
		p--;
	}
	return (n1);
}
