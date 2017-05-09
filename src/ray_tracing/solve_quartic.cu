/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic.cu                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:46:42 by tgros             #+#    #+#             */
/*   Updated: 2017/05/09 16:12:20 by tgros            ###   ########.fr       */
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
	t_vec3	fgh;
	t_vec3	sol_cubic;
	// divide all members by a
	printf("Before simplification : %f, %f, %f, %f\n", qua->a, qua->b, qua->c, qua->d, qua->e);
	qua->b /= qua->a;
	qua->c /= qua->a;
	qua->d /= qua->a;
	qua->e /= qua->a;
	qua->a = 1.0;

	printf("After simplification : %f, %f, %f, %f\n", qua->a, qua->b, qua->c, qua->d, qua->e);

	fgh.x = qua->c - (3 * qua->b * qua->b / 8);
	fgh.y = qua->d + ((qua->b * qua->b * qua->b) / 8) - (qua->b * qua->c / 2);
	fgh.z = qua->e - (3 * pow(qua->b, 4) / 256) + (qua->b * qua->b * qua->c / 16) - (qua->b * qua->d / 4);

	printf("f g h : %f, %f, %f\n", fgh.x, fgh.y, fgh.z);

	// Y3 + (f/2)*Y2 + ((f2 -4*h)/16)*Y -g2/64 = 0
	// solve cubic equation 
	// get 3 roots

	solve_cubic(v_new(1, fgh.x / 2.0, ((fgh.x * fgh.x - 4 * fgh.z) / 16)), - (fgh.y * fgh.y) / 64, &sol_cubic);

	printf("Sols cubics : %f, %f, %f\n", sol_cubic.x, sol_cubic.y, sol_cubic.z);

	float p = sol_cubic.x > 0 ? sqrt(sol_cubic.x) : 0;
	float q = sqrt(sol_cubic.z);
	float r = -fgh.y / (8 * p * q);
	float s = qua->b / (4 * qua->a);

	printf("pqrs : %f, %f, %f, %f\n", p, q, r, s);

	sol->w = p + q + r -s;
	sol->x = p - q - r -s;
	sol->y = -p + q - r -s;
	sol->z = -p - q + r -s;

	if (sol->w < 0 && sol->x < 0 && sol->y < 0 && sol->z < 0)
		return (false);
	return (true);
}