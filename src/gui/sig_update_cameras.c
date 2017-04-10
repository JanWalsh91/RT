/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_cameras.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 14:41:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/10 14:42:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*update_cameras_panel(t_gtk_tools *g) //change name
{
	GtkWidget	*widget;
	GtkWidget	*label;
	GdkRGBA		color;
	t_camera    *camera;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxLights"));

	light = g->r->scene->lights;
	while (light)
	{
		label = gtk_label_new(light->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		light = light->next;
	}
	if (!g->r->scene->lights)
		return (NULL);
	
	gtk_list_box_select_row(GTK_LIST_BOX(widget), gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), 0));
	update_lights_info_panel(g, g->r->scene->lights);
	
	gtk_widget_show_all(widget);
	return (NULL);
}