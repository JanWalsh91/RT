/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_iors.cu                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:56:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 16:03:51 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

__device__
void		get_iors2(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray);
__device__
void		get_iors3(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray);
		
/*
** Same as update_ior function, but only to retrieve the iors, not to update
** the lists and ray iors.
*/

__device__
void		get_iors(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray)
{
	int		i;

	if (ray->n_dir == 1)
	{
		i = 0;
		*n1 = ray->ior;
		while (r->ior_list[i] > 0.001 && i < r->scene->ray_depth)
			++i;
		*n2 = r->scene->objects[ray->hit_obj].ior;
	}
	else
		get_iors2(n1, n2, r, ray);
}

__device__
void		get_iors2(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray)
{
	int		i;
	float	ret;

	i = r->scene->ray_depth;
	if (i < 2)
	{
		*n1 = 1;
		*n2 = 1;
		return ;
	}
	while (i >= 0)
	{
		ret = r->ior_list[i] - r->scene->objects[ray->hit_obj].ior;
		if (ret < 0.001 && ret > -0.001)
			break ;
		--i;
	}
	if (!(ret < 0.001 && ret > -0.001))
		return (get_iors3(n1, n2, r, ray));
	i = 0;
	while (r->ior_list[i] > 0.001)
		++i;
	*n2 = r->ior_list[i - 1];
	*n1 = ray->ior;
}

__device__
void		get_iors3(float *n1, float *n2, t_raytracing_tools *r,
				t_ray *ray)
{
	int i;

	*n1 = ray->ior;
	i = 0;
	while (r->ior_list[i] > 0.001)
		++i;
	*n2 = r->ior_list[i - 1];
}
