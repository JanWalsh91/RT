/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_lights2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 15:37:02 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_light_dir_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_light		*l_ptr;
	GtkWidget	*widget;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
	{
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
													"SpinButtonLightDirY"));
		l_ptr->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
													"SpinButtonLightDirZ"));
		l_ptr->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		l_ptr->dir = v_norm(l_ptr->dir);
	}
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, true);
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_dir_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_light		*l_ptr;
	GtkWidget	*widget;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
	{
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
													"SpinButtonLightDirX"));
		l_ptr->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
													"SpinButtonLightDirZ"));
		l_ptr->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		l_ptr->dir = v_norm(l_ptr->dir);
	}
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, true);
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_dir_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_light		*l_ptr;
	GtkWidget	*widget;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
	{
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
													"SpinButtonLightDirX"));
		l_ptr->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
													"SpinButtonLightDirY"));
		l_ptr->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		l_ptr->dir = v_norm(l_ptr->dir);
	}
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, true);
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_light_dir_normalize(GtkWidget *button, t_gtk_tools *g)
{
	t_light		*light;
	GtkWidget	*widget;
	GtkBuilder	*b;

	(void)button;
	b = GTK_BUILDER(g->builder);
	light = get_selected_light(g);
	light->dir = v_norm(light->dir);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, FALSE);
	if (g->updating_gui)
		return (NULL);
	g->updating_gui = true;
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightDirX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightDirY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightDirZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.z);
	g->updating_gui = false;
	light_render_sig(g);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, FALSE);
	return (NULL);
}
