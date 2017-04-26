/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_shadow.cu                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:13:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 11:15:28 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Throws a shadow ray for each light in the scene.
** Returns true if there is an intersection between a light and the origin of
** the ray, else returns false.
*/

__device__
int		in_shadow(t_raytracing_tools *r, t_ray *primary_ray,
		t_ray *shadow_ray, t_light *light, t_color *dim_light)
{
	int			i;
	float		max;
	int			is_transparent;

	is_transparent = 0;
	r->t = INFINITY;
	shadow_ray->type = R_SHADOW;
	shadow_ray->origin = v_add(primary_ray->hit,
		v_scale(primary_ray->nhit, BIAS * primary_ray->n_dir));
	if (!v_isnan(light->pos))
		max = v_length(v_sub(light->pos, shadow_ray->origin));
	else
		max = INFINITY;
	if (!v_isnan(light->pos))
		shadow_ray->dir = v_sub(light->pos, shadow_ray->origin);
	else
		shadow_ray->dir = v_scale(light->dir, -1);
	shadow_ray->dir = v_norm(shadow_ray->dir);
	i = -1;
	// while (r->scene->objects[++i].type != T_INVALID_TOKEN)
	// {
	// 	if (intersects(r, shadow_ray, i) &&
	// 		shadow_ray->t < max && shadow_ray->t > 0)
	// 		return (true);
	// }
	while (r->scene->objects[++i].type != T_INVALID_TOKEN)
	{
		if (intersects(r, shadow_ray, i) &&
			shadow_ray->t < max && shadow_ray->t > 0)
		{
			if (r->scene->objects[i].transparency > 0.01)
			{
				*dim_light = c_min(c_scale(vec_to_col(r->scene->objects[i].col), r->scene->objects[i].transparency),
				*dim_light);
				is_transparent = 1;
			}
			else
				return (2);
		}
	}
	return (is_transparent);
}
