/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_lights1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 15:35:51 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_light_pos_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_light		*l_ptr;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->pos.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_pos_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_light		*l_ptr;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_pos_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_light		*l_ptr;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_color(GtkWidget *color_chooser, t_gtk_tools *g)
{
	t_light			*l_ptr;
	GdkRGBA			color;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(color_chooser), &color);
	l_ptr->col.x = color.red * 255;
	l_ptr->col.y = color.green * 255;
	l_ptr->col.z = color.blue * 255;
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_intensity(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_light		*l_ptr;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->intensity = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}
