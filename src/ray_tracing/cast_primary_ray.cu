/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_primary_ray.cu                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 11:10:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/03 18:11:39 by tgros            ###   ########.fr       */
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
	t_color 	col = v_new(0, 0, 0);

	// C(1)
	ray->t2 = INFINITY;
	i = -1;
	while (scene->objects[++i].type != T_INVALID_TOKEN)
	{
		if (intersects(scene, ray, i) && ray->t2 > ray->t)
			ray->t2 = ray->t;
	}
	// if (200 < scene->pix.x && scene->pix.x < 300)
	// {
	// 	col.z = 255;
	// }//ray->t2 = 10;
	// else
	// {
	// 	col = v_new(255, 0, 0);
	// }
	// C(2)
	if (ray->t2 == INFINITY)
		return (scene->background_color);
		// return (v_new(0, 0, 255));
	// C(3)
	ray->hit = v_add(ray->origin, v_scale(ray->dir, ray->t2));
	// C(4)
	get_normal(ray, &scene->objects[ray->hit_obj]);
	// C(5)
	// col = get_color_at_hitpoint(scene, ray, &shadow_ray);
	col = scene->objects[ray->hit_obj].col;
	// printf("col: %f, %f, %f\n", col.x, col.y, col.z);
	return (col);
}

__device__
static t_color	get_color_at_hitpoint(t_scene *scene, t_ray *ray,
				t_ray *shadow_ray)
{
	t_color	color;
	int		i;

	color = v_new(0, 0, 0);
	i = -1;
	// C(42)
	while (scene->lights[++i].col.x != -1)
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
