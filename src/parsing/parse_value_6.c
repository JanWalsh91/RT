/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:17:42 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/20 14:58:18 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Contains functions for parsing each value based on token.
*/

char	*parse_specular_coef(t_parse_tools *t)
{
	double	new_specular_coef;

	new_specular_coef = NAN;
	if (isnan(new_specular_coef = parse_double(t->input->value)) ||
		new_specular_coef < 0 || new_specular_coef > 1)
	{
		return ("Specular coefficient formatting error.\n\
The specular coefficient (ks) is a double between 0 and 1.");
		return (NULL);
	}
	if (!t->in_scene)
		t->global_attributes->ks = new_specular_coef;
	else if (!t->in_object)
		t->scene_attributes->ks = new_specular_coef;
	else if (t->in_object)
		t->object_attributes->ks = new_specular_coef;
	if (t->in_object && (t->current_type == T_LIGHT ||
		t->current_type == T_CAMERA))
		return ("Specular coefficient (ks) attribute \
only applicable to objects.");
	return (NULL);
}

char	*parse_specular_exponent(t_parse_tools *t)
{
	double	new_specular_exp;

	new_specular_exp = NAN;
	if (isnan(new_specular_exp = parse_double(t->input->value)) ||
		new_specular_exp <= 0)
		return ("Specular exponent formatting error.");
	if (!t->in_scene)
		t->global_attributes->specular_exp = new_specular_exp;
	else if (!t->in_object)
		t->scene_attributes->specular_exp = new_specular_exp;
	else if (t->in_object)
		t->object_attributes->specular_exp = new_specular_exp;
	if (t->in_object && (t->current_type == T_LIGHT ||
		t->current_type == T_CAMERA))
		return ("Specular exponent attribute only applicable to objects.");
	return (NULL);
}

char	*parse_ior(t_parse_tools *t)
{
	double	new_ior;

	new_ior = NAN;
	if (isnan(new_ior = parse_double(t->input->value)) || new_ior <= 0)
		return ("Ior formatting error.");
	if (!t->in_scene)
		t->global_attributes->specular_exp = new_ior;
	else if (!t->in_object)
		t->scene_attributes->specular_exp = new_ior;
	else if (t->in_object)
		t->object_attributes->specular_exp = new_ior;
	if (t->in_object && (t->current_type == T_LIGHT ||
		t->current_type == T_CAMERA))
		return ("Ior attribute only applicable to objects.");
	return (NULL);
}

char	*parse_reflection(t_parse_tools *t)
{
	double	new_reflection_coef;

	new_reflection_coef = NAN;
	if (isnan(new_reflection_coef = parse_double(t->input->value)) ||
		new_reflection_coef < 0 || new_reflection_coef > 1)
		return ("Reflection coefficient formatting error.\n\
The reflection coefficient is a double between 0 and 1.");
	if (!t->in_scene)
		t->global_attributes->reflection = new_reflection_coef;
	else if (!t->in_object)
		t->scene_attributes->reflection = new_reflection_coef;
	else if (t->in_object)
		t->object_attributes->reflection = new_reflection_coef;
	if (t->in_object && (t->current_type == T_LIGHT ||
		t->current_type == T_CAMERA))
		return ("Reflection coefficient attribute \
only applicable to objects.");
	return (NULL);
}

char	*parse_transparency(t_parse_tools *t)
{
	double	new_transparency_coef;

	new_transparency_coef = NAN;
	if (isnan(new_transparency_coef = parse_double(t->input->value)) ||
		new_transparency_coef < 0 || new_transparency_coef > 1)
		return ("Transparency coefficient formatting error.\n\
The reflection coefficient is a double between 0 and 1.");
	if (!t->in_scene)
		t->global_attributes->transparency = new_transparency_coef;
	else if (!t->in_object)
		t->scene_attributes->transparency = new_transparency_coef;
	else if (t->in_object)
		t->object_attributes->transparency = new_transparency_coef;
	if (t->in_object && (t->current_type == T_LIGHT ||
		t->current_type == T_CAMERA))
		return ("Transparency coefficient attribute \
only applicable to objects.");
	return (NULL);
}
