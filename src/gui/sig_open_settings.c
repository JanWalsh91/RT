/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_open_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 11:11:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 14:01:45 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include <cuda_runtime.h>

static void	create_info_string(struct cudaDeviceProp props, char label[127],
					GtkBuilder *builder);

void		update_grid_settings(t_gtk_tools *g, GtkBuilder *builder)
{
	GtkWidget	*widget;

	printf("update_grid_settings\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder),
													"SpinButtonTileSize"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
										g->r->settings.tile_size);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder),
													"ComboBoxAAType"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), g->r->scene->is_aa - 1);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder),
													"SpinButtonPhotonCount"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
												g->r->scene->photon_count);
}

void		*sig_open_settings(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkBuilder				*builder;
	GtkWidget				*widget;
	struct cudaDeviceProp	props;
	char					graphic_card_label[127];

	(void)menu_item;
	printf("sig_open_settings\n");
	ft_bzero(&graphic_card_label, 127);
	cudaGetDeviceProperties(&props, 0);
	cudaMemGetInfo(&(props.sharedMemPerBlock), NULL);
	builder = gtk_builder_new_from_file(SETTINGS_GLADE);
	gtk_builder_connect_signals(builder, g);
	widget = GTK_WIDGET(gtk_builder_get_object(builder, "window_settings"));
	gtk_window_set_transient_for(GTK_WINDOW(widget),
			GTK_WINDOW(gtk_builder_get_object(g->builder, "window_main")));
	gtk_widget_show(widget);
	g->updating_gui = 1;
	update_grid_settings(g, builder);
	g->updating_gui = 0;
	create_info_string(props, graphic_card_label, builder);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder),
												"SpinButtonTileSize"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
												g->r->settings.tile_size);
	return (NULL);
}

static void	create_info_string(struct cudaDeviceProp props, char label[127],
					GtkBuilder *builder)
{
	char		*tmp;
	GtkWidget	*widget;

	ft_strcat(label, props.name);
	ft_strcat(label, ": ");
	tmp = ft_itoa(props.sharedMemPerBlock / (float)(1024 * 1024));
	printf("tmp : [%d]\n", (int)props.sharedMemPerBlock);
	ft_strcat(label, tmp);
	free(tmp);
	ft_strcat(label, " / ");
	tmp = ft_itoa(props.totalGlobalMem / (1024 * 1024));
	ft_strcat(label, tmp);
	free(tmp);
	ft_strcat(label, " MB available");
	widget = GTK_WIDGET(gtk_builder_get_object(builder, "LabelGraphicCard"));
	gtk_label_set_text(GTK_LABEL(widget), label);
}
