/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_scene3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 16:46:48 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:16:36 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_is_aa(GtkWidget *check_box, t_gtk_tools *g)
{
	printf("sig_update_is_aa\n");
	g->r->scene->is_aa = gtk_toggle_button_get_active(
		GTK_TOGGLE_BUTTON(check_box)) + 1;
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_is_anaglyph(GtkWidget *check_box, t_gtk_tools *g)
{
	printf("sig_update_is_anaglyph\n");
	g->r->scene->is_3d = gtk_toggle_button_get_active(
		GTK_TOGGLE_BUTTON(check_box));
	if (g->r->scene->is_3d)
		g->r->update.anaglyph = 2;
	else
	{
		g->r->scene->cameras->filter = F_NONE;
		g->r->update.cameras = 1;
	}
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_is_raytracing(GtkWidget *check_box, t_gtk_tools *g)
{
	printf("sig_update_is_raytracing\n");
	g->r->scene->is_raytracing = gtk_toggle_button_get_active(
		GTK_TOGGLE_BUTTON(check_box));
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}

void	*sig_update_is_cartoon(GtkWidget *check_box, t_gtk_tools *g)
{
	printf("sig_update_is_raytracing\n");
	g->r->scene->is_cartoon_effect = gtk_toggle_button_get_active(
		GTK_TOGGLE_BUTTON(check_box));
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}
