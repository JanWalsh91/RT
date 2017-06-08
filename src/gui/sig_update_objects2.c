/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 17:07:48 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_obj_name(GtkWidget *gtk_entry, t_gtk_tools *g)
{
	char		*name;
	t_object	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	name = ft_strdup((char *)gtk_entry_get_text((struct _GtkEntry *)gtk_entry));
	free(obj->name);
	obj->name = name;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
														"ListBoxObjects"));
	gtk_label_set_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(
			gtk_list_box_get_selected_row(GTK_LIST_BOX(widget))))), name);
	return (NULL);
}

void	*sig_update_obj_pos_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->pos.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_pos_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_pos_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}
