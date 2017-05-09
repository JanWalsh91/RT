/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_cubic.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:16:04 by tgros             #+#    #+#             */
/*   Updated: 2017/05/09 17:50:45 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

/*
** Solves a cubic equation.
** Returns true if the cubic has at least one solution.
*/

__device__
bool	solve_cubic(t_vec3 q, float d, t_vec3 *sol)
{
	t_vec4	tmp;
	t_vec3	res;
	t_vec3	tmp2;

	res.x = (((3 * q.z) / q.x) - ((q.y * q.y) / (q.x * q.x))) / 3;
	res.y = ((((2 * powf(q.y, 3)) / powf(q.x, 3))) - (9 * q.y * q.z / (q.x * q.x)) + (27 * d / q.x)) / 27;
	res.z = (res.y * res.y / 4) + (powf(res.x, 3) / 27);

	if (res.x < 0.0001 && res.x > -0.0001 && res.z  < 0.0001 && res.z > -0.0001 && res.z  < 0.0001 && res.z > -0.0001)
	{
		sol->x = cbrtf(d / q.x) * -1;
		sol->y = sol->x;
		sol->z = sol->x;
	}
	else if (res.z > 0)
	{
		tmp.w = -(res.y / 2.0) + sqrtf(res.z);
		tmp.x = cbrtf(tmp.w);
		tmp.y = -(res.y / 2.0) - sqrtf(res.z);
		tmp.z = cbrtf(tmp.y);
		sol->x = (tmp.x + tmp.z) - (q.y / (q.x * 3));
		sol->y = sol->x;
		sol->z = sol->x;
	}
	else if (res.z <= 0)
	{
		tmp2.x = sqrtf(((res.y * res.y) / 4) - res.z);
		tmp2.y = cbrtf(tmp2.x);
		tmp2.z = acosf(-(res.y / (2 * tmp2.x)));

		tmp.w = tmp2.y * -1;
		tmp.x = cosf(tmp2.z / 3.0);
		tmp.y = sqrtf(3.0) * sinf(tmp2.z / 3.0);
		tmp.z = (q.y / (3.0 * q.x)) * -1;

		sol->x = ((2 * tmp2.y) * cosf(tmp2.z / 3.0)) - (q.y / (3.0 * q.x));
		sol->y = tmp.w * (tmp.x + tmp.y) + tmp.z;
		sol->z = tmp.w * (tmp.x - tmp.y) + tmp.z;
	}
	return (true);
}