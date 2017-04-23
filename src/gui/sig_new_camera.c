/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_new_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:08:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/23 11:01:44 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void    *sig_new_camera(GtkWidget *widget, t_gtk_tools *g)
{
    t_camera    *camera;

    printf("sig_new_camera\n");
    if (!(camera = (t_camera *)ft_memalloc(sizeof(t_camera))))
		return (NULL);
	ft_bzero(camera, sizeof(t_camera));
	
    // camera->pos = g->r->scene->cameras->pos; // --> WTF ?
    // camera->dir = g->r->scene->cameras->dir; // --> WTF ?
    camera->fov = DEFAULT_FOV;
	camera->name = ft_strdup("New camera");
	camera->next = NULL;
    init_camera(g->r->scene, camera);
	push_camera(&(g->r->scene->cameras), camera);
	update_grid_cameras(g);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonNextCamera"));
	(g->r->scene->cameras->next == NULL) ? gtk_widget_set_sensitive (widget, FALSE) :
		gtk_widget_set_sensitive (widget, TRUE);
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(g->builder, "ScrollWindowCamera")), true);
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(g->builder, "ButtonDeleteCamera")), true);
	return (NULL);
}