/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 17:02:19 by tgros             #+#    #+#             */
/*   Updated: 2017/04/07 17:09:06 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*update_lights_panel(t_gtk_tools *g) //change name
{
	GtkWidget	*widget;
	GtkWidget	*label;
	GdkRGBA		color;
	t_light		*light;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxLights"));

	light = g->r->scenes->lights;
	while (light)
	{
		label = gtk_label_new(light->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		light = light->next;
	}
	if (!g->r->scenes->lights)
		return (NULL);
	
	gtk_list_box_select_row(GTK_LIST_BOX(widget), gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), 0));
	update_lights_info_panel(g, g->r->scenes->lights);

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
	
	gtk_widget_show_all(widget);
	return (NULL);
}

void	update_lights_info_panel(t_gtk_tools *g, t_light *light)
{
	GtkWidget	*widget;
	GdkRGBA		color;
}

