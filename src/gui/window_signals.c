/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:06:27 by tgros             #+#    #+#             */
/*   Updated: 2017/04/28 17:06:41 by tgros            ###   ########.fr       */
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

void window_destroy(GtkWidget *widget, void *ouais)
{
	gtk_widget_destroy (ouais ? GTK_WIDGET(ouais) : widget);
}

void window_destroy_esc(GtkWidget *widget, void *ouais)
{
	gtk_widget_destroy (GTK_WIDGET(ouais));
}