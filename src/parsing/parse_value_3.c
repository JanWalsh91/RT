/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:13:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/25 16:38:50 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

static void	free_s2(char **s2);

/*
** Contains functions for parsing each value based on token.
*/

char		*parse_cone(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_CONE;
	push_object(&t->current_scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
	return (NULL);
}

char		*parse_resolution(t_parse_tools *t)
{
	char	**s2;
	t_pt2	new_res;
	bool	invalid;

	invalid = false;
	if (ft_charcount(t->input->value, ',') != 1 && (invalid = true))
		return ("Resolution formatting error.");
	s2 = split_trim(t->input->value, ',');
	if (!(s2[0] && s2[1]) && (invalid = true))
		return ("Resolution formatting error.");
	// if ((new_res.x = ft_atoi(s2[0])) < 1 || new_res.x > 2560 ||
	// 	(new_res.y = ft_atoi(s2[1])) < 1 || new_res.y > 1600)
	if ((new_res.x = ft_atoi(s2[0])) < 1 || new_res.x > 4000 || // TODO: max value ?
	(new_res.y = ft_atoi(s2[1])) < 1 || new_res.y > 4000)
	{
		invalid = true;
		rt_file_warning(t, "Resolution width and height invalid.");
	}
	free_s2(s2);
	if (invalid)
		return (NULL);
	if (!t->in_scene)
		t->global_attributes->res = new_res;
	else if (!t->in_object)
		t->current_scene->res = new_res;
	else if (t->in_object)
		rt_file_warning(t, "You tryin' to give a resolution to an object?");
	return (NULL);
}

static void	free_s2(char **s2)
{
	if (s2 && s2[0])
		free(s2[0]);
	if (s2 && s2[1])
		free(s2[1]);
	if (s2)
		free(s2);
}

char		*parse_ray_depth(t_parse_tools *t)
{
	int	new_ray_depth;

	if (!t->input->value)
		return ("Ray depth formatting error.");
	if ((new_ray_depth = ft_atoi(t->input->value)) < 1)
		return ("Ray depth must be a positive and non-zero integer.");
	if (!t->in_scene)
		t->global_attributes->ray_depth = new_ray_depth;
	else if (!t->in_object)
		t->current_scene->ray_depth = new_ray_depth;
	else if (t->in_object)
		return ("Ray depth is a scene attribute, not an object attribute!");
	return (NULL);
}

char		*parse_background_color(t_parse_tools *t)
{
	t_vec3	new_col;

	if (v_isnan(new_col = get_color(t, t->input->value)))
		return ("Background color formatting error.");
	if (new_col.x < 0 || new_col.y < 0 || new_col.z < 0 ||
		new_col.x > 255 || new_col.y > 255 || new_col.z > 255)
	{
		new_col = v_clamp(new_col, 0, 255);
		rt_file_warning(t, "Color clamped to [0 - 255].");
	}
	if (!t->in_scene)
		t->global_attributes->col = new_col;
	else if (!t->in_object)
		t->current_scene->background_color = new_col;
	else if (t->in_object)
		return ("Objects cannot have background colors!");
	return (NULL);
}

