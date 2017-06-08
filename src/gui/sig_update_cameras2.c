/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_cameras2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 14:35:14 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.h"

static void	update_cam_dir(t_gtk_tools *g, t_camera *cam);

void		*sig_update_cam_lookat_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;

	cam = get_selected_camera(g);
	cam->look_at.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	cam->dir = v_norm(v_sub(cam->look_at, cam->pos));
	g->updating_gui = true;
	update_cam_dir(g, cam);
	g->updating_gui = false;
	update_camera_ctw(cam);
	camera_render_sig(g);
	return (NULL);
}

void		*sig_update_cam_lookat_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;

	cam = get_selected_camera(g);
	cam->look_at.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	cam->dir = v_norm(v_sub(cam->look_at, cam->pos));
	g->updating_gui = true;
	update_cam_dir(g, cam);
	g->updating_gui = false;
	update_camera_ctw(cam);
	camera_render_sig(g);
	return (NULL);
}

void		*sig_update_cam_lookat_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;

	cam = get_selected_camera(g);
	cam->look_at.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	cam->dir = v_norm(v_sub(cam->look_at, cam->pos));
	g->updating_gui = true;
	update_cam_dir(g, cam);
	g->updating_gui = false;
	update_camera_ctw(cam);
	camera_render_sig(g);
	return (NULL);
}

static void	update_cam_dir(t_gtk_tools *g, t_camera *cam)
{
	GtkWidget	*widget;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"ComboBoxTextCamLookAtName"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive(widget, false);
}
