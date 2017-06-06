/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects12.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 11:51:50 by tgros             #+#    #+#             */
/*   Updated: 2017/06/06 17:05:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	update_obj_type1(t_gtk_tools *g, t_object *obj);
static void	populate_combo_box(t_gtk_tools *g, GtkWidget *widget);

void		*sig_update_obj_type(GtkWidget *combo_box, t_gtk_tools *g)
{
	int			id;
	t_object	*obj;
	GtkWidget	*widget;
	int			render;

	printf("sig_update_obj_type\n");
	render = (g->updating_gui) ? 0 : 1;
	obj = get_selected_object(g);
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
	obj->type = id + 6;
	widget = get_widget(g, "SpinButtonObjectHeight");
	if (obj->type == T_CYLINDER || obj->type == T_CONE)
		gtk_widget_set_sensitive(widget, TRUE);
	else
		gtk_widget_set_sensitive(widget, FALSE);
	update_obj_type1(g, obj);
	update_objects_info_panel(g, obj);
	render ? obj_render_sig(g) : 0;
	return (NULL);
}

static void	update_obj_type1(t_gtk_tools *g, t_object *obj)
{
	GtkWidget	*widget;

	widget = get_widget(g, "SpinButtonObjectRadius");
	if (obj->type == T_DISK || obj->type == T_SPHERE ||
		obj->type == T_CYLINDER || obj->type == T_CONE ||
		obj->type == T_PARABOLOID || obj->type == T_TORUS)
		gtk_widget_set_sensitive(widget, TRUE);
	else
		gtk_widget_set_sensitive(widget, FALSE);
	widget = get_widget(g, "SpinButtonObjectRadius2");
	if (obj->type == T_TORUS)
		gtk_widget_set_sensitive(widget, TRUE);
	else
		gtk_widget_set_sensitive(widget, FALSE);
	if (obj->type == T_CONE)
		obj->angle = atan(obj->rad / obj->height);
	if (v_isnan(obj->dir))
		obj->dir = v_new(DEFAULT_DIR_X, DEFAULT_DIR_Y, DEFAULT_DIR_Z);
	if (isnan(obj->height))
		obj->height = DEFAULT_HEIGHT;
	if (g->updating_gui)
		return ;
}

void		init_obj_look_at_combo_box(GtkWidget *widget, t_gtk_tools *g)
{
	int			id;

	printf("init_obj_look_at_combo_box\n");
	if (g->updating_gui)
		return ;
	id = (gtk_combo_box_get_has_entry(GTK_COMBO_BOX(widget))) ?
		gtk_combo_box_get_active(GTK_COMBO_BOX(widget)) : 0;
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(widget));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "-");
	populate_combo_box(g, widget);
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), id);
	gtk_widget_show_all(widget);
}

static void	populate_combo_box(t_gtk_tools *g, GtkWidget *widget)
{
	t_object	*obj;
	t_light		*light;
	t_camera	*camera;

	obj = g->r->scene->objects;
	while (obj)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), obj->name);
		obj = obj->next;
	}
	light = g->r->scene->lights;
	while (light)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), light->name);
		light = light->next;
	}
	camera = g->r->scene->cameras;
	while (camera)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget),
														camera->name);
		camera = camera->next;
	}
}

void		*sig_udpate_bg_color(GtkWidget *color_chooser, t_gtk_tools *g)
{
	GdkRGBA			color;
	t_vec3			bg_color;

	printf("sig_update_bg_col\n");
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(color_chooser), &color);
	bg_color = g->r->scene->background_color;
	bg_color.x = color.red * 255;
	bg_color.y = color.green * 255;
	bg_color.z = color.blue * 255;
	g->r->scene->background_color = v_clamp(bg_color, 0.0, 255.0);
	(g->updating_gui) ? 0 : scene_render_sig(g);
	return (NULL);
}
