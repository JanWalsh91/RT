/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects7.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:54:16 by tgros             #+#    #+#             */
/*   Updated: 2017/06/07 20:24:27 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_obj_kreflection(GtkWidget *scale, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_kreflection\n");
	obj = get_selected_object(g);
	obj->reflection = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_radius(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_radius\n");
	obj = get_selected_object(g);
	obj->rad = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (obj->type == T_CONE)
		obj->angle = atan(obj->rad / obj->height);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_height(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_height\n");
	obj = get_selected_object(g);
	obj->height = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (obj->type == T_CONE)
		obj->angle = atan(obj->rad / obj->height);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_texture_negative(GtkWidget *toggle_button,
										gboolean state, t_gtk_tools *g)
{
	t_object	*obj;

	(void)toggle_button;
	printf("sig_update_obj_texture_negative\n");
	obj = get_selected_object(g);
	obj->texture_color_style = state;
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}
