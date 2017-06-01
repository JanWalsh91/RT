/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:25:45 by tgros             #+#    #+#             */
/*   Updated: 2017/05/24 14:52:45 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "objparser.h"

/*
** Contains functions for parsing each value based on token.
*/

char	*parse_fov(t_parse_tools *t)
{
	float	new_fov;

	new_fov = NAN;
	if (isnan(new_fov = parse_float(t->input->value)) ||
		new_fov < 1 || new_fov > 179)
		return ("FOV index formatting error.\n\
The field of view is a float between 1 and 179.");
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
	float	new_intensity;

	new_intensity = NAN;
	if (isnan(new_intensity = parse_float(t->input->value)) ||
		new_intensity < 0)
		return ("Intensity index formatting error.\
Intensity is a positive float.");
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

char	*parse_filter(t_parse_tools *t)
{
	ft_strtoupper(t->input->value);
	if (ft_strcmp(t->input->value, "BLACK AND WHITE") == 0)
		t->current_camera->filter = F_BW;
	else if (ft_strcmp(t->input->value, "SEPIA") == 0)
		t->current_camera->filter = F_SEPIA;
	else if (ft_strcmp(t->input->value, "DEUTAN") == 0)
		t->current_camera->filter = F_DEUTAN;
	
	return (NULL);
}

char	*read_normal_map(t_parse_tools *t)
{
	// rt_file_warning(t, ".rt file name not provided.");
	t_color			*normal_map;

	if (!t->input->value)
		return ("Invalid texture name");
	if (!check_file_ext(t->input->value, "BMP"))
		return ("Texture must be a bmp file.");
	if (!(normal_map = read_bmp(t->input->value, &t->current_object->normal_map_dim)))
		return (strerror(errno));
	t->current_object->normal_map_name = ft_strdup(t->input->value); // free?
	t->current_object->normal_map = normal_map;
	return (NULL);
}

char	*read_obj_file(t_parse_tools *t)
{
	t_obj	*new_obj;
	char	*ret;

	//check if right place, 
	printf("READING OBJ\n");
	if ((ret = objparser(t->input->value, &new_obj)))
		return (ret);
	printf("ad : %p\n", new_obj);
	C(2);
	print_triangles(new_obj);
	if (!t->in_scene)
		t->global_attributes->obj = new_obj;
	else if (!t->in_object)
		t->scene_attributes->obj = new_obj;
	else if (t->in_object)
		t->object_attributes->obj = new_obj;
	t->object_attributes->rad = v_dist(new_obj->far_point1, (t_vec3){0, 0, 0}) * 2;
	return (NULL);
}

char	*parse_obj(t_parse_tools *t)
{
	printf("parse_obj\n");
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_OBJ;
	push_object(&t->scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
	return (NULL);
}
