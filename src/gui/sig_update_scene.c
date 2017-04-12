/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:33:12 by tgros             #+#    #+#             */
/*   Updated: 2017/04/12 13:25:57 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"


void *update_scene_panel(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GdkRGBA		color;

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

void	*sig_update_res_x(GtkWidget *SpinButton, t_gtk_tools *g)
{
	g->r->scene->res.x = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SpinButton));
	g->r->scene->image_aspect_ratio = (double)g->r->scene->res.x / (double)g->r->scene->res.y;
	return (NULL);
}

void	*sig_update_res_y(GtkWidget *SpinButton, t_gtk_tools *g)
{
	g->r->scene->res.y = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SpinButton));
	g->r->scene->image_aspect_ratio = (double)g->r->scene->res.x / (double)g->r->scene->res.y;
	return (NULL);
}

void	*sig_update_ambient_light_coeff(GtkWidget *spin_button, t_gtk_tools *g)
{
	g->r->scene->ka = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

void	*sig_udpate_ambient_light_color(GtkWidget *color_chooser, t_gtk_tools *g)
{
	GdkRGBA			color;

	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(color_chooser), &color);
	g->r->scene->ambient_light_color.x = color.red * 255;
	g->r->scene->ambient_light_color.y = color.green * 255;
	g->r->scene->ambient_light_color.z = color.blue * 255;
	return (NULL);
}

void	*sig_next_camera(GtkWidget *button, t_gtk_tools *g)
{
	GtkWidget	*widget;

	printf("sig_next_camera\n");
	if (g->r->scene->cameras->next)
		g->r->scene->cameras = g->r->scene->cameras->next;	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelCurrentCamera"));
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras->name);
	update_scene_panel(g);
	return (NULL);
}

void	*sig_prev_camera(GtkWidget *button, t_gtk_tools *g)
{
	GtkWidget	*widget;

	printf("sig_prev_camera\n");
	if (g->r->scene->cameras->prev)
		g->r->scene->cameras = g->r->scene->cameras->prev;	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelCurrentCamera"));
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras->name);
	update_scene_panel(g);
	return (NULL);
}