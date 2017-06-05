/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_signals1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 17:00:43 by tgros             #+#    #+#             */
/*   Updated: 2017/06/04 17:00:53 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_generated_texture_quit(GtkWidget *combo_box, t_gtk_tools *g)
{
	(void)combo_box;
	gtk_widget_destroy(GTK_WIDGET(gtk_builder_get_object(g->builder_texture,
													"window_generate")));
	return (NULL);
}
