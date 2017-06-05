/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_delete_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:47:39 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 14:48:30 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	set_gui_no_camera_left(t_gtk_tools *g);

void		*sig_delete_camera(GtkWidget *button, t_gtk_tools *g)
{
	t_camera			*camera;
	GtkListBoxRow		*list_box_row;
	GtkWidget			*widget;
	int					id;

	(void)button;
	printf("sig_delete_camera\n");
	widget = get_widget(g, "ListBoxCameras");
	list_box_row = gtk_list_box_get_selected_row(GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index(list_box_row);
	camera = get_selected_camera(g);
	gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(list_box_row));
	remove_camera(camera, g);
	if (g->r->scene->cameras)
	{
		gtk_list_box_select_row(GTK_LIST_BOX(widget),
			gtk_list_box_get_row_at_index(
				GTK_LIST_BOX(widget), id - 1 >= 0 ? id - 1 : 0));
		update_cameras_info_panel(g, get_selected_camera(g));
		sig_next_camera(NULL, g);
	}
	else
		set_gui_no_camera_left(g);
	return (NULL);
}

static void	set_gui_no_camera_left(t_gtk_tools *g)
{
	GtkWidget	*widget;

	widget = get_widget(g, "LabelCurrentCamera");
	gtk_label_set_text(GTK_LABEL(widget), "None");
	gtk_widget_set_sensitive(get_widget(g, "ButtonNextCamera"), false);
	gtk_widget_set_sensitive(get_widget(g, "ButtonPreviousCamera"), false);
	gtk_widget_set_sensitive(get_widget(g, "ButtonRender"), false);
	widget = get_widget(g, "ScrollWindowCamera");
	gtk_widget_set_sensitive(widget, false);
	widget = get_widget(g, "ButtonDeleteCamera");
	gtk_widget_set_sensitive(widget, false);
}
