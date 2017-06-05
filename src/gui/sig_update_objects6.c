/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:51:58 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 12:12:32 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_obj_ks(GtkWidget *scale, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_ks\n");
	obj = get_selected_object(g);
	obj->ks = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_spec_exp(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_spec_exp\n");
	obj = get_selected_object(g);
	obj->specular_exp = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_kd(GtkWidget *scale, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_kd\n");
	obj = get_selected_object(g);
	obj->kd = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_kt(GtkWidget *scale, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_transparency\n");
	obj = get_selected_object(g);
	obj->transparency = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_ior(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_ior\n");
	obj = get_selected_object(g);
	obj->ior = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}
