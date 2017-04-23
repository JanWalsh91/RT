/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_delete_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:47:39 by tgros             #+#    #+#             */
/*   Updated: 2017/04/23 11:00:31 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_delete_camera(GtkWidget *button, t_gtk_tools *g)
{
    t_camera			*camera;
	GtkListBoxRow 		*list_box_row;
	GtkWidget			*widget;
	int					id;

    printf("sig_delete_camera\n");
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxCameras"));
	list_box_row = gtk_list_box_get_selected_row (GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index(list_box_row);
	camera = get_selected_camera(g);
	gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(list_box_row));
	remove_camera(camera, g);
	if (g->r->scene->cameras)
	{
		printf("%s\n", g->r->scene->cameras->name);
		gtk_list_box_select_row(GTK_LIST_BOX(widget), gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), id - 1 >= 0 ? id - 1 : 0));
		update_cameras_info_panel(g, get_selected_camera(g));
		sig_next_camera(NULL, g);
	}
	else
	{
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelCurrentCamera"));
		gtk_label_set_text(GTK_LABEL(widget), "None");
		gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonNextCamera")), false);
		gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonPreviousCamera")), false);
		widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ScrollWindowCamera"));
		gtk_widget_set_sensitive(widget, false);
		widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ButtonDeleteCamera"));
		gtk_widget_set_sensitive(widget, false);	
	}
	return (NULL);
}
