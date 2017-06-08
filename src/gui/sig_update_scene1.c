/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_scene1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 16:44:28 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_ambient_light_coeff(GtkWidget *spin_button, t_gtk_tools *g)
{
	g->r->scene->ka = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_udpate_ambient_light_color(GtkWidget *color_chooser,
													t_gtk_tools *g)
{
	GdkRGBA			color;
	t_vec3			ambient_col;

	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(color_chooser), &color);
	ambient_col = g->r->scene->ambient_light_color;
	ambient_col.x = color.red * 255;
	ambient_col.y = color.green * 255;
	ambient_col.z = color.blue * 255;
	g->r->scene->ambient_light_color = v_clamp(ambient_col, 0.0, 255.0);
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_next_camera(GtkWidget *button, t_gtk_tools *g)
{
	GtkWidget	*widget;

	(void)button;
	if (!g->r->scene->cameras->next)
		return (NULL);
	g->r->scene->cameras = g->r->scene->cameras->next;
	widget = get_widget(g, "LabelCurrentCamera");
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras->name);
	widget = get_widget(g, "ButtonNextCamera");
	gtk_widget_set_sensitive(widget, (bool)g->r->scene->cameras->next);
	widget = get_widget(g, "ButtonPreviousCamera");
	gtk_widget_set_sensitive(widget, (bool)g->r->scene->cameras->prev);
	update_camera_ctw(g->r->scene->cameras);
	g->r->update.cameras = 1;
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_prev_camera(GtkWidget *button, t_gtk_tools *g)
{
	GtkWidget	*widget;

	(void)button;
	if (!g->r->scene->cameras->prev)
		return (NULL);
	g->r->scene->cameras = g->r->scene->cameras->prev;
	widget = get_widget(g, "LabelCurrentCamera");
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras->name);
	widget = get_widget(g, "ButtonNextCamera");
	gtk_widget_set_sensitive(widget, (bool)g->r->scene->cameras->next);
	widget = get_widget(g, "ButtonPreviousCamera");
	gtk_widget_set_sensitive(widget, (bool)g->r->scene->cameras->prev);
	update_camera_ctw(g->r->scene->cameras);
	g->r->update.cameras = 1;
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_ray_depth(GtkWidget *spin_button, t_gtk_tools *g)
{
	g->r->scene->ray_depth = gtk_spin_button_get_value(
							GTK_SPIN_BUTTON(spin_button));
	g->r->update.render = 1;
	g->r->update.scene = 1;
	g->r->update.ray_depth = 2;
	if (g->win)
		gtk_widget_queue_draw(g->win);
	return (NULL);
}
