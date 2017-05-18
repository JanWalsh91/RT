/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic.cu                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:46:42 by tgros             #+#    #+#             */
/*   Updated: 2017/05/18 16:31:25 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

/*
** Solves a quartic equation.
** Updates r1 and r2 if at least a solution exists. ?????????????????????????????
** Returns true if the quartic has at least one solution.
*/


__device__
void	solve_four_root(t_quartic *qua, t_vec3 fgh, t_vec3im sol_cubic, t_vec4im *sol)
{
	t_squart q;

	q.p = sqrt(sol_cubic.x.r);
	q.q = sqrt(sol_cubic.z.r);
	q.r = -fgh.y / (8 * q.p * q.q);
	q.s = qua->b / (4 * qua->a);
	sol->w.r = q.p + q.q + q.r -q.s;
	sol->x.r = q.p - q.q - q.r -q.s;
	sol->y.r = -q.p + q.q - q.r -q.s;
	sol->z.r = -q.p - q.q + q.r -q.s;
	sol->w.i = NAN;
	sol->x.i = NAN;
	sol->y.i = NAN;
	sol->z.i = NAN;
}

__device__
void	solve_im_root(t_quartic *qua, t_vec3 fgh, t_vec3im sol_cubic, t_vec4im *sol)
{
	t_squart q;

	q.pim = ft_sqrtfi(sol_cubic.y);
	q.qim.r = q.pim.r;
	q.qim.i = -q.pim.i;
	q.r = -fgh.y / (8 * ((q.pim.r * q.qim.r) - (q.pim.i * q.qim.i)));
	q.s = qua->b / (4 * qua->a);
	sol->w.r = q.pim.r + q.qim.r + q.r - q.s; 
	sol->x.r = q.pim.r - q.qim.r - q.r - q.s;
	sol->y.r = -q.pim.r + q.qim.r - q.r - q.s;
	sol->z.r = -q.pim.r - q.qim.r + q.r - q.s;
	sol->w.i = NAN;
	sol->x.i = q.pim.i - q.qim.i;
	sol->y.i = -q.pim.i + q.qim.i;
	sol->z.i = NAN;
}

__device__
bool	solve_quartic(t_quartic *qua, t_vec4im *sol)
{
	t_vec3		fgh;
	t_vec3im	sol_cubic;
	
	// divide all members by a
	qua->a = 1; 
	qua->b = -0.25;
	qua->c = -0.85;
	qua->d = 1.45;
	qua->e = -4.35;
	qua->b /= qua->a;
	qua->c /= qua->a;
	qua->d /= qua->a;
	qua->e /= qua->a;
	qua->a /= qua->a;
	//printf("After complication : %f, %f, %f, %f, %f\n", qua->a, qua->b, qua->c, qua->d, qua->e);
	fgh.x = qua->c - (3 * qua->b * qua->b / 8); // f
	fgh.y = qua->d + ((qua->b * qua->b * qua->b) / 8) - (qua->b * qua->c / 2); // g
	fgh.z = qua->e - (3 * pow(qua->b, 4) / 256) + (qua->b * qua->b * qua->c / 16) - (qua->b * qua->d / 4); // h
	//printf("f g h : %f, %f, %f\n", fgh.x, fgh.y, fgh.z);

	// Y3 + (f/2)*Y2 + ((f2 -4*h)/16)*Y -g2/64 = 0
	// solve cubic equation 
	// get 3 roots
	solve_cubic(v_new(1, fgh.x / 2.0, ((fgh.x * fgh.x - 4 * fgh.z) / 16)), - (fgh.y * fgh.y) / 64, &sol_cubic);

	// printf("Sols cubics x : %f, %f, \n", sol_cubic.x.r, sol_cubic.x.i);
	// printf("Sols cubics y : %f, %f, \n", sol_cubic.y.r, sol_cubic.y.i);
	// printf("Sols cubics z : %f, %f, \n", sol_cubic.z.r, sol_cubic.z.i);
	if (!isnan(sol_cubic.y.i) || !isnan(sol_cubic.z.i))
		solve_im_root(qua, fgh, sol_cubic, sol);
	else
		solve_four_root(qua, fgh, sol_cubic, sol);
	//printf("pim %f %f\n qim %f %f\n", pim.r, pim.i, qim.r, qim.i);
	printf("sol quartic\nX1 : %f, %f\nX2 : %f, %f\nX3 : %f. %f\nX4 : %f, %f\n", sol->w.r, sol->w.i,
		sol->x.r, sol->x.i, sol->y.r, sol->y.i, sol->z.r, sol->z.i);
	//printf("rs : %f, %f,\n",r, s);

	//printf("Before simplification : %f, %f, %f, %f, %f sols : %f, %f, %f, %f\n", qua->a, qua->b, qua->c, qua->d, qua->e, sol->w, sol->x, sol->y, sol->z);

	// if (sol->w < 0 && sol->x < 0 && sol->y < 0 && sol->z < 0)
	// 	return (false);
	return (true);
}