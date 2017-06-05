/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_cameras3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 14:35:53 by tgros             #+#    #+#             */
/*   Updated: 2017/06/04 14:43:17 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.h"

static void	set_cam_dir_values(t_gtk_tools *g, t_camera *cam);

void		*sig_cam_dir_normalize(GtkWidget *button, t_gtk_tools *g)
{
	t_camera	*cam;
	GtkWidget	*widget;

	(void)button;
	printf("sig_obj_dir_normalize\n");
	cam = get_selected_camera(g);
	cam->dir = v_norm(cam->dir);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive(widget, FALSE);
	if (g->updating_gui)
		return (NULL);
	g->updating_gui = true;
	set_cam_dir_values(g, cam);
	g->updating_gui = false;
	update_camera_ctw(cam);
	camera_render_sig(g);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
											"ButtonCamDirNormalize"));
	gtk_widget_set_sensitive(widget, FALSE);
	return (NULL);
}

static void	set_cam_dir_values(t_gtk_tools *g, t_camera *cam)
{
	GtkWidget	*widget;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
										"SpinButtonCameraDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.z);
}

void		*sig_update_cam_fov(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;

	printf("sig_update_cam_fov\n");
	cam = get_selected_camera(g);
	cam->fov = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	update_camera_scale(cam);
	(g->updating_gui) ? 0 : camera_render_sig(g);
	return (NULL);
}

void		*sig_update_camera_filter(GtkWidget *list_box, t_gtk_tools *g)
{
	printf("%d\n", gtk_combo_box_get_active(GTK_COMBO_BOX(list_box)));
	g->r->scene->cameras->filter =
		gtk_combo_box_get_active(GTK_COMBO_BOX(list_box));
	(g->updating_gui) ? 0 : camera_render_sig(g);
	return (NULL);
}

void		*sig_update_cam_ior(GtkWidget *spin_button, t_gtk_tools *g)
{
	printf("sig_update_cam_ior\n");
	g->r->scene->cameras->ior =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : camera_render_sig(g);
	return (NULL);
}
