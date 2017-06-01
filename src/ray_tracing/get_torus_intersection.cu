/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_torus_intersection.cu                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:52:47 by tgros             #+#    #+#             */
/*   Updated: 2017/05/27 14:31:43 by jwalsh           ###   ########.fr       */
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
	float		rad_torus2;
	float		rad2;

	// obj->dir.x = 0;
	// obj->dir.y = 0;
	// obj->dir.z = 1;
	 //obj->rad_torus = 0.000001;
	// obj->rad = 0.001;
	qua.m = v_dot(ray->dir, ray->dir);
	qua.n = v_dot(ray->dir, v_sub(ray->origin, obj->pos));
	qua.o = v_dot(v_sub(ray->origin, obj->pos), v_sub(ray->origin, obj->pos));
	qua.p = v_dot(ray->dir, obj->dir);
	qua.q = v_dot(v_sub(ray->origin, obj->pos), obj->dir);
	rad2 = powf(obj->rad, 2.0);
	rad_torus2 = powf(obj->rad_torus, 2.0);
	// printf("%f, %f, %f\n", obj->dir.x, obj->dir.y, obj->dir.z);

	//printf("Rad torus = %f, rad = %f\n", obj->rad_torus, obj->rad);


   // a = m^2
   // b = 4*m*n
   // c = 4*m^2 + 2*m*o - 2*(R^2+r^2)*m + 4*R^2*p^2
   // d = 4*n*o - 4*(R^2+r^2)*n + 8*R^2*p*q
   // e = o^2 - 2*(R^2+r^2)*o + 4*R^2*q^2 + (R^2-r^2)^2
	qua.a = powf(qua.m, 2.0);
	qua.b = (4.0 * qua.m * qua.n);
	qua.c = (4.0 * qua.a + (2.0 * qua.m * qua.o)) - (2.0 * rad_torus2 + rad2 *
		qua.m)+ (4.0 * rad_torus2 * qua.p * qua.p);
	qua.d = (4.0 * qua.n * qua.o) - (4.0 * (rad_torus2 + rad2) * qua.n)+ (8.0 * rad_torus2 * qua.p * qua.q);
	qua.e = (qua.o * qua.o) - (2.0 * (rad_torus2 + rad2) * qua.o) + (4.0 * rad_torus2 * qua.q * qua.q) +
	((rad_torus2 + rad2) * (rad_torus2 + rad2));
	if (!solve_quartic(&qua, &sol))
	{
		//printf("Return false\n");
	 	return (false);
	}
	if (isnan(sol.w.r) && isnan(sol.x.r) && isnan(sol.y.r) && isnan(sol.z.r))
		return(false);
	res = INFINITY;
	// if (r->pix.y == 1 && r->pix.x == 1)
	// {
	//  printf("sol quartic\nX1 : %f, %f\nX2 : %f, %f\nX3 : %f. %f\nX4 : %f, %f\n", sol.w.r, sol.w.i,
	// 	 sol.x.r, sol.x.i, sol.y.r, sol.y.i, sol.z.r, sol.z.i);
	// // printf("resultat : %f\n",res);
	// }
	if ((isnan(sol.x.i) || isnan(sol.y.i)) && (!isnan(sol.w.r) && !isnan(sol.x.r) && !isnan(sol.y.r) && !isnan(sol.z.r)))
	{
		printf("sol quartic\nX1 : %f, %f\nX2 : %f, %f\nX3 : %f. %f\nX4 : %f, %f\n", sol.w.r, sol.w.i,
	 	 sol.x.r, sol.x.i, sol.y.r, sol.y.i, sol.z.r, sol.z.i);
		res = choose_between_four_roots(sol.w.r, sol.x.r, sol.y.r, sol.z.r);
	}
	else 
		res = choose_between_two_roots(sol.w.r, sol.z.r);
	if (res < 0 || isnan(res))
		return (false);
	 r->t > res ? ray->t = res : 0;
	if (ray->type == R_PRIMARY && r->t > res)
	{
		ray->hit_obj = index;
		ray->hit_type = T_TORUS;
	}
	//printf("mnopq: %f, %f, %f, %f, %f : sol %f, %f, %f, %f\n", qua.m, qua.n, qua.o,qua.p,qua.q, sol.w, sol.x, sol.y, sol.z);
	return (true);
}
