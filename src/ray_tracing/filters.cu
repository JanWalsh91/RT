/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 10:41:42 by tgros             #+#    #+#             */
/*   Updated: 2017/04/19 13:47:25 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

__device__
t_color		b_w_filter(t_color c)
{
	float	color;

	color = 0.299f * c.r + 0.587 * c.g + 0.114 * c.b;
	c.r = color;
	c.g = color;
	c.b = color;
	return (c);
}

__device__
t_color		b_w_filter_average(t_color c)
{
	float	average;

	average = (c.r + c.g + c.b) / 3.0;
	c.r = average;
	c.g = average;
	c.b = average;
	return (c);
}

__device__
t_color		sepia_filter(t_color c)
{
	float	r;
	float	g;
	float	b;

	r = (c.r * 0.393 + c.g * 0.769 + c.b * 0.189);
	g = (c.r * 0.349 + c.g * 0.686 + c.b * 0.168);
	b = (c.r * 0.272 + c.g * 0.534 + c.b * 0.131);
	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

__device__
t_color		deutan_filter(t_color c)
{
	float	r;
	float	g;
	float	b;

	r = c.r * 0.8 + c.g * 0.2;
	g = c.r * 0.25833 + c.g * 0.74167;
	b = c.g * 0.14167 + c.b * 0.85833;
	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}