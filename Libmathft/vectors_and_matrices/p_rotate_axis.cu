/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_rotate_axis.cu                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 11:38:22 by tgros             #+#    #+#             */
/*   Updated: 2017/05/26 12:11:19 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmathft.cuh"

/*
** Rotates a point around an arbitrary axis intersecting an arbitrary point
*/

__host__ __device__
t_vec3		p_rotate_axis(t_vec3 d1, t_vec3 d2, t_vec3 rot_p, t_vec3 point)
{
	t_matrix	mat;
	t_vec3		res;
	t_vec3		u;
	float		angle;

	d1 = v_norm(d1);
	d2 = v_norm(d2);
	u = v_norm(v_cross(d2, d1));
	angle = acos((v_dot(d1, d2)) / (v_length(d1) * v_length(d2)));
	m_new_rotate_axis(&mat, u, angle);

	res = m_v_mult(v_sub(point, rot_p), &mat);
	res = v_add(res, rot_p);
	return (res);
}