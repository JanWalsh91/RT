/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_settings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 11:23:26 by tgros             #+#    #+#             */
/*   Updated: 2017/05/13 11:26:41 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_tile_size(GtkWidget *spin_button, t_gtk_tools *g)
{
	printf("sig_update_tile_size\n");
	while (g->r->rendering); // find something. Kill the current rendering?
	g->r->settings.tile_size = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}