/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:51:58 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_obj_ks(GtkWidget *scale, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->ks = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_spec_exp(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->specular_exp = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_kd(GtkWidget *scale, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->kd = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_kt(GtkWidget *scale, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->transparency = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_ior(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->ior = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}
