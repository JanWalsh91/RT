/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_new_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:08:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/06 13:52:57 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

/*
** Adds a new camera in the list of cameras.
*/

void	*sig_new_camera(GtkWidget *widget, t_gtk_tools *g)
{
	t_camera	*camera;

	printf("sig_new_camera\n");
	if (!(camera = (t_camera *)ft_memalloc(sizeof(t_camera))))
		return (NULL);
	ft_bzero(camera, sizeof(t_camera));
	camera->fov = DEFAULT_FOV;
	camera->name = ft_strdup("New camera");
	camera->next = NULL;
	camera->prev = NULL;
	camera->ior = DEFAULT_IOR;
	init_camera(camera);
	if (g->r->scene->cameras)
	{
		camera->dir = g->r->scene->cameras->dir;
		camera->pos = g->r->scene->cameras->pos;
	}
	camera->dir = g->r->scene->cameras ? g->r->scene->cameras->dir : camera->dir;
	camera->pos = g->r->scene->cameras ? g->r->scene->cameras->pos : camera->pos;
	push_camera(&(g->r->scene->cameras), camera);
	update_grid_cameras(g);
	widget = get_widget(g, "ButtonNextCamera");
	gtk_widget_set_sensitive(widget, (g->r->scene->cameras->next != NULL));
	gtk_widget_set_sensitive(get_widget(g, "ScrollWindowCamera"), true);
	gtk_widget_set_sensitive(get_widget(g, "ButtonDeleteCamera"), true);
	gtk_widget_set_sensitive(get_widget(g, "ButtonRender"), true);
	g->r->update.cameras = 2;
	return (NULL);
}
