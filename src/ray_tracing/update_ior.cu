/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ior.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 12:46:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 10:22:53 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Updates the ior list and determines n1 and n2.
** n1: ior of volume of incoming ray
** n2: ior of volume of outgoing ray
*/

__device__
static void		ray_entering(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray);
__device__
static void		ray_exiting(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray);
				__device__
static void		ray_exiting2(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray);
				__device__
static void		ray_exiting3(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray);
__device__
void			update_ior(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray)
{
	if (ray->n_dir == 1)
		ray_entering(n1, n2, r, ray);
	else
		ray_exiting(n1, n2, r, ray);
}

__device__
static void		ray_entering(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray)
{
	int		i;

	i = 0;
	*n1 = ray->ior;
	while (r->ior_list[i] > 0.001 &&
		i < r->scene->ray_depth && i < MAX_RAY_DEPTH)
		++i;
	if (i)
		r->ior_list[i] = r->scene->objects[ray->hit_obj].ior;
	*n2 = r->scene->objects[ray->hit_obj].ior;
}

__device__
static void		ray_exiting(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray)
{
	int		i;
	int		ret;

	i = r->scene->ray_depth;
	while (i >= 0)
	{
		ret = r->ior_list[i] - r->scene->objects[ray->hit_obj].ior;
		if (ret < 0.001 && ret > -0.001)
			break ;
		--i;
	}
	if (!(ret < 0.001 && ret > -0.001))
		return (ray_exiting2(n1, n2, r, ray));
	if (i)
	{
		r->ior_list[i] = 0;
		while (i < r->scene->ray_depth && r->ior_list[i] < 0.001)
		{
			r->ior_list[i] = r->ior_list[i + 1];
			r->ior_list[i + 1] = 0;
			++i;
		}
	}
	ray_exiting3(n1, n2, r, ray);
}

__device__
static void		ray_exiting3(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray)
{
	int i;

	i = 0;
	while (r->ior_list[i] > 0.001)
		++i;
	*n2 = r->ior_list[i ? i - 1 : 0];
	*n1 = ray->ior;
}

__device__
static void		ray_exiting2(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray)
{
	int i;

	i = 0;
	*n1 = ray->ior;
	while (r->ior_list[i] > 0.001 && i < r->scene->ray_depth)
		++i;
	*n2 = r->ior_list[i == r->scene->ray_depth || !i ? 0 : i - 1];
	return ;
}
