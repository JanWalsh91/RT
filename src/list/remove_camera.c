/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:37:33 by tgros             #+#    #+#             */
/*   Updated: 2017/04/23 11:01:57 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "gui.h"

void	free_camera(t_camera *to_delete)
{
	if (to_delete->name)
		free(to_delete->name);
	free(to_delete);
}

// void	remove_camera(t_camera **head, t_camera *to_delete)
// {
// 	t_camera	*prev;
// 	t_camera	*tmp;

// 	if (!head || !*head)
// 		return ;
// 	prev = *head;
// 	if (prev == to_delete)
// 	{
// 		*head = prev->next;
// 		free_camera(to_delete);
// 		return ;
// 	}
// 	if (prev->next)
// 	{
// 		tmp = prev->next;
// 		while (tmp && tmp != to_delete)
// 		{
// 			prev = prev->next;
// 			tmp = tmp->next;
// 		}
// 		if (tmp == to_delete)
// 		{
// 			prev->next = tmp->next;
// 			free_camera(to_delete);
// 		}
// 	}
// 	else
// 	{
// 		free_camera(to_delete);
// 		*head = NULL;
// 	}
// }

void	remove_camera(t_camera *to_delete, t_gtk_tools *g)
{
	t_camera	*head;

	head = get_first_camera(g);
	if (!head)
		return ;
	while (head && head != to_delete)
		head = head->next;
	if (head == to_delete)
	{
		if (head->prev == NULL)
		{
			if (head->next)
				head->next->prev = NULL;
			else
				g->r->scene->cameras = NULL;
		}
		else
		{
			if (head->prev)
				head->prev->next = head->next;
			if (head->next)
				head->next->prev = head->prev;
		}
		if (head->prev)
			g->r->scene->cameras = head->prev;
		else if (head->next)
			g->r->scene->cameras = head->next;
		else
			g->r->scene->cameras = NULL;
		free_camera(head);
	}
}