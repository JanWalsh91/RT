/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:31:14 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 17:41:55 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Functions for setting default values for
** - resolution
** - ray depth
** - ambient light coefficient (ka)
** - ambient light color
** - PPM light intensity
*/

void	set_default_resolution(t_scene *scene)
{
	data_warning(scene, 0, NULL, "Providing default resolution.");
	scene->res.x = DEFAULT_RES_H;
	scene->res.y = DEFAULT_RES_W;
}

void	set_default_ray_depth(t_scene *scene)
{
	data_warning(scene, 0, NULL, "Providing default ray depth.");
	scene->ray_depth = DEFAULT_RAY_DEPTH;
}

void	set_default_ka(t_scene *scene)
{
	data_warning(scene, 0, NULL,
		"Providing default ambient light coefficient (ka).");
	scene->ka = DEFAULT_KA;
}

void	set_default_ambient_light_color(t_scene *scene)
{
	data_warning(scene, 0, NULL, "Providing default ambient light color.");
	scene->ambient_light_color = v_new(DEFAULT_AMBIENT_LIGHT_COLOR_R,
										DEFAULT_AMBIENT_LIGHT_COLOR_G,
										DEFAULT_AMBIENT_LIGHT_COLOR_B);
}

void	set_default_ppm_light_intensity(t_scene *scene)
{
	scene->ppm_light_intensity = DEFAULT_PPM_LIGHT_INTENSITY;
}
