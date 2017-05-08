/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_to_vec.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:23:57 by tgros             #+#    #+#             */
/*   Updated: 2017/05/04 16:25:12 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

__host__ __device__
t_vec3		col_to_vec(t_color col)
{
	t_vec3	v_col;

	v_col.x = col.r;
	v_col.y = col.g;
	v_col.z = col.b;
	return (v_col);
}