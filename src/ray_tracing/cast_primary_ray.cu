/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_primary_ray.cu                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 11:10:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/20 15:37:55 by jwalsh           ###   ########.fr       */
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
__device__
t_color	get_reflected_and_refracted(t_raytracing_tools *r, t_scene *scene, t_ray *ray);

__device__
static t_color	get_color_at_hitpoint(t_raytracing_tools *r, t_ray *ray,
				t_ray *shadow_ray);

__device__
t_color			cast_primary_ray(t_raytracing_tools *r, t_ray *ray)
{
	t_ray		shadow_ray;
	int			i;
	t_color 	col;
	
	--r->ray_depth;
	if (r->pix.x == 50 && r->pix.y == 50)
		printf("r: [%i]\n", r->ray_depth);
	if (r->ray_depth == 0)
		return (c_new(0, 0, 0));
	r->t = INFINITY;
	i = -1;
	while (r->scene->objects[++i].type != T_INVALID_TOKEN)
	{
		if (intersects(r, ray, i) && r->t > ray->t)
			r->t = ray->t;
	}
	if (r->t == INFINITY)
		return (vec_to_col(r->scene->background_color));
	ray->hit = v_add(ray->origin, v_scale(ray->dir, r->t));
	get_normal(ray, &r->scene->objects[ray->hit_obj]);
	col = get_color_at_hitpoint(r, ray, &shadow_ray);
	// col = r->scene->objects[ray->hit_obj].col;
	// printf("col: %f, %f, %f\n", col.x, col.y, col.z);
	return (col);
}

__device__
static t_color	get_color_at_hitpoint(t_raytracing_tools *r, t_ray *ray,
				t_ray *shadow_ray)
{
	t_color	color;
	int		i;

	color = r->scene->is_diffuse ? c_new(0, 0, 0) : vec_to_col(r->scene->objects[ray->hit_obj].col);
	// printf("%d, %d, %d\n", color.r, color.g, color.b);
	i = -1;
	while (!v_isnan(r->scene->lights[++i].col))
	{
		if (!in_shadow(r, ray, shadow_ray, &r->scene->lights[i]) || !r->scene->is_shadow)
		{
			if (r->scene->is_diffuse)
				color = c_add(color, get_diffuse(r->scene, ray, shadow_ray, &r->scene->lights[i]));
			if (r->scene->is_specular)
				color = c_add(color, get_specular(r->scene, ray, shadow_ray, &r->scene->lights[i]));
		}
	}
	color = c_add(color, get_reflected_and_refracted(r, r->scene, ray));
	color = c_add(color, get_ambient(r->scene));
	return (color);
	// return (v_clamp(color, 0, 255));
}
