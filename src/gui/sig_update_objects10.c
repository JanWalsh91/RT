/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects10.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 11:28:15 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 12:12:41 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	update_gui_lookat_name(t_gtk_tools *g, t_vec3 look_at,
														t_object *obj);

void		*sig_update_obj_lookat_name(GtkWidget *combo_box, t_gtk_tools *g)
{
	t_vec3		look_at;
	t_object	*obj;

	printf("sig_update_obj_lookat_name\n");
	obj = get_selected_object(g);
	if (v_isnan(look_at = get_look_at_obj(GTK_COMBO_BOX(combo_box), g)))
		return (NULL);
	obj->dir = v_norm(v_sub(look_at, obj->pos));
	if (g->updating_gui)
		return (NULL);
	g->updating_gui = true;
	update_gui_lookat_name(g, look_at, obj);
	g->updating_gui = false;
	obj_render_sig(g);
	return (NULL);
}

static void	update_gui_lookat_name(t_gtk_tools *g, t_vec3 look_at,
														t_object *obj)
{
	GtkWidget	*widget;

	widget = get_widget(g, "SpinButtonObjectLookAtX");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), look_at.x);
	widget = get_widget(g, "SpinButtonObjectLookAtY");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), look_at.y);
	widget = get_widget(g, "SpinButtonObjectLookAtZ");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), look_at.z);
	widget = get_widget(g, "SpinButtonObjectDirectionX");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);
	widget = get_widget(g, "SpinButtonObjectDirectionY");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);
	widget = get_widget(g, "SpinButtonObjectDirectionZ");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);
	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, FALSE);
}

void		*sig_uptate_obj_texture_translate_x(GtkWidget *spin_button,
														t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_texture_translate\n");
	obj = get_selected_object(g);
	obj->texture_translate.x =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void		*sig_uptate_obj_texture_translate_y(GtkWidget *spin_button,
														t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_texture_translate\n");
	obj = get_selected_object(g);
	obj->texture_translate.y =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}
