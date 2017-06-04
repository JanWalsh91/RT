/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_lights3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 15:40:44 by tgros             #+#    #+#             */
/*   Updated: 2017/06/04 15:59:36 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_current_light(GtkListBox *box, GtkListBoxRow *row,
														t_gtk_tools *g)
{
	int			index;
	int			i;
	t_light		*l_ptr;

	(void)box;
	printf("sig_update_current_light\n");
	i = -1;
	index = gtk_list_box_row_get_index(row);
	l_ptr = g->r->scene->lights;
	while (++i != index && l_ptr)
		l_ptr = l_ptr->next;
	if (i != index || !l_ptr)
		return (NULL);
	g->updating_gui = 1;
	update_lights_info_panel(g, l_ptr);
	g->updating_gui = 0;
	return (NULL);
}

void	switch_light_type(t_gtk_tools *g, bool is_pos)
{
	GtkWidget	*widget;
	GtkBuilder	*b;

	b = GTK_BUILDER(g->builder);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightPosX"));
	gtk_widget_set_sensitive(widget, is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightPosY"));
	gtk_widget_set_sensitive(widget, is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightPosZ"));
	gtk_widget_set_sensitive(widget, is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightDirX"));
	gtk_widget_set_sensitive(widget, !is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightDirY"));
	gtk_widget_set_sensitive(widget, !is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonLightDirZ"));
	gtk_widget_set_sensitive(widget, !is_pos);
}

void	*sig_update_light_type(GtkWidget *combo_box, t_gtk_tools *g)
{
	int			id;
	t_light		*light;

	printf("sig_update_light_type\n");
	light = get_selected_light(g);
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
	if (id == 0)
	{
		light->dir = v_new(NAN, NAN, NAN);
		light->pos = v_isnan(light->pos) ?
			v_new(DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z) :
			v_new(light->pos.x, light->pos.y, light->pos.z);
		switch_light_type(g, 1);
	}
	else if (id == 1)
	{
		light->pos = v_new(NAN, NAN, NAN);
		light->dir = v_isnan(light->dir) ?
			v_new(DEFAULT_DIR_X, -DEFAULT_DIR_Y, DEFAULT_DIR_Z) :
			v_new(light->dir.x, light->dir.y, light->dir.z);
		switch_light_type(g, 0);
	}
	update_lights_info_panel(g, light);
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_name(GtkWidget *gtk_entry, t_gtk_tools *g)
{
	char		*name;
	t_light		*light;
	GtkWidget	*widget;

	printf("sig_update_light_name\n");
	light = get_selected_light(g);
	name = ft_strdup((char *)gtk_entry_get_text((struct _GtkEntry *)gtk_entry));
	free(light->name);
	light->name = name;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
														"ListBoxLights"));
	gtk_label_set_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(
			gtk_list_box_get_selected_row(GTK_LIST_BOX(widget))))), name);
	return (NULL);
}

void	*sig_update_light_kflare(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_light		*l_ptr;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->kflare = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}
