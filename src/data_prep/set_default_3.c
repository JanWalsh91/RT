/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:29:45 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Functions for setting default values for
** - height
** - direction (camera)
** - direction (objects)
** - direction (light)
*/

void	set_default_height(t_scene *scene, int type, void *obj, double *height)
{
	if (type == T_CONE || type == T_CYLINDER)
		data_warning(scene, type, ((t_object *)obj),
			"Providing default height.");
	*height = DEFAULT_HEIGHT;
}

void	set_default_cam_dir(t_scene *scene, int type, void *cam, t_vec3 *dir)
{
	data_warning(scene, type, ((t_camera *)cam),
		"Providing default direction.");
	*dir = v_new(DEFAULT_CAM_DIR_X, DEFAULT_CAM_DIR_Y, DEFAULT_CAM_DIR_Z);
}

void	set_default_obj_dir(t_scene *scene, int type, void *obj, t_vec3 *dir)
{
	if (type != T_LIGHT)
		data_warning(scene, type, ((t_light *)obj),
			"Providing default direction.");
	else
		return ;
	*dir = v_new(DEFAULT_DIR_X, DEFAULT_DIR_Y, DEFAULT_DIR_Z);
}

void	set_default_light_dir(t_scene *scene, int type, void *obj, t_vec3 *dir)
{
	if (type == T_LIGHT)
		data_warning(scene, type, ((t_light *)obj),
			"Providing default direction.");
	else
		return ;
	*dir = v_new(DEFAULT_DIR_X, -DEFAULT_DIR_Y, DEFAULT_DIR_Z);
}
