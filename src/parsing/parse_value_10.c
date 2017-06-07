/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:00:03 by tgros             #+#    #+#             */
/*   Updated: 2017/06/07 20:24:57 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

/*
** Contains functions for parsing each value based on token.
*/

char	*parse_paraboloid(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_PARABOLOID;
	push_object(&t->scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
	return (NULL);
}

char	*parse_parent_index(t_parse_tools *t)
{
	short	new_index;

	new_index = 0;
	if ((new_index = ft_atoi(t->input->value)) < 0)
		return ("Parent index formatting error.");
	if (!t->in_scene)
		t->global_attributes->parent_index = new_index;
	else if (!t->in_object)
		t->scene_attributes->parent_index = new_index;
	else if (t->in_object)
		t->object_attributes->parent_index = new_index;
	return (NULL);
}

char	*parse_kflare(t_parse_tools *t)
{
	float	new_kflare;

	new_kflare = NAN;
	if (isnan(new_kflare = parse_float(t->input->value)) ||
		new_kflare < 0)
		return ("Flare coefficient formatting error.\
		Flare coefficient is a positive float.");
	if (!t->in_scene)
		t->global_attributes->kflare = new_kflare;
	else if (!t->in_object)
		t->scene_attributes->kflare = new_kflare;
	else if (t->in_object)
		t->object_attributes->kflare = new_kflare;
	if (t->in_object && t->current_type != T_LIGHT)
		return ("kflare attribute only applicable to lights.");
	return (NULL);
}
