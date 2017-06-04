/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_cameras5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 14:41:44 by tgros             #+#    #+#             */
/*   Updated: 2017/06/04 14:44:36 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.h"

t_camera		*get_first_camera(t_gtk_tools *g)
{
	t_camera	*cam;

	cam = g->r->scene->cameras;
	while (cam && cam->prev)
		cam = cam->prev;
	return (cam);
}

t_camera		*get_selected_camera(t_gtk_tools *g)
{
	GtkWidget		*widget;
	GtkListBoxRow	*list_box_row;
	int				id;
	int				i;
	t_camera		*cam;

	printf("get_selected_camera\n");
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxCameras"));
	list_box_row = gtk_list_box_get_selected_row(GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index(list_box_row);
	i = -1;
	cam = get_first_camera(g);
	while (++i != id && cam)
		cam = cam->next;
	return ((cam && id == i) ? cam : NULL);
}

void			*sig_update_cam_dir_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;
	GtkWidget	*widget;

	printf("sig_update_cam_dir_x\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive(widget, TRUE);
	cam = get_selected_camera(g);
	cam->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"ComboBoxTextCamLookAtName"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"SpinButtonCameraDirectionY"));
	cam->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"SpinButtonCameraDirectionZ"));
	cam->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	cam->dir = v_norm(cam->dir);
	update_camera_ctw(cam);
	camera_render_sig(g);
	return (NULL);
}

void			*sig_update_cam_dir_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;
	GtkWidget	*widget;

	printf("sig_update_cam_dir_y\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive(widget, TRUE);
	cam = get_selected_camera(g);
	cam->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"ComboBoxTextCamLookAtName"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"SpinButtonCameraDirectionX"));
	cam->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"SpinButtonCameraDirectionZ"));
	cam->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	cam->dir = v_norm(cam->dir);
	update_camera_ctw(cam);
	camera_render_sig(g);
	return (NULL);
}

void			*sig_update_cam_dir_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;
	GtkWidget	*widget;

	printf("sig_update_cam_dir_z\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive(widget, TRUE);
	cam = get_selected_camera(g);
	cam->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"ComboBoxTextCamLookAtName"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"SpinButtonCameraDirectionX"));
	cam->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"SpinButtonCameraDirectionY"));
	cam->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	cam->dir = v_norm(cam->dir);
	update_camera_ctw(cam);
	camera_render_sig(g);
	return (NULL);
}
