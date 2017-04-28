/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:33:12 by tgros             #+#    #+#             */
/*   Updated: 2017/04/28 13:57:34 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"


void *update_grid_scene(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GdkRGBA		color;

	printf("update_grid_scene\n");
	print_scenes(g->r->scene);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "NoteBookMenu"));
	gtk_widget_set_visible(widget, TRUE);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonPreviousCamera"));
	gtk_widget_set_sensitive(widget, TRUE);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonNextCamera"));
	gtk_widget_set_sensitive(widget, TRUE);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonRender"));
	gtk_widget_set_sensitive(widget, TRUE);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ResolutionXSpinButton"));
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), g->r->scene->res.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ResolutionYSpinButton"));
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), g->r->scene->res.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "RayDepthSpinButton"));
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), g->r->scene->ray_depth);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "AmbientLightCoeffSpinButton"));
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), g->r->scene->ka);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "AmbientLightColorPicker"));
	color.red = g->r->scene->ambient_light_color.x / 255.0;
	color.green = g->r->scene->ambient_light_color.y / 255.0;
	color.blue = g->r->scene->ambient_light_color.z / 255.0;
	color.alpha = 1;
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER(widget), &color);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonPreviousCamera"));
	(g->r->scene->cameras->prev == NULL) ? gtk_widget_set_sensitive (widget, FALSE) :
		gtk_widget_set_sensitive (widget, TRUE);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonNextCamera"));
	(g->r->scene->cameras->next == NULL) ? gtk_widget_set_sensitive (widget, FALSE) :
		gtk_widget_set_sensitive (widget, TRUE);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelCurrentCamera"));
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras->name);
	return (NULL);
}

void	scene_render_sig(t_gtk_tools *g)
{
	g->r->update.render = 1;
	g->r->update.scene = 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
}

void	*sig_update_res_x(GtkWidget *SpinButton, t_gtk_tools *g)
{
	printf("sig_update_res_x\n");
	g->r->scene->res.x = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SpinButton));
	g->r->scene->image_aspect_ratio = (float)g->r->scene->res.x / (float)g->r->scene->res.y;
	g->r->update.resolution = 2;
	gtk_window_resize (GTK_WINDOW(g->win), g->r->scene->res.x, g->r->scene->res.y);
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_res_y(GtkWidget *SpinButton, t_gtk_tools *g)
{
	g->r->scene->res.y = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SpinButton));
	g->r->scene->image_aspect_ratio = (float)g->r->scene->res.x / (float)g->r->scene->res.y;
	return (NULL);
}

void	*sig_update_ambient_light_coeff(GtkWidget *spin_button, t_gtk_tools *g)
{
	g->r->scene->ka = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_udpate_ambient_light_color(GtkWidget *color_chooser, t_gtk_tools *g)
{
	GdkRGBA			color;

	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(color_chooser), &color);
	g->r->scene->ambient_light_color.x = color.red * 255;
	g->r->scene->ambient_light_color.y = color.green * 255;
	g->r->scene->ambient_light_color.z = color.blue * 255;
	g->r->scene->ambient_light_color = v_clamp(g->r->scene->ambient_light_color, 0.0, 255.0);
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_next_camera(GtkWidget *button, t_gtk_tools *g)
{
	GtkWidget	*widget;

	printf("sig_next_camera\n");
	if (!g->r->scene->cameras->next)
		return (NULL);
	g->r->scene->cameras = g->r->scene->cameras->next;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelCurrentCamera"));
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras->name);
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonNextCamera")), (gboolean)g->r->scene->cameras->next);
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonPreviousCamera")), (gboolean)g->r->scene->cameras->prev);
	// update_grid_scene(g); // --> WTF ?
	g->r->update.cameras = 1;
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_prev_camera(GtkWidget *button, t_gtk_tools *g)
{
	GtkWidget	*widget;

	printf("sig_prev_camera\n");
	if (!g->r->scene->cameras->prev)
		return (NULL);
	g->r->scene->cameras = g->r->scene->cameras->prev;	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelCurrentCamera"));
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras->name);
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonNextCamera")), (gboolean)g->r->scene->cameras->next);
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonPreviousCamera")), (gboolean)g->r->scene->cameras->prev);
	// update_grid_scene(g); // --> WTF ?
	g->r->update.cameras = 1;
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_ray_depth(GtkWidget *spin_button, t_gtk_tools *g)
{
	printf("sig_update_ray_depth\n");
	g->r->scene->ray_depth = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	g->r->update.render = 1;
	g->r->update.scene = 1;
	g->r->update.ray_depth = 2;
	if (g->win)
		gtk_widget_queue_draw(g->win);
	return (NULL);
}

void	*sig_update_is_shadow(GtkWidget *check_box, t_gtk_tools *g)
{
	printf("sig_update_is_shadow\n");
	g->r->scene->is_shadow = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_box));
	printf("%d\n", gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_box)));
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}


void	*sig_update_is_diffuse(GtkWidget *check_box, t_gtk_tools *g)
{
	GtkWidget	*widget;

	printf("sig_update_is_diffuse\n");
	g->r->scene->is_diffuse = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_box));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "IsShadowCheckBox"));
	gtk_widget_set_sensitive(widget, g->r->scene->is_diffuse);
	if (!g->r->scene->is_diffuse)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), false);
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}


void	*sig_update_is_specular(GtkWidget *check_box, t_gtk_tools *g)
{
	printf("sig_update_is_specular\n");
	g->r->scene->is_specular = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_box));
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}


