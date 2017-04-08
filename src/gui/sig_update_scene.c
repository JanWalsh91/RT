/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:33:12 by tgros             #+#    #+#             */
/*   Updated: 2017/04/08 15:37:09 by jwalsh           ###   ########.fr       */
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
	return (NULL);
}

void	*sig_update_res_x(GtkWidget *SpeedButton, t_gtk_tools *g)
{
	g->r->scene->res.x = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SpeedButton));
	g->r->scene->image_aspect_ratio = (double)g->r->scene->res.x / (double)g->r->scene->res.y;
	return (NULL);
}

void	*sig_update_res_y(GtkWidget *SpeedButton, t_gtk_tools *g)
{
	g->r->scene->res.y = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SpeedButton));
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
