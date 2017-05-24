/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:00:03 by tgros             #+#    #+#             */
/*   Updated: 2017/05/23 11:01:39 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

char	*parse_torus(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_TORUS;
	t->current_object->rad_torus = 0.1;
	push_object(&t->scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
	return (NULL);
}

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
	unsigned short	new_index;

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