/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:00:03 by tgros             #+#    #+#             */
/*   Updated: 2017/05/09 15:55:35 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

char	*parse_torus(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_TORUS;
	t->current_object->rad_torus = 1.5;
	push_object(&t->current_scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
	return (NULL);
}