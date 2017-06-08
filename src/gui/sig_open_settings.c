/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_open_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 11:11:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 12:29:54 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include <cuda_runtime.h>

static void	create_info_string(struct cuda_device_prop props, char label[127],
					GtkBuilder *builder);

void		update_grid_settings(t_gtk_tools *g, GtkBuilder *builder)
{
	GtkWidget	*widget;

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
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder),
											"SpinButtonPhotonCountPerPass"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
									g->r->scene->photon_count_per_pass);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder),
											"SpinButtonPhotonRadius"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
									g->r->settings.photon_search_radius);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder),
											"SpinButtonPPMLightIntensity"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
									g->r->scene->ppm_light_intensity);
}

void		*sig_open_settings(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkBuilder				*builder;
	GtkWidget				*widget;
	struct cuda_device_prop	props;
	char					graphic_card_label[127];

	(void)menu_item;
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

static void	create_info_string(struct cuda_device_prop props, char label[127],
					GtkBuilder *builder)
{
	char		*tmp;
	GtkWidget	*widget;

	ft_strcat(label, props.name);
	ft_strcat(label, ": ");
	tmp = ft_itoa(props.sharedMemPerBlock / (float)(1024 * 1024));
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
