/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_primary_ray.cu                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 11:10:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/02 18:07:52 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

/*
** Casts a primary ray:
** - checks for intersections with all objects in the scenes
** - checks for intersections between hit point and all light sources
** - evaluates color at hitpoint based on diffuse, specular and ambient
** lighting.
** - returns the calculated color, or background color if no intersections
** are found.
*/

static t_color	get_color_at_hitpoint(t_scene *scene, t_ray *ray,
				t_ray *shadow_ray);

__device__
t_color			cast_primary_ray(t_scene *scene, t_ray *ray)
{
	t_ray		shadow_ray;
	int			i;

	scene->t = INFINITY;
	i = -1;
	while (scene->objects[++i].type != -1)
	{
		if (intersects(scene, ray, i) && scene->t > ray->t)
			scene->t = ray->t;
	}
	if (scene->t == INFINITY)
		return (scene->background_color);
	ray->hit = v_add(ray->origin, v_scale(ray->dir, scene->t));
	get_normal(ray, &scene->objects[ray->hit_obj]);
	return (get_color_at_hitpoint(scene, ray, &shadow_ray));
}

__device__
static t_color	get_color_at_hitpoint(t_scene *scene, t_ray *ray,
				t_ray *shadow_ray)
{
	t_color	color;
	int		i;

	color = v_new(0, 0, 0);
	i = -1;
	while (&scene->lights[++i] != NULL)
	{
		if (!in_shadow(scene, ray, shadow_ray, &scene->lights[i]))
		{
			color = v_add(color, get_diffuse(scene, ray, shadow_ray, &scene->lights[i]));
			color = v_add(color, get_specular(scene, ray, shadow_ray, &scene->lights[i]));
		}
	}
	color = v_add(color, get_ambient(scene));
	return (v_clamp(color, 0, 255));
}
