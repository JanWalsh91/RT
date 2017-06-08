/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_13.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 12:09:16 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

char	*parse_beer_lambert(t_parse_tools *t)
{
	float	new_beer_lambert;

	new_beer_lambert = NAN;
	if (isnan(new_beer_lambert = parse_float(t->input->value)) ||
		new_beer_lambert < 0 || new_beer_lambert > 1)
		return ("Beer Lambert coefficient formatting error.\n\
		The Beer Lambert coefficient is a float between 0 and 1.");
	if (!t->in_scene)
		t->global_attributes->beer_lambert = new_beer_lambert;
	else if (!t->in_object)
		t->scene_attributes->beer_lambert = new_beer_lambert;
	else if (t->in_object)
		t->object_attributes->beer_lambert = new_beer_lambert;
	if (t->in_object && (t->current_type == T_LIGHT ||
		t->current_type == T_CAMERA))
		return ("Beer Lambert coefficient attribute \
		only applicable to objects.");
	return (NULL);
}
