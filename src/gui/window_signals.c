/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:06:27 by tgros             #+#    #+#             */
/*   Updated: 2017/04/29 12:28:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

void window_destroy(GtkWidget *widget, void *g)
{
		printf("window_destroy\n");
	gtk_widget_destroy (((t_gtk_tools *)g)->win ? GTK_WIDGET(((t_gtk_tools *)g)->win) : widget);
	((t_gtk_tools *)g)->win = NULL;
}

void window_destroy_esc(GtkWidget *widget, void *g)
{
		printf("window_destroy_esc\n");
	gtk_widget_destroy (GTK_WIDGET(g));
}