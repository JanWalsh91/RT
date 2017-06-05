/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:37:33 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 11:43:16 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "gui.h"

static void	set_current_camera(t_camera *head, t_gtk_tools *g);

void		free_camera(t_camera *to_delete)
{
	if (to_delete->name)
		free(to_delete->name);
	free(to_delete);
}

void		remove_camera(t_camera *to_delete, t_gtk_tools *g)
{
	t_camera	*head;

	head = get_first_camera(g);
	if (!head)
		return ;
	while (head && head != to_delete)
		head = head->next;
	if (head != to_delete)
		return ;
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
	set_current_camera(head, g);
	free_camera(head);
}

static void	set_current_camera(t_camera *head, t_gtk_tools *g)
{
	if (head->prev)
		g->r->scene->cameras = head->prev;
	else if (head->next)
		g->r->scene->cameras = head->next;
	else
	{
		g->r->scene->cameras = NULL;
		gtk_widget_destroy(GTK_WIDGET(g->win));
	}
}
