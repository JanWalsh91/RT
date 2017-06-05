/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:35:52 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 11:42:11 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Removes a light.
*/
static void		remove_light2(t_light *prev,
				t_light *to_delete);

void			free_light(t_light *to_delete)
{
	if (to_delete->name)
		free(to_delete->name);
	free(to_delete);
}

void			remove_light(t_light **head, t_light *to_delete)
{
	t_light	*prev;

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
		remove_light2(prev, to_delete);
	else
	{
		free_light(to_delete);
		*head = NULL;
	}
}

static void		remove_light2(t_light *prev,
				t_light *to_delete)
{
	t_light	*tmp;

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
