/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 17:07:53 by tgros             #+#    #+#             */
/*   Updated: 2017/06/06 15:08:36 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_obj_lookat_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_lookat_x\n");
	obj = get_selected_object(g);
	obj->look_at.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	obj->dir = v_norm(v_sub(obj->look_at, obj->pos));
	g->updating_gui = true;
	widget = get_widget(g, "ComboBoxTextObjLookAtName");
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = get_widget(g, "SpinButtonObjectDirectionX");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);
	widget = get_widget(g, "SpinButtonObjectDirectionY");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);
	widget = get_widget(g, "SpinButtonObjectDirectionZ");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);
	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, FALSE);
	g->updating_gui = false;
	obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_lookat_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_lookat_y\n");
	obj = get_selected_object(g);
	obj->look_at.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	obj->dir = v_norm(v_sub(obj->look_at, obj->pos));
	g->updating_gui = true;
	widget = get_widget(g, "ComboBoxTextObjLookAtName");
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = get_widget(g, "SpinButtonObjectDirectionX");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);
	widget = get_widget(g, "SpinButtonObjectDirectionY");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);
	widget = get_widget(g, "SpinButtonObjectDirectionZ");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);
	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, FALSE);
	g->updating_gui = false;
	obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_lookat_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_lookat_z\n");
	obj = get_selected_object(g);
	obj->look_at.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (g->updating_gui)
		return (NULL);
	obj->dir = v_norm(v_sub(obj->look_at, obj->pos));
	g->updating_gui = true;
	widget = get_widget(g, "ComboBoxTextObjLookAtName");
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	widget = get_widget(g, "SpinButtonObjectDirectionX");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);
	widget = get_widget(g, "SpinButtonObjectDirectionY");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);
	widget = get_widget(g, "SpinButtonObjectDirectionZ");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);
	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, FALSE);
	g->updating_gui = false;
	obj_render_sig(g);
	return (NULL);
}
