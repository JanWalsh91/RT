/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_open_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 11:11:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/13 11:54:59 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include <cuda_runtime.h>

void    *update_grid_settings(t_gtk_tools *g, GtkBuilder *builder)
{
	GtkWidget	*widget;

	printf("update_grid_settings\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder), "SpinButtonTileSize"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), g->r->settings.tile_size);
	return (NULL);
}

void    *sig_open_settings(GtkWidget *menu_item, t_gtk_tools *g)
{
    printf("sig_open_settings\n");
    GtkBuilder              *builder;
    GtkWidget               *widget;
    struct cudaDeviceProp   props;
    char                    graphic_card_label[127];
    char                    *tmp;
    size_t                  free_byte;
    size_t                  total_byte;

    ft_bzero(&graphic_card_label, 127);
    cudaMemGetInfo(&free_byte, &total_byte);
    cudaGetDeviceProperties(&props, 0);
    builder = gtk_builder_new_from_file("Settings_glade.glade");
    gtk_builder_connect_signals(builder, g);
    widget = GTK_WIDGET(gtk_builder_get_object(builder, "window_settings"));
    gtk_widget_show(widget);
    update_grid_settings(g, builder);
    widget = GTK_WIDGET(gtk_builder_get_object(builder, "LabelGraphicCard"));
    ft_strcat(graphic_card_label, props.name);
    ft_strcat(graphic_card_label, ": ");
    tmp = ft_itoa(free_byte / (1024 * 1024));
    ft_strcat(graphic_card_label, tmp);
    free(tmp);
    ft_strcat(graphic_card_label, " / ");
    tmp = ft_itoa(props.totalGlobalMem / (1024 * 1024));
    ft_strcat(graphic_card_label, tmp);
    free(tmp);
    ft_strcat(graphic_card_label, " MB available");
    gtk_label_set_text(GTK_LABEL(widget), graphic_card_label);
    return (NULL);
}
