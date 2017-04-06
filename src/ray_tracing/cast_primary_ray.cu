/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_primary_ray.cu                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 11:10:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Casts a primary ray:
** - checks for intersections with all objects in the scenes
** - checks for intersections between hit point and all light sources
** - evaluates color at hitpoint based on diffuse, specular and ambient
** lighting.
** - returns the calculated color, or background color if no intersections
** are found.
*/

static t_color	get_color_at_hitpoint(t_raytracing_tools *r, t_ray *ray,
				t_ray *shadow_ray);

__device__
t_color			cast_primary_ray(t_raytracing_tools *r, t_ray *ray)
{
	t_ray		shadow_ray;
	int			i;
	t_color 	col;

	r->t = INFINITY;
	i = -1;
	while (r->scenes->objects[++i].type != T_INVALID_TOKEN)
	{
		if (intersects(r, ray, i) && r->t > ray->t)
			r->t = ray->t;
	}
	if (r->t == INFINITY)
		return (r->scenes->background_color);
	ray->hit = v_add(ray->origin, v_scale(ray->dir, r->t));
	get_normal(ray, &r->scenes->objects[ray->hit_obj]);
	col = get_color_at_hitpoint(r, ray, &shadow_ray);
	// col = r->scenes->objects[ray->hit_obj].col;
	// printf("col: %f, %f, %f\n", col.x, col.y, col.z);
	return (col);
}

__device__
static t_color	get_color_at_hitpoint(t_raytracing_tools *r, t_ray *ray,
				t_ray *shadow_ray)
{
	t_color	color;
	int		i;

	i = -1;
	while (!v_isnan(r->scenes->lights[++i].col))
	{
		if (!in_shadow(r, ray, shadow_ray, &r->scenes->lights[i]))
		{
			color = v_add(color, get_diffuse(r->scenes, ray, shadow_ray, &r->scenes->lights[i]));
			color = v_add(color, get_specular(r->scenes, ray, shadow_ray, &r->scenes->lights[i]));
		}
	}
	color = v_add(color, get_ambient(r->scenes));
	return (v_clamp(color, 0, 255));
}
