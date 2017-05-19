/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_primary_ray.cu                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 11:10:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/19 15:04:03 by jwalsh           ###   ########.fr       */
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
static t_color	apply_filter(t_vec3 dim_light, t_color light_color);
__device__
t_color			get_reflected_and_refracted(t_raytracing_tools *r, t_scene *scene, t_ray *ray);
__device__
static t_color	get_color_at_hitpoint(t_raytracing_tools *r, t_ray *ray,
				t_ray *shadow_ray);

__device__
t_color			cast_primary_ray(t_raytracing_tools *r, t_ray *ray)
{
	t_ray		shadow_ray;
	int			i;
	t_color 	col;
	
	if (ray->depth == 0)
		return (c_new(0, 0, 0));
	--ray->depth;
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
	col = (ray->type < 2) ? get_color_at_hitpoint(r, ray, &shadow_ray) : update_photon(r, ray);
	return (col);
}

__device__
static t_color	get_color_at_hitpoint(t_raytracing_tools *r, t_ray *ray,
				t_ray *shadow_ray)
{
	t_color	color;
	t_color light_color;
	t_vec3	dim_light;
	int		i;
	int		ret;

	i = -1;
	color = r->scene->is_diffuse ? c_new(0, 0, 0) : vec_to_col(r->scene->objects[ray->hit_obj].col);
	while (!v_isnan(r->scene->lights[++i].col))
	{
		dim_light = v_new(1, 1, 1);
		light_color = c_new(0, 0, 0);
		if ((ret = in_shadow(r, ray, shadow_ray, &r->scene->lights[i], &dim_light)) != 2 || !r->scene->is_shadow)
		{
			if (r->scene->is_diffuse)
				light_color = c_add(light_color, get_diffuse(r->scene, ray, shadow_ray, &r->scene->lights[i]));
			if (r->scene->is_specular && !ret)
				light_color = c_add(light_color, get_specular(r->scene, ray, shadow_ray, &r->scene->lights[i]));
			color = c_add(color, ret ? apply_filter(dim_light, light_color) : light_color);
			
		}
	}
	color = c_add(color, get_reflected_and_refracted(r, r->scene, ray));
	if (ray->depth == r->scene->ray_depth - 1)
		color = c_add(color, get_ambient(r->scene, get_object_color(&r->scene->objects[ray->hit_obj], ray)));
	return (color);
}

__device__
static t_color	apply_filter(t_vec3 dim_light, t_color light_color)
{
	t_color new_col;

	new_col.r = (uint8_t)(dim_light.x * (float)light_color.r);
	new_col.g = (uint8_t)(dim_light.y * (float)light_color.g);
	new_col.b = (uint8_t)(dim_light.z * (float)light_color.b);
	return (new_col);
}
