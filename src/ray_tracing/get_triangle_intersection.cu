/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle_intersection.cu                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <talemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:26:41 by talemari          #+#    #+#             */
/*   Updated: 2017/05/18 15:28:58 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../../inc/objparser.h"
/*
** Checks for a ray-sphere intersection.
*/

__device__
bool	get_triangle_intersection(t_triangle *t, t_ray *ray, int index, t_vec3 *norm)
{
	float		det;
	float		invdet;
	float		u;
	float		v;
	float		tmp;
	t_vec3		edge1;
	t_vec3		edge2;
	t_vec3		s1;
	t_vec3		s2;
	t_vec3		s3;

	edge1 = v_sub(t->v2, t->v1);
	edge2 = v_sub(t->v3, t->v1);
	s1 = v_cross(ray->dir, edge2);
	det = v_dot(edge1, s1);
	if (det > -0.0001 && det < 0.0001)
		return (false);
	invdet = 1 / det;
	s2 = v_sub(ray->origin, t->v1);
	u = v_dot(s2, s1) * invdet;
	if (u < 0 || u > 1)
		return (false);
	s3 = v_cross(ray->dir, edge1);
	v = v_dot(ray->dir, s3) * invdet;
	if (v < 0 || (u + v) > 1)
		return (false);
	tmp = v_dot(edge2, s3) * invdet;
	if ((tmp < 0) || (tmp > ray->t) || ray->type == R_SHADOW)
		return (false);
	ray->t = tmp - 0.005;
	ray->hit_obj = index;
	ray->hit_type = T_TRIANGLE;
	*norm = v_cross(edge2, edge1);
	return (true);
}
