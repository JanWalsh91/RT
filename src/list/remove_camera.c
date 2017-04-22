/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:37:33 by tgros             #+#    #+#             */
/*   Updated: 2017/04/21 17:44:42 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

void	free_camera(t_camera *to_delete)
{
	if (to_delete->name)
		free(to_delete->name);
	free(to_delete);
}

void	remove_camera(t_camera **head, t_camera *to_delete)
{
	t_camera	*prev;
	t_camera	*tmp;

	if (!head || !*head)
		return ;
	prev = *head;
	if (prev == to_delete)
	{
		*head = prev->next;
		free_camera(to_delete);
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
			free_camera(to_delete);
		}
	}
	else
	{
		free_camera(to_delete);
		*head = NULL;
	}
}
