/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:06:27 by tgros             #+#    #+#             */
/*   Updated: 2017/05/18 15:51:54 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"

// called when window is closed
void 		on_window_main_destroy()
{
    gtk_main_quit();
}

void 		window_destroy(GtkWidget *widget, void *g)
{
	printf("window_destroy\n");
	gtk_widget_destroy (((t_gtk_tools *)g)->win ? GTK_WIDGET(((t_gtk_tools *)g)->win) : widget);
	((t_gtk_tools *)g)->win = NULL;
}

void 		window_destroy_esc(GtkWidget *widget, void *g)
{
	printf("window_destroy_esc\n");
	gtk_widget_destroy (GTK_WIDGET(g));
}

void		*sig_button_pressed_window(GtkWidget *widget, GdkEvent *event, t_gtk_tools *g)
{
	gtk_window_set_keep_above(GTK_WINDOW(gtk_builder_get_object(g->builder, "window_main")), false);
	g_signal_handlers_disconnect_by_func(GTK_WIDGET(gtk_builder_get_object(g->builder, "window_main")), sig_button_pressed_window, g);
	return (NULL);
}

gboolean	update_available_memory(gpointer data)
{
	GtkWidget	*widget;
	size_t		free_bytes;
	size_t		total_bytes;
	char		gpu_infos[127];
	char		*tmp;

	ft_bzero(&gpu_infos, 127);
	widget = GTK_WIDGET(gtk_builder_get_object(((t_gtk_tools *)data)->builder, "LabelAvailableCudaMemory"));
    cudaMemGetInfo(&free_bytes, &total_bytes);
    tmp = ft_itoa(free_bytes / (1024 * 1024));
    ft_strcat(gpu_infos, tmp);
    free(tmp);
    ft_strcat(gpu_infos, " / ");
    tmp = ft_itoa(total_bytes / (1024 * 1024));
    ft_strcat(gpu_infos, tmp);
    free(tmp);
    ft_strcat(gpu_infos, " MB available");
    gtk_label_set_text(GTK_LABEL(widget), gpu_infos);
	return (true);
}