/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_11.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 12:08:19 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 12:10:07 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

/*
** Contains functions for parsing each value based on token.
*/

char	*parse_radius_2(t_parse_tools *t)
{
	float	new_radius_2;

	new_radius_2 = NAN;
	if (isnan(new_radius_2 = parse_float(t->input->value)) ||
		new_radius_2 <= 0)
		return ("Radius 2 formatting error.");
	if (!t->in_scene)
		t->global_attributes->rad_torus = new_radius_2;
	else if (!t->in_object)
		t->scene_attributes->rad_torus = new_radius_2;
	else if (t->in_object)
		t->object_attributes->rad_torus = new_radius_2;
	if (t->in_object && t->current_type != T_TORUS)
		return ("Radius 2 attribute only applicable \
		to toruses.");
	return (NULL);
}

char	*parse_obj(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_OBJ;
	push_object(&t->scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
	return (NULL);
}
