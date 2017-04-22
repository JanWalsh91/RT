/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:57:12 by tgros             #+#    #+#             */
/*   Updated: 2017/04/21 16:36:36 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

void	free_object(t_object *to_delete)
{
	if (to_delete->name)
				free(to_delete->name);
	free(to_delete);
}

void	remove_object(t_object **head, t_object *to_delete)
{
	t_object	*prev;
	t_object	*tmp;

	if (!head || !*head)
		return ;
	prev = *head;
	if (prev == to_delete)
	{
		*head = prev->next;
		free_object(to_delete);
		return ;
	}
	if (prev->next)
	{
		tmp = prev->next;
		while (tmp && tmp != to_delete)
		{
			prev = prev->next;
			tmp = tmp->next;
		}
		if (tmp == to_delete)
		{
			prev->next = tmp->next;
			free_object(to_delete);
		}
	}
	else
	{
		free_object(to_delete);
		*head = NULL;
	}
}
