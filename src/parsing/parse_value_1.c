/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:11:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 11:57:07 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Functions for parsing each value based on token.
*/

char	*parse_open_bracket(t_parse_tools *t)
{
	(void)t;
	return ("Extraneous open bracket.");
}

char	*parse_close_bracket(t_parse_tools *t)
{
	if (t->in_object)
	{
		set_attributes(t, t->object_attributes);
		reset_attributes(t->object_attributes);
		t->in_object = false;
	}
	else if (t->in_scene)
		t->in_scene = false;
	else
		return ("Extraneous closing bracket.");
	return (NULL);
}

char	*parse_empty_line(t_parse_tools *t)
{
	(void)t;
	return (NULL);
}

char	*parse_scene(t_parse_tools *t)
{
	char	*ret;

	if ((ret = can_add_new_scene(t)))
		return (ret);
	t->scene = get_new_scene(t);
	if (t->global_attributes->res.x != -1)
		t->scene->res = t->global_attributes->res;
	if (t->global_attributes->ray_depth != -1)
		t->scene->ray_depth = t->global_attributes->ray_depth;
	if (!isnan(t->global_attributes->ka))
		t->scene->ka = t->global_attributes->ka;
	if (!v_isnan(t->global_attributes->ambient_light_color))
		t->scene->ambient_light_color =
			t->global_attributes->ambient_light_color;
	t->input = t->input->next;
	return (NULL);
}

char	*parse_camera(t_parse_tools *t)
{
	char	*ret;

	if ((ret = can_add_new_object(t)))
		return (ret);
	t->current_type = T_CAMERA;
	t->current_camera = get_new_camera(t);
	push_camera(&t->scene->cameras, t->current_camera);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
	return (NULL);
}
