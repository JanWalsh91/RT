/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:39:53 by tgros             #+#    #+#             */
/*   Updated: 2017/04/06 18:52:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"


void *update_objects_panel(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GtkWidget	*label;
	GdkRGBA		color;
	t_object	*obj;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ObjectListBox"));
	obj = g->r->scenes->objects;
	while (obj)
	{
		printf("%s\n", obj->name);
		label = gtk_label_new(obj->name);
		gtk_list_box_prepend(GTK_LIST_BOX(widget), label);
		obj = obj->next;
	}	
	
	
	// gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), g->r->scenes->res.x);
	// widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ResolutionYSpinButton"));
	// gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), g->r->scenes->res.y);
	// widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "RayDepthSpinButton"));
	// gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), g->r->scenes->ray_depth);
	// widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "AmbientLightCoeffSpinButton"));
	// gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), g->r->scenes->ka);
	// widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "AmbientLightColorPicker"));
	// color.red = g->r->scenes->ambient_light_color.x / 255.0;
	// color.green = g->r->scenes->ambient_light_color.y / 255.0;
	// color.blue = g->r->scenes->ambient_light_color.z / 255.0;
	// color.alpha = 1;
	// gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER(widget), &color);
	return (NULL);
}