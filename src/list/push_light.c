/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:46:09 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Adds new_light to the end of list t_lights.
*/

void	push_light(t_light **lights_head, t_light *new_light)
{
	t_light	*light_ptr;

	if (new_light)
	{
		if (!(*lights_head))
			*lights_head = new_light;
		else
		{
			light_ptr = *lights_head;
			while (light_ptr->next)
				light_ptr = light_ptr->next;
			light_ptr->next = new_light;
		}
		new_light->next = NULL;
	}
}
