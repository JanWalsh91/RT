/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:02:03 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a t_input n to the end of t_input input.
*/

#include "../../inc/rt.cuh"

void	input_pushback(t_input **input, t_input *n)
{
	t_input	*ptr;

	if (n)
	{
		if (!(*input))
			*input = n;
		else
		{
			ptr = *input;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = n;
		}
		n->next = NULL;
	}
}
