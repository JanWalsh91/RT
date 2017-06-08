/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_iors.cu                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:56:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 11:29:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

__device__
static void		get_iors2(float *n1, float *n2, t_raytracing_tools *r, t_ray *ray);

/*
** Same as update_ior function, but only to retrieve the iors, not to update the lists and ray iors.
*/

__device__
void			get_iors(float *n1, float *n2, t_raytracing_tools *r, t_ray *ray)
{
	int		i;

	if (ray->n_dir == 1)
	{
		i = -1;
		*n1 = ray->ior;
		while (r->ior_list[++i] > 0.001);
		*n2 = r->scene->objects[ray->hit_obj].ior;
	}
	else
		get_iors2(n1, n2, r, ray);
}

__device__
static void		get_iors2(float *n1, float *n2, t_raytracing_tools *r, t_ray *ray)
{
	int i;
	float	ret;

	i = r->scene->ray_depth;
	while (i >= 0)
	{
		ret = r->ior_list[i] - r->scene->objects[ray->hit_obj].ior;
		if (ret < 0.001 && ret > -0.001)
			break;
		--i;
	}
	if (!(ret < 0.001 && ret > -0.001))
	{
		*n1 = ray->ior;
		i = 0;
		while (r->ior_list[i] > 0.001)
			++i;
		*n2 = r->ior_list[i - 1];
		return ;
	}
	i = 0;
	while (r->ior_list[i] > 0.001)
		++i;
	*n2 = r->ior_list[i - 1];
	*n1 = ray->ior;
}
