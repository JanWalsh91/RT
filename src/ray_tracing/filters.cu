/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 10:41:42 by tgros             #+#    #+#             */
/*   Updated: 2017/04/05 12:38:48 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

__device__
t_color		b_w_filter(t_color c)
{
	float	color;

	color = 0.299f * c.x + 0.587 * c.y + 0.114 * c.z;
	c.x = color;
	c.y = color;
	c.z = color;
	return (c);
}

__device__
t_color		b_w_filter_average(t_color c)
{
	float	average;

	average = (c.x + c.y + c.z) / 3.0;
	c.x = average;
	c.y = average;
	c.z = average;
	return (c);
}

__device__
t_color		sepia_filter(t_color c)
{
	float	r;
	float	g;
	float	b;

	r = (c.x * 0.393 + c.y * 0.769 + c.z * 0.189);
	g = (c.x * 0.349 + c.y * 0.686 + c.z * 0.168);
	b = (c.x * 0.272 + c.y * 0.534 + c.z * 0.131);
	c.x = r;
	c.y = g;
	c.z = b;
	return (v_clamp(c, 0, 255));
}

__device__
t_color		deutan_filter(t_color c)
{
	float	r;
	float	g;
	float	b;

	r = c.x * 0.8 + c.y * 0.2;
	g = c.x * 0.25833 + c.y * 0.74167;
	b = c.y * 0.14167 + c.z * 0.85833;
	c.x = r;
	c.y = g;
	c.z = b;
	return (c);
}