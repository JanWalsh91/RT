/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:35:28 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/20 14:59:53 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

static t_vec3	look_at_object2(t_parse_tools *t, char *value);

/*
** Contains helper functions for parsing each value based on token.
*/

char				*can_add_new_scene(t_parse_tools *t)
{
	if (!t->in_scene)
		t->in_scene = true;
	else
		return ("Cannot add new scene within a scene.");
		// rt_file_error_exit(t, "Cannot add new scene within a scene.");
	if (!t->input->next)
		return ("New scene must be followed by open bracket.");
		// rt_file_error_exit(t, "New scene must be followed by open bracket.");
	if (t->input->next->token != T_OPEN_BRACKET)
	{
		t->input = t->input->next;
		return ("New scene must be followed by open bracket.");
		// rt_file_error_exit(t, "New scene must be followed by open bracket.");
	}
	return (NULL);
}

char				*can_add_new_object(t_parse_tools *t)
{
	if (!t->in_scene)
		return ("Cannot add new object outside a scene.");
		// rt_file_error_exit(t, "Cannot add new object outside a scene.");
	if (!t->in_object)
		t->in_object = true;
	else
		return ("Cannot add new object inside another object.");
		// rt_file_error_exit(t, "Cannot add new object inside another object.");
	if (t->input->next->token != T_OPEN_BRACKET)
	{
		t->input = t->input->next;
		return ("New object must be followed by open bracket.");
		// rt_file_error_exit(t, "New object must be followed by open bracket.");
	}
	return (NULL);
}

t_vec3			look_at_object(t_parse_tools *t, char *value)
{
	t_object	*o_ptr;
	t_light		*l_ptr;

	o_ptr = t->scenes->objects;
	while (o_ptr)
	{
		if (!ft_strcmp(value, o_ptr->name))
			return (o_ptr->pos);
		o_ptr = o_ptr->next;
	}
	l_ptr = t->scenes->lights;
	while (l_ptr)
	{
		if (!ft_strcmp(value, l_ptr->name))
			return (l_ptr->pos);
		l_ptr = l_ptr->next;
	}
	return (look_at_object2(t, value));
}

static t_vec3	look_at_object2(t_parse_tools *t, char *value)
{
	t_camera	*c_ptr;

	c_ptr = t->scenes->cameras;
	while (c_ptr)
	{
		if (!ft_strcmp(value, c_ptr->name))
			return (c_ptr->pos);
		c_ptr = c_ptr->next;
	}
	rt_file_warning(t, "Object to look at not found.\n\
Make sure to declare the object to look at before the look_at call.");
	return (v_new(NAN, NAN, NAN));
}
