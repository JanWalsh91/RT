/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_torus_intersection.cu                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:52:47 by tgros             #+#    #+#             */
/*   Updated: 2017/05/22 16:21:34 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

__device__
float	choose_between_two_roots(float a, float b)
{
	if (a < 0)
	{
		if (b > 0)
			return(b);
	}
	else if (b < 0)
	{
		if (a > 0)
			return(a);
	}
	else if (a < 0 && b < 0)
		return(-1);
	else if (a > b)
		return(b);
	return(a);
}

__device__
float	choose_between_four_roots(float a, float b, float c, float d)
{
	float e;
	float f;

	e = choose_between_two_roots(a, b);
	f = choose_between_two_roots(c, d);
	if (e > 0 && f > 0)	
		return ((e < f) ? e : f);
	else if (e > 0 && f < 0)
		return (e);
	else if (f > 0 && e < 0)
		return (f);
	else
		return (-1);
}

// void	get_torus_quartic()
// {
// 	qua.m = v_dot(ray->dir, ray->dir);
// 	qua.n = v_dot(ray->dir, v_sub(ray->origin, obj->pos));
// 	qua.o = v_dot(v_sub(ray->origin, obj->pos), v_sub(ray->origin, obj->pos));
// 	qua.p = v_dot(ray->dir, obj->dir);
// 	qua.q = v_dot(v_sub(ray->origin, obj->pos), obj->dir);

// 	// printf("%f, %f, %f\n", obj->dir.x, obj->dir.y, obj->dir.z);

// 	qua.a = qua.m * qua.m;
// 	qua.b = 4 * qua.m * qua.n;
// 	qua.c = 4 * (qua.m * qua.m) + 2 * qua.m * qua.o - 2 * (obj->rad_torus * obj->rad_torus +
// 		obj->rad * obj->rad) * qua.m + 4 * (obj->rad_torus * obj->rad_torus) * qua.p * qua.p;
// 	qua.d = 4 * qua.n * qua.o - 4 * (obj->rad_torus * obj->rad_torus + obj->rad *
// 		obj->rad) * qua.n + 8 * obj->rad_torus * obj->rad_torus * qua.p * qua.q;
// 	qua.e = qua.o * qua.o - 2 * (obj->rad_torus * obj->rad_torus +
// 		obj->rad * obj->rad) * qua.o + 4 * (obj->rad_torus * obj->rad_torus) * (qua.q * qua.q) +
// 	((obj->rad_torus * obj->rad_torus + obj->rad * obj->rad) * (obj->rad_torus * obj->rad_torus +
// 		obj->rad * obj->rad));
// }

__device__
bool		get_torus_intersection(t_raytracing_tools *r, t_ray *ray,
				int index)
{
	t_quartic	qua;
	t_object	*obj = &r->scene->objects[index];
	t_vec4im	sol;
	float		res;

	obj->dir.x = 0;
	obj->dir.y = 0;
	obj->dir.z = 1;
	obj->rad_torus = 1;
	obj->rad = 10;
 //	m = D|D, n = D|X, o = X|X, p = D|V, q = X|V
	qua.m = v_dot(ray->dir, ray->dir);
	qua.n = v_dot(ray->dir, v_sub(ray->origin, obj->pos));
	qua.o = v_dot(v_sub(ray->origin, obj->pos), v_sub(ray->origin, obj->pos));
	qua.p = v_dot(ray->dir, obj->dir);
	qua.q = v_dot(v_sub(ray->origin, obj->pos), obj->dir);

	// printf("%f, %f, %f\n", obj->dir.x, obj->dir.y, obj->dir.z);

	// printf("Rad torus = %f, rad = %f\n", obj->rad_torus, obj->rad);


   // a = m^2
   // b = 4*m*n
   // c = 4*m^2 + 2*m*o - 2*(R^2+r^2)*m + 4*R^2*p^2
   // d = 4*n*o - 4*(R^2+r^2)*n + 8*R^2*p*q
   // e = o^2 - 2*(R^2+r^2)*o + 4*R^2*q^2 + (R^2-r^2)^2
	qua.a = qua.m * qua.m;
	qua.b = 4 * qua.m * qua.n;
	qua.c = (4 * (qua.m * qua.m)) + (2 * qua.m * qua.o) - (2 * (obj->rad_torus * obj->rad_torus + obj->rad * obj->rad)) *
		qua.m + (4 * (obj->rad_torus * obj->rad_torus) * qua.p * qua.p);
	qua.d = (4 * qua.n * qua.o) - 4 * ((obj->rad_torus * obj->rad_torus) + (obj->rad * obj->rad)) * qua.n + 8 * obj->rad_torus * obj->rad_torus * qua.p * qua.q;
	qua.e = qua.o * qua.o - 2 * (obj->rad_torus * obj->rad_torus + obj->rad * obj->rad) * qua.o +
	(4 * (obj->rad_torus * obj->rad_torus) * (qua.q * qua.q)) +
	((obj->rad_torus * obj->rad_torus + obj->rad * obj->rad) * (obj->rad_torus * obj->rad_torus + obj->rad * obj->rad));

	if (r->pix.x == 600)
	{
		//printf("rpixy : %d ray dir: %f %f %f abcde : %f %f %f %f %f\n", r->pix.y, ray->dir.x, ray->dir.y, ray->dir.z, qua.a, qua.b, qua.c, qua.d, qua.e);
	}

	if (!solve_quartic(&qua, &sol))
	{
		//printf("Return false\n");
	 	return (false);
	}
	if (r->pix.y == 600 && r->pix.x == 600)
	{
	 printf("sol quartic\nX1 : %f, %f\nX2 : %f, %f\nX3 : %f. %f\nX4 : %f, %f\n", sol.w.r, sol.w.i,
		 sol.x.r, sol.x.i, sol.y.r, sol.y.i, sol.z.r, sol.z.i);
	// printf("resultat : %f\n",res);
	}
	if (isnan(sol.x.i) || isnan(sol.y.i))
		res = choose_between_four_roots(sol.w.r, sol.x.r, sol.y.r, sol.z.r);
	else
		res = choose_between_two_roots(sol.w.r, sol.z.r);
	if (r->pix.x == 1 && r->pix.y == 1)
	{
		//printf("Coucou\n");
	}
	if (res < 0)
	{
		//printf("Return false\n");
		return (false);
	}

	if (r->pix.y == 600 && r->pix.x == 600)
	{
	 printf("sol quartic\nX1 : %f, %f\nX2 : %f, %f\nX3 : %f. %f\nX4 : %f, %f\n", sol.w.r, sol.w.i,
		 sol.x.r, sol.x.i, sol.y.r, sol.y.i, sol.z.r, sol.z.i);
	// printf("resultat : %f\n",res);
	}
	 r->t > res ? ray->t = res : 0;
	if (ray->type == R_PRIMARY && r->t > res)
	{
		ray->hit_obj = index;
		ray->hit_type = T_TORUS;
	}
	//printf("mnopq: %f, %f, %f, %f, %f : sol %f, %f, %f, %f\n", qua.m, qua.n, qua.o,qua.p,qua.q, sol.w, sol.x, sol.y, sol.z);
	return (true);
}
