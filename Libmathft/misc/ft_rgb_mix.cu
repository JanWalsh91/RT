/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_mix.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:50:29 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 15:26:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

__host__ __device__
int	ft_rgb_mix(int *colors, int n)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = -1;
	r = 0;
	g = 0;
	b = 0;
	while (i < n)
		b += colors[++i] % 0x100;
	i = -1;
	while (i < n)
		g += colors[++i] % 0x10000;
	i = -1;
	while (i < n)
		r += colors[++i] % 0x1000000;
	r = r * 0x10000 / n;
	g = g * 0x100 / n;
	b /= n;
	return (r + g + b);
}
