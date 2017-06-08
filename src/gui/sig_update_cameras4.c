/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_cameras4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 14:38:45 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.h"

static void	populate_combo_box(t_gtk_tools *g, GtkWidget *widget);
static void	set_lookat_dir_values(t_gtk_tools *g, t_vec3 l_at, t_camera *cam);

void		init_cam_look_at_combo_box(GtkWidget *widget, t_gtk_tools *g)
{
	int			id;

	id = (gtk_combo_box_get_has_entry(GTK_COMBO_BOX(widget))) ?
		gtk_combo_box_get_active(GTK_COMBO_BOX(widget)) : 0;
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(widget));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "");
	populate_combo_box(g, widget);
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), id);
	gtk_widget_show_all(widget);
}

static void	populate_combo_box(t_gtk_tools *g, GtkWidget *widget)
{
	t_object	*obj;
	t_light		*light;
	t_camera	*camera;

	obj = g->r->scene->objects;
	while (obj)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), obj->name);
		obj = obj->next;
	}
	light = g->r->scene->lights;
	while (light)
	{
		if (!v_isnan(light->pos))
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget),
															light->name);
		light = light->next;
	}
	camera = get_first_camera(g);
	while (camera)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget),
															camera->name);
		camera = camera->next;
	}
}

void		*sig_update_cam_lookat_name(GtkWidget *combo_box, t_gtk_tools *g)
{
	t_vec3		look_at;
	t_camera	*cam;

	cam = get_selected_camera(g);
	if (v_isnan(look_at = get_look_at_obj(GTK_COMBO_BOX(combo_box), g)))
		return (NULL);
	cam->dir = v_norm(v_sub(look_at, cam->pos));
	if (g->updating_gui)
		return (NULL);
	g->updating_gui = true;
	set_lookat_dir_values(g, look_at, cam);
	update_camera_ctw(cam);
	g->updating_gui = false;
	camera_render_sig(g);
	return (NULL);
}

static void	set_lookat_dir_values(t_gtk_tools *g, t_vec3 l_at, t_camera *cam)
{
	GtkWidget	*widget;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"SpinButtonCameraLookAtX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), l_at.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"SpinButtonCameraLookAtY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), l_at.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"SpinButtonCameraLookAtZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), l_at.z);
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
	gtk_widget_set_sensitive(widget, TRUE);
}

void		camera_render_sig(t_gtk_tools *g)
{
	g->r->update.render = 1;
	g->r->update.cameras = 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
}
