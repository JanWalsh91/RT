/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:35:52 by tgros             #+#    #+#             */
/*   Updated: 2017/04/21 16:36:33 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

void	free_light(t_light *to_delete)
{
	if (to_delete->name)
				free(to_delete->name);
	free(to_delete);
}

void	remove_light(t_light **head, t_light *to_delete)
{
	t_light	*prev;
	t_light	*tmp;

	if (!head || !*head)
		return ;
	prev = *head;
	if (prev == to_delete)
	{
		*head = prev->next;
		free_light(to_delete);
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
			free_light(to_delete);
		}
	}
	else
	{
		free_light(to_delete);
		*head = NULL;
	}
}
