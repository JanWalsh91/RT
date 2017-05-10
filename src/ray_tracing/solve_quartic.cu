/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic.cu                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:46:42 by tgros             #+#    #+#             */
/*   Updated: 2017/05/10 14:20:53 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

/*
** Solves a quartic equation.
** Updates r1 and r2 if at least a solution exists.
** Returns true if the quartic has at least one solution.
*/

__device__
bool	solve_quartic(t_quartic *qua, t_vec4 *sol)
{
	t_vec3		fgh;
	t_vec3im	sol_cubic;
	float p, q, r, s;
	// divide all members by a
	qua->b /= qua->a;
	qua->c /= qua->a;
	qua->d /= qua->a;
	qua->e /= qua->a;
	qua->a = 1.0;

	// printf("After simplification : %f, %f, %f, %f, %f\n", qua->a, qua->b, qua->c, qua->d, qua->e);

	fgh.x = qua->c - (3 * qua->b * qua->b / 8);
	fgh.y = qua->d + ((qua->b * qua->b * qua->b) / 8) - (qua->b * qua->c / 2);
	fgh.z = qua->e - (3 * pow(qua->b, 4) / 256) + (qua->b * qua->b * qua->c / 16) - (qua->b * qua->d / 4);

	printf("f g h : %f, %f, %f\n", fgh.x, fgh.y, fgh.z);

	// Y3 + (f/2)*Y2 + ((f2 -4*h)/16)*Y -g2/64 = 0
	// solve cubic equation 
	// get 3 roots

	solve_cubic(v_new(1, fgh.x / 2.0, ((fgh.x * fgh.x - 4 * fgh.z) / 16)), - (fgh.y * fgh.y) / 64, &sol_cubic);

	printf("Sols cubics : %f, %f, %f\n", sol_cubic.x, sol_cubic.y, sol_cubic.z);

	if (!isnan(sol_cubic.y.i) || !isnan(sol_cubic.z.i))
	{
		p = ft_sqrtfi(sol_cubic.y).r;
		q = ft_sqrtfi(sol_cubic.z).r;
		r = -fgh.y / (8 * p * q);
		s = qua->b / (4 * qua->a);
		sol->w = p + q + r - s; 
		sol->x = NAN;
		sol->y = NAN;
		sol->z = -p -q + r - s;
	}
	else
	{
		p = sqrt(sol_cubic.x.r);
		q = sqrt(sol_cubic.z.r);
		r = -fgh.y / (8 * p * q);
		s = qua->b / (4 * qua->a);
		sol->w = p + q + r -s;
		sol->x = p - q - r -s;
		sol->y = -p + q - r -s;
		sol->z = -p - q + r -s;
	}

	printf("pqrs : %f, %f, %f, %f\n", p, q, r, s);

	printf("Before simplification : %f, %f, %f, %f, %f sols : %f, %f, %f, %f\n", qua->a, qua->b, qua->c, qua->d, qua->e, sol->w, sol->x, sol->y, sol->z);

	if (sol->w < 0 && sol->x < 0 && sol->y < 0 && sol->z < 0)
		return (false);
	return (true);
}