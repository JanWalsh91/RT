/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:18:11 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/20 14:58:57 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Contains functions for parsing each value based on token.
*/

char	*parse_fov(t_parse_tools *t)
{
	double	new_fov;

	new_fov = NAN;
	if (isnan(new_fov = parse_double(t->input->value)) ||
		new_fov < 1 || new_fov > 179)
		return ("FOV index formatting error.\n\
The field of view is a double between 1 and 179.");
	if (!t->in_scene)
		t->global_attributes->fov = new_fov;
	else if (!t->in_object)
		t->scene_attributes->fov = new_fov;
	else if (t->in_object)
		t->object_attributes->fov = new_fov;
	if (t->in_object && t->current_type != T_CAMERA)
		return ("FOV (field of view) attribute only applicable to cameras.");
	return (NULL);
}

char	*parse_intensity(t_parse_tools *t)
{
	double	new_intensity;

	new_intensity = NAN;
	if (isnan(new_intensity = parse_double(t->input->value)) ||
		new_intensity < 0)
		return ("Intensity index formatting error.\
Intensity is a positive double.");
	if (!t->in_scene)
		t->global_attributes->intensity = new_intensity;
	else if (!t->in_object)
		t->scene_attributes->intensity = new_intensity;
	else if (t->in_object)
		t->object_attributes->intensity = new_intensity;
	if (t->in_object && t->current_type != T_LIGHT)
		return ("Intensity attribute only applicable to lights.");
	return (NULL);
}

char	*import_rt_file(t_parse_tools *t)
{
	rt_file_warning(t, "Import: feature not yet available.");
	return (NULL);
}

char	*read_rt_file(t_parse_tools *t)
{
	rt_file_warning(t, ".rt file name not provided.");
	return (NULL);
}

char	*read_obj_file(t_parse_tools *t)
{
	rt_file_warning(t, "Read obj file: feature not yet available.");
	return (NULL);
}
