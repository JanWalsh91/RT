/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 17:07:49 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_obj_dir_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, TRUE);
	obj = get_selected_object(g);
	obj->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	widget = get_widget(g, "ComboBoxTextObjLookAtName");
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = get_widget(g, "SpinButtonObjectDirectionY");
	obj->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = get_widget(g, "SpinButtonObjectDirectionZ");
	obj->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	obj->dir = v_norm(obj->dir);
	obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_dir_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, TRUE);
	obj = get_selected_object(g);
	obj->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	widget = get_widget(g, "ComboBoxTextObjLookAtName");
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = get_widget(g, "SpinButtonObjectDirectionX");
	obj->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = get_widget(g, "SpinButtonObjectDirectionZ");
	obj->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	obj->dir = v_norm(obj->dir);
	obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_dir_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, TRUE);
	obj = get_selected_object(g);
	obj->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	widget = get_widget(g, "ComboBoxTextObjLookAtName");
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = get_widget(g, "SpinButtonObjectDirectionX");
	obj->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = get_widget(g, "SpinButtonObjectDirectionY");
	obj->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	obj->dir = v_norm(obj->dir);
	obj_render_sig(g);
	return (NULL);
}

void	*sig_obj_dir_normalize(GtkWidget *button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	(void)button;
	obj = get_selected_object(g);
	obj->dir = v_norm(obj->dir);
	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, FALSE);
	if (g->updating_gui)
		return (NULL);
	g->updating_gui = true;
	widget = get_widget(g, "SpinButtonObjectDirectionX");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);
	widget = get_widget(g, "SpinButtonObjectDirectionY");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);
	widget = get_widget(g, "SpinButtonObjectDirectionZ");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);
	g->updating_gui = false;
	obj_render_sig(g);
	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, FALSE);
	return (NULL);
}
