/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_new_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:08:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/13 10:56:28 by jwalsh           ###   ########.fr       */
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
	
    camera->pos = g->r->scene->cameras->pos;
    camera->dir = g->r->scene->cameras->dir;
    camera->fov = DEFAULT_FOV;
	camera->name = ft_strdup("New camera");
	camera->next = NULL;
    init_camera(g->r->scene, camera);
	push_camera(&(g->r->scene->cameras), camera);
	update_cameras_panel(g);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonNextCamera"));
	(g->r->scene->cameras->next == NULL) ? gtk_widget_set_sensitive (widget, FALSE) :
		gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}