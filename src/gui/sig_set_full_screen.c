/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_set_full_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 12:40:45 by tgros             #+#    #+#             */
/*   Updated: 2017/06/03 16:54:35 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_set_fullscreen(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkWidget		*widget;
	GdkRectangle	res;

	(void)menu_item;
	printf("sig_set_full_screen");
	if (!g->win)
		return (NULL);
	gdk_monitor_get_geometry(gdk_display_get_monitor(gdk_display_get_default(),
																	0), &res);
	g->r->scene->res.x = res.width;
	g->r->scene->res.y = res.height;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"ResolutionXSpinButton"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), g->r->scene->res.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"ResolutionYSpinButton"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), g->r->scene->res.y);
	gtk_window_fullscreen(GTK_WINDOW(g->win));
	return (NULL);
}
