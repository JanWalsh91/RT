/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_torus_intersection.cu                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:52:47 by tgros             #+#    #+#             */
/*   Updated: 2017/05/18 16:28:17 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"


__device__
bool		get_torus_intersection(t_raytracing_tools *r, t_ray *ray,
				int index)
{
	t_quartic	qua;
	t_object	*obj = &r->scene->objects[index];
	t_vec4im	sol;

	obj->dir.x = 0;
	obj->dir.y = 1;
	obj->dir.z = 0;
	qua.m = v_dot(ray->dir, ray->dir);
	qua.n = v_dot(ray->dir, v_sub(ray->origin, obj->pos));
	qua.o = v_dot(v_sub(ray->origin, obj->pos), v_sub(ray->origin, obj->pos));
	qua.p = v_dot(ray->dir, obj->dir);
	qua.q = v_dot(v_sub(ray->origin, obj->pos), obj->dir);

	// printf("%f, %f, %f\n", obj->dir.x, obj->dir.y, obj->dir.z);

	qua.a = qua.m * qua.m;
	qua.b = 4 * qua.m * qua.n;
	qua.c = 4 * (qua.m * qua.m) + 2 * qua.m * qua.o - 2 * (obj->rad_torus * obj->rad_torus + obj->rad * obj->rad) * qua.m + 4 * (obj->rad_torus * obj->rad_torus) * qua.p * qua.p;
	qua.d = 4 * qua.n * qua.o - 4 * (obj->rad_torus * obj->rad_torus + obj->rad * obj->rad) * qua.n + 8 * obj->rad_torus * obj->rad_torus * qua.p * qua.q;
	qua.e = qua.o * qua.o - 2 * (obj->rad_torus * obj->rad_torus + obj->rad * obj->rad) * qua.o + 4 * (obj->rad_torus * obj->rad_torus) * (qua.q * qua.q) + ((obj->rad_torus * obj->rad_torus + obj->rad * obj->rad) * (obj->rad_torus * obj->rad_torus + obj->rad * obj->rad));

	/* if (!*/solve_quartic(&qua, &sol);
	// 	return (false);
	// if (sol.w < sol.x)
	// 	ft_swapf(&sol.w, &sol.x);
	// if (sol.w < sol.y)
	// 	ft_swapf(&sol.w, &sol.y);
	// if (sol.w < sol.z)
	// 	ft_swapf(&sol.w, &sol.z);
	// if (sol.w < 0)
	// 	return (false);
	// printf("mnopq: %f, %f, %f, %f, %f : sol %f, %f, %f, %f\n", qua.m, qua.n, qua.o,qua.p,qua.q, sol.w, sol.x, sol.y, sol.z);
	// if (r->t > sol.w)
	// 	r->t = sol.w;
	return (true);
}
