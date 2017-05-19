/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_shadow.cu                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:13:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/19 14:24:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Throws a shadow ray for each light in the scene.
** Returns true if there is an intersection between a light and the origin of
** the ray, else returns false.
*/
__device__
static void	filter_for_transparency(t_vec3 *dim_light, t_vec3 obj_col, float k);
__device__
static void	filter_color(float *dim, float obj_col, float k);

__device__
int		in_shadow(t_raytracing_tools *r, t_ray *primary_ray,
		t_ray *shadow_ray, t_light *light, t_vec3 *dim_light)
{
	int			i;
	float		max;
	int			is_transparent;

	is_transparent = 0;
	r->t = INFINITY;
	shadow_ray->t = INFINITY;
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
	while (r->scene->objects[++i].type != T_INVALID_TOKEN)
	{
		if (intersects(r, shadow_ray, i) &&
			shadow_ray->t < max && shadow_ray->t > 0.0) 
		{
			if (r->scene->objects[i].transparency > 0.01)
			{
				filter_for_transparency(dim_light, 
					get_object_color(&r->scene->objects[i], primary_ray),
					r->scene->objects[i].transparency);
				is_transparent = 1;
			}
			else
				return (2);
		}
	}
	return (is_transparent);
}

__device__
static void	filter_for_transparency(t_vec3 *dim_light, t_vec3 obj_col, float k)
{
	filter_color(&dim_light->x, obj_col.x, k);
	filter_color(&dim_light->y, obj_col.y, k);
	filter_color(&dim_light->z, obj_col.z, k);
}

__device__
static void	filter_color(float *dim, float obj_col, float k)
{
	*dim *= (1 - (255 - obj_col) / 255 * (1 - k)) * k;				
}