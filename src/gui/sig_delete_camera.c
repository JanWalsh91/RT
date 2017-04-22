/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_delete_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:47:39 by tgros             #+#    #+#             */
/*   Updated: 2017/04/21 18:01:55 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_delete_camera(GtkWidget *widget, t_gtk_tools *g)
{
    t_camera			*camera;
	GtkListBoxRow 	*list_box_row;
	GtkWidget		*list_box;
	int				id;

    printf("sig_delete_camera\n");
	list_box = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxCameras"));
	list_box_row = gtk_list_box_get_selected_row (GTK_LIST_BOX(list_box));
	id = gtk_list_box_row_get_index(list_box_row);
	camera = get_selected_camera(g);
	gtk_container_remove(GTK_CONTAINER(list_box), GTK_WIDGET(list_box_row));
	remove_camera(&g->r->scene->cameras, camera);
	C(3)
	if (g->r->scene->cameras)
	{
		C(4)
		gtk_list_box_select_row(GTK_LIST_BOX(list_box), gtk_list_box_get_row_at_index(GTK_LIST_BOX(list_box), id - 1 >= 0 ? id - 1 : 0));
		C(5)
		update_cameras_info_panel(g, get_selected_camera(g));
		C(6)
	}
	else
	{
		list_box = GTK_WIDGET(gtk_builder_get_object(g->builder, "ScrollWindowCamera"));
		gtk_widget_set_sensitive(list_box, false);
	}
	return (NULL);
}
