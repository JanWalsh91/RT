/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/12 15:57:43 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Adds new_object to the end of list t_objects.
*/

void	push_object(t_object **objects_head, t_object *new_object)
{
	t_object	*obj_ptr;

	printf("push_object\n");
	if (new_object)
	{
		C(1)
		if (!(*objects_head))
			*objects_head = new_object;
		else
		{
			C(2)
			obj_ptr = *objects_head;
			C(3)
			while (obj_ptr->next)
				obj_ptr = obj_ptr->next;
			C(4)
			obj_ptr->next = new_object;
			C(5)
		}
		new_object->next = NULL;
		C(6)
	}
}
