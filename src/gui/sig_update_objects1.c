/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 12:12:52 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 12:18:09 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	update_objects_info_panel1(t_gtk_tools *g, t_object *obj, int type);
static void	update_objects_info_panel2(t_gtk_tools *g, t_object *obj, int type);
static void	update_objects_info_panel3(t_gtk_tools *g, t_object *obj);

void		update_objects_info_panel_bis(t_gtk_tools *g, t_object *o, int type)
{
	update_objects_info_panel1(g, o, type);
	update_objects_info_panel2(g, o, type);
	update_objects_info_panel3(g, o);
}

static void	update_objects_info_panel1(t_gtk_tools *g, t_object *obj, int type)
{
	GtkWidget	*widget;

	widget = get_widget(g, "ComboBoxObjectType");
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), obj->type - 6);
	widget = get_widget(g, "SpinButtonObjectPosX");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->pos.x);
	widget = get_widget(g, "SpinButtonObjectPosY");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->pos.y);
	widget = get_widget(g, "SpinButtonObjectPosZ");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->pos.z);
	widget = get_widget(g, "SpinButtonObjectLookAtX");
	gtk_widget_set_sensitive(widget, TRUE);
	type != T_SPHERE && !obj->parent ?
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.x) :
		gtk_widget_set_sensitive(widget, FALSE);
	widget = get_widget(g, "SpinButtonObjectLookAtY");
	gtk_widget_set_sensitive(widget, TRUE);
	type != T_SPHERE && !obj->parent ?
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.y) :
		gtk_widget_set_sensitive(widget, FALSE);
	widget = get_widget(g, "SpinButtonObjectLookAtZ");
	gtk_widget_set_sensitive(widget, TRUE);
	type != T_SPHERE && !obj->parent ?
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.z) :
		gtk_widget_set_sensitive(widget, FALSE);
}

static void	update_objects_info_panel2(t_gtk_tools *g, t_object *obj, int type)
{
	GtkWidget	*widget;

	widget = get_widget(g, "ComboBoxTextObjLookAtName");
	gtk_widget_set_sensitive(widget, TRUE);
	type != T_SPHERE ? init_obj_look_at_combo_box(widget, g) :
						gtk_widget_set_sensitive(widget, FALSE);
	widget = get_widget(g, "ComboBoxTextObjectParent");
	gtk_widget_set_sensitive(widget, TRUE);
	init_obj_parent_combo_box(widget, g);
	widget = get_widget(g, "SpinButtonObjectDirectionX");
	gtk_widget_set_sensitive(widget, TRUE);
	type != T_SPHERE ?
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x) :
		gtk_widget_set_sensitive(widget, FALSE);
	widget = get_widget(g, "SpinButtonObjectDirectionY");
	gtk_widget_set_sensitive(widget, TRUE);
	type != T_SPHERE ?
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y) :
		gtk_widget_set_sensitive(widget, FALSE);
	widget = get_widget(g, "SpinButtonObjectDirectionZ");
	gtk_widget_set_sensitive(widget, TRUE);
	type != T_SPHERE ?
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z) :
		gtk_widget_set_sensitive(widget, FALSE);
}

static void	update_objects_info_panel3(t_gtk_tools *g, t_object *obj)
{
	GtkWidget	*widget;

	widget = get_widget(g, "ButtonObjectDirNormalize");
	gtk_widget_set_sensitive(widget, FALSE);
	widget = get_widget(g, "ScaleObjectKS");
	gtk_range_set_value(GTK_RANGE(widget), obj->ks);
	widget = get_widget(g, "SpinButtonObjectSepcularExponent");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->specular_exp);
	widget = get_widget(g, "ScaleObjectKD");
	gtk_range_set_value(GTK_RANGE(widget), obj->kd);
	widget = get_widget(g, "ScaleObjectKT");
	gtk_range_set_value(GTK_RANGE(widget), obj->transparency);
	widget = get_widget(g, "SpinButtonObjectIOR");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->ior);
	widget = get_widget(g, "ScaleObjectKR");
	gtk_range_set_value(GTK_RANGE(widget), obj->reflection);
	widget = get_widget(g, "LabelObjectTexture");
	gtk_label_set_text(GTK_LABEL(widget), obj->texture_name ?
							get_file_name(obj->texture_name) : "");
}
