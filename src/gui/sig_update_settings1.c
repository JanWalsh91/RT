/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_settings1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 13:09:16 by tgros             #+#    #+#             */
/*   Updated: 2017/06/07 13:19:58 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_photon_count_per_pass(GtkWidget *spin_button, t_gtk_tools *g)
{
	printf("sig_update_photon_count_per_pass\n");
	g->r->scene->photon_count_per_pass =
		gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : settings_render_sig(g);
	return (NULL);
}

void	*sig_update_photon_radius(GtkWidget *spin_button, t_gtk_tools *g)
{
	printf("sig_update_photon_radius\n");
	g->r->settings.photon_search_radius =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : settings_render_sig(g);
	return (NULL);
}
