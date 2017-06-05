/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attributes_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 13:19:50 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 13:21:11 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Sets parsed attributes to current object based on current type.
*/

void	set_attributes_paraboloid(t_parse_tools *t, t_attributes *a)
{
	if (!v_isnan(a->look_at))
		t->current_object->look_at = a->look_at;
	if (!isnan(a->rad))
		t->current_object->rad = a->rad;
	if (!isnan(a->height))
		t->current_object->height = a->height;
}

void	set_attributes_obj(t_parse_tools *t, t_attributes *a)
{
	if (a->obj)
		t->current_object->obj = a->obj;
}
