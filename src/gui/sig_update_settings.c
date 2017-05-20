/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_settings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 11:23:26 by tgros             #+#    #+#             */
/*   Updated: 2017/05/13 16:23:46 by tgros            ###   ########.fr       */
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

void	*sig_update_aa(GtkWidget *combo_box, t_gtk_tools *g)
{
	printf("sig_update_aa");
	g->r->scene->is_aa = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box)) + 1;
	g->r->update.render = 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
	return (NULL);
}

void	*sig_update_font_size(GtkWidget *combo_box, t_gtk_tools *g)
{
	int	id;
	GtkStyleContext *context;

	printf("sig_update_font_size");
	context = gtk_widget_get_style_context(GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")));
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
	if (id == 0)
	{
		if (gtk_style_context_has_class(context, "bigfont"))
			gtk_style_context_remove_class(context, "bigfont");
		gtk_style_context_add_class(context, "smallfont");
	}
	else if (id == 1)
	{
		if (gtk_style_context_has_class(context, "bigfont"))
			gtk_style_context_remove_class(context, "bigfont");
		if (gtk_style_context_has_class(context, "smallfont"))
			gtk_style_context_remove_class(context, "smallfont");
	}
	else if (id == 2)
	{
		if (gtk_style_context_has_class(context, "smallfont"))
			gtk_style_context_remove_class(context, "smallfont");
		gtk_style_context_add_class(context, "bigfont");
	}
	return (NULL);
}