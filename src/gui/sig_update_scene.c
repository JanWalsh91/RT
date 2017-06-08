/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:33:12 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 14:14:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.cuh"

static void	update_scene_gui(t_gtk_tools *g, GtkBuilder *b);

void		*update_grid_scene(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GdkRGBA		color;
	GtkBuilder	*b;

	b = GTK_BUILDER(g->builder);
	update_scene_gui(g, b);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ButtonPreviousCamera"));
	(g->r->scene->cameras && g->r->scene->cameras->prev == NULL) ?
		gtk_widget_set_sensitive(widget, false) :
		gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ButtonNextCamera"));
	(g->r->scene->cameras && g->r->scene->cameras->next == NULL) ?
		gtk_widget_set_sensitive(widget, false) :
		gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "LabelCurrentCamera"));
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras ?
							g->r->scene->cameras->name : "None");
	widget = GTK_WIDGET(gtk_builder_get_object(b, "BackgroundColorPicker"));
	color.red = g->r->scene->background_color.x / 255.0;
	color.green = g->r->scene->background_color.y / 255.0;
	color.blue = g->r->scene->background_color.z / 255.0;
	color.alpha = 1;
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(widget), &color);
	return (NULL);
}

static void	update_scene_gui(t_gtk_tools *g, GtkBuilder *b)
{
	GtkWidget	*widget;
	GdkRGBA		color;

	widget = GTK_WIDGET(gtk_builder_get_object(b, "NoteBookMenu"));
	gtk_widget_set_visible(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ButtonPreviousCamera"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ButtonNextCamera"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ButtonRender"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ResolutionXSpinButton"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), g->r->scene->res.x);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ResolutionYSpinButton"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), g->r->scene->res.y);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "RayDepthSpinButton"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), g->r->scene->ray_depth);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "AmbientLightCoeffSpinB"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), g->r->scene->ka);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "AmbientLightColorPicker"));
	color.red = g->r->scene->ambient_light_color.x / 255.0;
	color.green = g->r->scene->ambient_light_color.y / 255.0;
	color.blue = g->r->scene->ambient_light_color.z / 255.0;
	color.alpha = 1;
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(widget), &color);
}

void		scene_render_sig(t_gtk_tools *g)
{
	g->r->update.render = 1;
	g->r->update.scene = 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
}

void		*sig_update_res_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_pt2	res;

	res = g->r->scene->res;
	while (g->r->rendering)
		;
	res.x = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button));
	res.x += res.x % 4;
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button), res.x);
	g->r->scene->image_aspect_ratio = (float)res.x / (float)res.y;
	g->r->update.resolution = 2;
	(g->updating_gui) ? 0 : scene_render_sig(g);
	g->win ? gtk_widget_set_size_request(g->drawing_area, res.x, res.y) : 0;
	g->win ? gtk_window_resize(GTK_WINDOW(g->win), res.x, res.y) : 0;
	g->r->scene->res = res;
	return (NULL);
}

void		*sig_update_res_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_pt2	res;

	res = g->r->scene->res;
	while (g->r->rendering)
		;
	res.y = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button));
	res.y += res.y % 4;
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button), res.y);
	g->r->scene->image_aspect_ratio = (float)res.x / (float)res.y;
	g->r->update.resolution = 2;
	(g->updating_gui) ? 0 : scene_render_sig(g);
	g->win ? gtk_widget_set_size_request(g->drawing_area, res.x, res.y) : 0;
	g->win ? gtk_window_resize(GTK_WINDOW(g->win), res.x, res.y) : 0;
	g->r->scene->res = res;
	return (NULL);
}
