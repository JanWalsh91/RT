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
static void		print_vec2(t_vec3 vec)
{
	printf("x : %f, y : %f, z : %f\n", vec.x, vec.y, vec.z);
}

__device__
bool	get_triangle_intersection(t_raytracing_tools *r, t_triangle *t, t_ray *ray, int index)
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

	if (r->idx == 0)
		printf("get triangle itnersection\n");
	//if (r->pix.x == 600 && r->pix.y < 5)
	//{
	
	edge1 = v_sub(t->v2, t->v1);
	edge2 = v_sub(t->v3, t->v1);
	if (r->idx == 0)
	{
		printf("edge: %f, %f, %f edge2: %f, %f, %f\n", edge1.x, edge1.y, edge1.z, edge2.x, edge2.y, edge2.z);
		print_vec2(t->v1);
		print_vec2(t->v2);
		print_vec2(t->v3);
	}
	__syncthreads();
	s1 = v_cross(ray->dir, edge2);
	det = v_dot(edge1, s1);
	// printf("det = %f\n", det);
	if (r->idx == 0)
		C(10)
	__syncthreads();
	if (det > -0.0001 && det < 0.0001)
	{
		if (r->idx == 0)
			C(2)
				
		return (false);
	}
	
		// printf("idx: %d, det: %f\n", r->idx, det);
		
	__syncthreads();
	invdet = 1 / det;
	s2 = v_sub(ray->origin, t->v1);
	u = v_dot(s2, s1) * invdet;
	if (u < 0 || u > 1)
	{
		if (r->idx == 0)
			C(3)	
		return (false);
	}
	if (r->idx == 0)
		C(12)
	__syncthreads();
	s3 = v_cross(ray->dir, edge1);
	v = v_dot(ray->dir, s3) * invdet;
	if (v < 0 || (u + v) > 1)
	{
		if (r->idx == 0)
			C(4)	
		return (false);
	}
	if (r->idx == 0)
		C(13)
	__syncthreads();	
	tmp = v_dot(edge2, s3) * invdet;
	if ((tmp < 0) || (tmp > ray->t) || ray->type == R_SHADOW)
	{
		if (r->idx == 0)
			C(5)	
		return (false);
	}
	if (r->idx == 0)
		C(14)
	__syncthreads();
	ray->t = tmp - 0.005;
	ray->hit_obj = index;
	ray->hit_type = T_TRIANGLE;
	ray->nhit = v_cross(edge2, edge1);
	//}
	if (r->idx == 0)
		C(1)
	__syncthreads();
	return (true);
}
