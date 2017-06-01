/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:29:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/31 11:49:54 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Functions for setting default values for
** - field of view (fov)
** - specular coefficient (ks)
** - diffuse coefficient (kd)
** - specular exponent (specular_exp)
*/

void	set_default_ior(t_scene *scene, int type, void *obj, float *ior)
{
	if (type == T_CAMERA)
		data_warning(scene, type, (t_camera *)obj,
		"Providing default index of refraction.");
	else
		data_warning(scene, type, (t_object *)obj,
		"Providing default index of refraction.");
	*ior = DEFAULT_IOR;
}

void	set_default_reflection(t_scene *scene, int type, void *obj,
			float *reflection)
{
	data_warning(scene, type, ((t_object *)obj),
			"Providing default reflection coefficient.");
	*reflection = DEFAULT_REFLECTION;
}

void	set_default_transparency(t_scene *scene, int type, void *obj,
			float *transparency)
{
	data_warning(scene, type, ((t_object *)obj),
			"Providing default transparency coefficient.");
	*transparency = DEFAULT_TRANSPARENCY;
}
