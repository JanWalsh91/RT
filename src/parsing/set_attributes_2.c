/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attributes_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:07:02 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/07 20:25:50 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Sets parsed attributes to current object based on current type.
*/

void	set_attributes_plane(t_parse_tools *t, t_attributes *a)
{
	if (!v_isnan(a->look_at))
		t->current_object->look_at = a->look_at;
	if (!isnan(a->rad))
		t->current_object->rad = a->rad;
}

void	set_attributes_sphere(t_parse_tools *t, t_attributes *a)
{
	if (!isnan(a->rad))
		t->current_object->rad = a->rad;
}

void	set_attributes_cylinder(t_parse_tools *t, t_attributes *a)
{
	if (!v_isnan(a->look_at))
		t->current_object->look_at = a->look_at;
	if (!isnan(a->rad))
		t->current_object->rad = a->rad;
	if (!isnan(a->height))
		t->current_object->height = a->height;
}

void	set_attributes_cone(t_parse_tools *t, t_attributes *a)
{
	if (!v_isnan(a->look_at))
		t->current_object->look_at = a->look_at;
	if (!isnan(a->rad))
		t->current_object->rad = a->rad;
	if (!isnan(a->height))
		t->current_object->height = a->height;
}
