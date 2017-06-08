/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 17:02:19 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static int	set_gui_no_light(t_gtk_tools *g);
static void	update_light_pos_dir(t_gtk_tools *g, t_light *light);

void		*update_grid_lights(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GtkWidget	*label;
	t_light		*light;
	GtkBuilder	*b;

	b = GTK_BUILDER(g->builder);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ListBoxLights"));
	gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)G_CALLBACK(
												gtk_widget_destroy), NULL);
	light = g->r->scene->lights;
	while (light)
	{
		label = gtk_label_new(light->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		light = light->next;
	}
	if (set_gui_no_light(g))
		return (NULL);
	gtk_list_box_select_row(GTK_LIST_BOX(widget),
		gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), 0));
	update_lights_info_panel(g, g->r->scene->lights);
	gtk_widget_show_all(widget);
	return (NULL);
}

static int	set_gui_no_light(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GtkBuilder	*b;

	if (g->r->scene->lights)
		return (0);
	b = GTK_BUILDER(g->builder);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ScrollWindowLight"));
	gtk_widget_set_sensitive(widget, FALSE);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ButtonDeleteLight"));
	gtk_widget_set_sensitive(widget, FALSE);
	return (1);
}

void		update_lights_info_panel(t_gtk_tools *g, t_light *light)
{
	GtkWidget	*widget;
	GdkRGBA		color;
	GtkBuilder	*b;

	b = GTK_BUILDER(g->builder);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ComboBoxLightType"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), !v_isnan(light->dir));
	widget = GTK_WIDGET(gtk_builder_get_object(b, "EntryLightName"));
	gtk_entry_set_text(GTK_ENTRY(widget), light->name);
	update_light_pos_dir(g, light);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightIntensity"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->intensity);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonKFlare"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->kflare);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ColorButtonLight"));
	color.red = light->col.x / 255.0;
	color.green = light->col.y / 255.0;
	color.blue = light->col.z / 255.0;
	color.alpha = 1;
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(widget), &color);
}

static void	update_light_pos_dir(t_gtk_tools *g, t_light *light)
{
	GtkWidget	*widget;
	GtkBuilder	*b;

	b = GTK_BUILDER(g->builder);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightPosX"));
	v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
		light->pos.x) : gtk_widget_set_sensitive(widget, false);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightPosY"));
	v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
		light->pos.y) : gtk_widget_set_sensitive(widget, false);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightPosZ"));
	v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
		light->pos.z) : gtk_widget_set_sensitive(widget, false);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightDirX"));
	!v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
		light->dir.x) : gtk_widget_set_sensitive(widget, false);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightDirY"));
	!v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
		light->dir.y) : gtk_widget_set_sensitive(widget, false);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightDirZ"));
	!v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
		light->dir.z) : gtk_widget_set_sensitive(widget, false);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, !v_isnan(light->dir));
}
