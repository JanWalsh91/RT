/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:39:53 by tgros             #+#    #+#             */
/*   Updated: 2017/06/06 14:57:40 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.h"
#include <cuda_runtime.h>

static void	update_objects_info_panel3(t_gtk_tools *g, t_object *obj);
static void	update_objects_info_panel4(t_gtk_tools *g);
static void	update_objects_info_panel5(t_gtk_tools *g, t_object *obj, int type);

void		*populate_list_box_objects(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GtkWidget	*label;
	t_object	*obj;

	printf("populate_list_box_objects\n");
	obj = g->r->scene->objects;
	widget = get_widget(g, "ListBoxObjects");
	while (obj)
	{
		label = gtk_label_new(obj->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		obj = obj->next;
	}
	if (!g->r->scene->objects)
	{
		widget = get_widget(g, "ScrollWindowObject");
		gtk_widget_set_sensitive(widget, false);
		widget = get_widget(g, "ButtonDeleteObject");
		gtk_widget_set_sensitive(widget, false);
		return (NULL);
	}
	gtk_list_box_select_row(GTK_LIST_BOX(widget),
		gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), 0));
	update_objects_info_panel(g, g->r->scene->objects);
	gtk_widget_show_all(widget);
	return (NULL);
}

void		update_objects_info_panel(t_gtk_tools *g, t_object *obj)
{
	GtkWidget	*widget;
	GdkRGBA		color;
	t_token		type;

	printf("update_objects_info_panel\n");
	g->updating_gui = true;
	type = obj->type;
	obj->dir = v_norm(obj->dir);
	widget = get_widget(g, "EntryObjectName");
	gtk_entry_set_text(GTK_ENTRY(widget), obj->name);
	update_objects_info_panel_bis(g, obj, type);
	if (obj->texture || obj->normal_map)
		update_objects_info_panel3(g, obj);
	else
		update_objects_info_panel4(g);
	update_objects_info_panel5(g, obj, type);
	widget = get_widget(g, "ColorButtonObject");
	color.red = obj->col.x / 255.0;
	color.green = obj->col.y / 255.0;
	color.blue = obj->col.z / 255.0;
	color.alpha = 1;
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(widget), &color);
	g->updating_gui = false;
}

static void	update_objects_info_panel3(t_gtk_tools *g, t_object *obj)
{
	GtkWidget	*widget;

	widget = get_widget(g, "SpinButtonObjectTextureX");
	gtk_widget_set_sensitive(widget, true);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
									obj->texture_ratio.x);
	widget = get_widget(g, "SpinButtonObjectTextureY");
	gtk_widget_set_sensitive(widget, true);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
									obj->texture_ratio.y);
	widget = get_widget(g, "SpinButtonObjectTextureTranslateX");
	gtk_widget_set_sensitive(widget, true);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
								obj->texture_translate.x);
	widget = get_widget(g, "SpinButtonObjectTextureTranslateY");
	gtk_widget_set_sensitive(widget, true);
	if (obj->texture)
	{
		widget = get_widget(g, "ComboBoxGeneratedTexture");
		gtk_widget_set_sensitive(widget, false);
		widget = get_widget(g, "FileChooserTexture");
		gtk_widget_set_sensitive(widget, false);
	}
}

static void	update_objects_info_panel4(t_gtk_tools *g)
{
	GtkWidget	*widget;

	widget = get_widget(g, "SpinButtonObjectTextureX");
	gtk_widget_set_sensitive(widget, false);
	widget = get_widget(g, "SpinButtonObjectTextureY");
	gtk_widget_set_sensitive(widget, false);
	widget = get_widget(g, "SpinButtonObjectTextureTranslateX");
	gtk_widget_set_sensitive(widget, false);
	widget = get_widget(g, "SpinButtonObjectTextureTranslateY");
	gtk_widget_set_sensitive(widget, false);
	widget = get_widget(g, "ComboBoxGeneratedTexture");
	gtk_widget_set_sensitive(widget, true);
	widget = get_widget(g, "FileChooserTexture");
	gtk_widget_set_sensitive(widget, true);
}

static void	update_objects_info_panel5(t_gtk_tools *g, t_object *obj, int type)
{
	GtkWidget	*widget;

	widget = get_widget(g, "LabelObjectNormalMap");
	gtk_label_set_text(GTK_LABEL(widget), obj->normal_map_name ?
						get_file_name(obj->normal_map_name) : "");
	widget = get_widget(g, "SpinButtonObjectRadius");
	gtk_widget_set_sensitive(widget, true);
	(obj->type == T_CYLINDER || obj->type == T_CONE ||
		obj->type == T_SPHERE || obj->type == T_DISK ||
		obj->type == T_TORUS || obj->type == T_PARABOLOID) ?
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->rad) :
		gtk_widget_set_sensitive(widget, false);
	widget = get_widget(g, "SpinButtonObjectRadius2");
	gtk_widget_set_sensitive(widget, true);
	(obj->type == T_TORUS) ? gtk_spin_button_set_value(
			GTK_SPIN_BUTTON(widget), obj->rad_torus) :
			gtk_widget_set_sensitive(widget, false);
	widget = get_widget(g, "SpinButtonObjectHeight");
	gtk_widget_set_sensitive(widget, true);
	(type != T_SPHERE && type != T_DISK && type != T_PLANE) ?
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->height) :
		gtk_widget_set_sensitive(widget, false);
}
