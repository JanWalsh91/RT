/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_cameras.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 14:41:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 14:14:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.cuh"

static int	set_gui_no_camera(t_gtk_tools *g);
static void	update_cameras_info_panel1(t_gtk_tools *g, t_camera *camera);

void		*update_grid_cameras(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GtkWidget	*label;
	t_camera	*camera;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
													"ListBoxCameras"));
	gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)
								G_CALLBACK(gtk_widget_destroy), NULL);
	camera = get_first_camera(g);
	while (camera)
	{
		label = gtk_label_new(camera->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		camera = camera->next;
	}
	if (set_gui_no_camera(g))
		return (NULL);
	gtk_list_box_select_row(GTK_LIST_BOX(widget),
			gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), 0));
	update_cameras_info_panel(g, get_first_camera(g));
	gtk_widget_show_all(widget);
	return (NULL);
}

static int	set_gui_no_camera(t_gtk_tools *g)
{
	GtkWidget	*widget;

	if (g->r->scene->cameras)
		return (0);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"ScrollWindowCamera"));
	gtk_widget_set_sensitive(widget, FALSE);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"ButtonDeleteCamera"));
	gtk_widget_set_sensitive(widget, FALSE);
	return (1);
}

void		update_cameras_info_panel(t_gtk_tools *g, t_camera *camera)
{
	GtkWidget	*widget;

	g->updating_gui = true;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"EntryCameraName"));
	gtk_entry_set_text(GTK_ENTRY(widget), camera->name);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraPosX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->pos.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraPosY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->pos.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraPosZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->pos.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraLookAtX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->look_at.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraLookAtY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->look_at.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraLookAtZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->look_at.z);
	update_cameras_info_panel1(g, camera);
}

static void	update_cameras_info_panel1(t_gtk_tools *g, t_camera *camera)
{
	GtkWidget	*widget;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"ComboBoxTextCamLookAtName"));
	gtk_widget_set_sensitive(widget, TRUE);
	init_cam_look_at_combo_box(widget, g);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive(widget, FALSE);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraFov"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->fov);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraIOR"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->ior);
	g->updating_gui = false;
}
