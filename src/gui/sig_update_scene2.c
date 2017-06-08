/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_scene2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 16:45:18 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_is_shadow(GtkWidget *check_box, t_gtk_tools *g)
{
	g->r->scene->is_shadow = gtk_toggle_button_get_active(
								GTK_TOGGLE_BUTTON(check_box));
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_is_diffuse(GtkWidget *check_box, t_gtk_tools *g)
{
	GtkWidget	*widget;

	g->r->scene->is_diffuse = gtk_toggle_button_get_active(
									GTK_TOGGLE_BUTTON(check_box));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"IsShadowCheckBox"));
	gtk_widget_set_sensitive(widget, g->r->scene->is_diffuse);
	if (!g->r->scene->is_diffuse)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), false);
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_is_specular(GtkWidget *check_box, t_gtk_tools *g)
{
	g->r->scene->is_specular = gtk_toggle_button_get_active(
									GTK_TOGGLE_BUTTON(check_box));
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_is_fresnel(GtkWidget *check_box, t_gtk_tools *g)
{
	g->r->scene->is_fresnel = gtk_toggle_button_get_active(
									GTK_TOGGLE_BUTTON(check_box));
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_is_photon_mapping(GtkWidget *check_box, t_gtk_tools *g)
{
	g->r->scene->is_photon_mapping = gtk_toggle_button_get_active(
									GTK_TOGGLE_BUTTON(check_box));
	if (g->r->scene->is_photon_mapping)
		g->r->update.photon_map = 2;
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}
