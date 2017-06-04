/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 17:02:19 by tgros             #+#    #+#             */
/*   Updated: 2017/06/03 17:21:58 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*update_grid_lights(t_gtk_tools *g) //change name
{
	GtkWidget	*widget;
	GtkWidget	*label;
	t_light		*light;

	printf("update_grid_lights\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxLights"));
	gtk_container_foreach (GTK_CONTAINER(widget), (GtkCallback)G_CALLBACK(gtk_widget_destroy), NULL);
	light = g->r->scene->lights;
	while (light)
	{
		printf("foudn lights\n");
		label = gtk_label_new(light->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		light = light->next;
	}
	if (!g->r->scene->lights)
	{
		printf("no lights found\n");
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ScrollWindowLight"));
		gtk_widget_set_sensitive (widget, FALSE);
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonDeleteLight"));
		gtk_widget_set_sensitive (widget, FALSE);
		return (NULL);
	}
	gtk_list_box_select_row(GTK_LIST_BOX(widget), gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), 0));
	update_lights_info_panel(g, g->r->scene->lights);
	
	gtk_widget_show_all(widget);
	return (NULL);
}

void	switch_light_type(t_gtk_tools *g, bool is_pos)
{
	GtkWidget	*widget;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightPosX"));
	gtk_widget_set_sensitive(widget, is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightPosY"));
	gtk_widget_set_sensitive(widget, is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightPosZ"));
	gtk_widget_set_sensitive(widget, is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirX"));
	gtk_widget_set_sensitive(widget, !is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirY"));
	gtk_widget_set_sensitive(widget, !is_pos);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirZ"));
	gtk_widget_set_sensitive(widget, !is_pos);
}

void	update_lights_info_panel(t_gtk_tools *g, t_light *light)
{
	GtkWidget	*widget;
	GdkRGBA		color;

	printf("update_lights_info_panel\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ComboBoxLightType"));
	if (v_isnan(light->dir))
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
	else
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 1);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "EntryLightName"));
	gtk_entry_set_text (GTK_ENTRY(widget), light->name);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightPosX"));
	v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->pos.x) :
		gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightPosY"));
	v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->pos.y) :
		gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightPosZ"));
	v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->pos.z) :
		gtk_widget_set_sensitive (widget, FALSE); 

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirX"));
	!v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.x) :
		gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirY"));
	!v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.y) :
		gtk_widget_set_sensitive (widget, FALSE);
 
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirZ"));
	!v_isnan(light->dir) ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.z) :
		gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, !v_isnan(light->dir));

	printf("adding light intensty\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightIntensity"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->intensity);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonKFlare"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->kflare);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ColorButtonLight"));
	color.red = light->col.x / 255.0;
	color.green = light->col.y / 255.0;
	color.blue = light->col.z / 255.0;
	color.alpha = 1;
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER(widget), &color);
}

t_light	*get_light_from_list_box(t_gtk_tools *g)
{
	t_light		*l_ptr;
	int			index;
	int			i;

	printf("get_light_from_list_box\n");
	i = -1;
	index = gtk_list_box_row_get_index(gtk_list_box_get_selected_row(
		GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(g->builder),
												"ListBoxLights"))));
	l_ptr = g->r->scene->lights;
	while (++i != index && l_ptr)
		l_ptr = l_ptr->next;
	if (i != index || !l_ptr)
		return (NULL);
	else
		return (l_ptr);
}

t_light		*get_selected_light(t_gtk_tools *g)
{
	GtkWidget	    *widget;
	GtkListBoxRow	*listBoxRow;
	int			    id;
	int			    i;
	t_light		    *light;

	printf("get_selected_light\n");
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxLights"));
	listBoxRow = gtk_list_box_get_selected_row (GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index (listBoxRow);
	i = -1;
	light = g->r->scene->lights;
	while (++i != id && light)
		light = light->next;
	return ((light && id == i) ? light : NULL);
}

void	light_render_sig(t_gtk_tools *g)
{
	g->r->update.render = 1;
	g->r->update.lights = g->r->update.lights > 1 ? 2 : 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
}

void	*sig_update_current_light(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g)
{
	int			index;
	int			i;
	t_light		*l_ptr;

	(void)box;
	printf("sig_update_current_light\n");
	i = -1;
	index = gtk_list_box_row_get_index (row);
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

void	*sig_update_light_type(GtkWidget *combo_box, t_gtk_tools *g)
{
	int			id;
	t_light 	*light;

	printf("sig_update_light_type\n");
	light = get_selected_light(g);
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
	printf("type : %d\n", id);
	if (id == 0)
	{
		light->dir = v_new(NAN, NAN, NAN);
		if (v_isnan(light->pos))
			light->pos = v_new(DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
		else	
			light->pos = v_new(light->pos.x, light->pos.y, light->pos.z);
		switch_light_type(g, 1);
	}
	else if (id == 1)
	{
		light->pos = v_new(NAN, NAN, NAN);
		if (v_isnan(light->dir))
			light->dir = v_new(DEFAULT_DIR_X, -DEFAULT_DIR_Y, DEFAULT_DIR_Z);
		else
			light->dir = v_new(light->dir.x, light->dir.y, light->dir.z);
		switch_light_type(g, 0);
	}
	update_lights_info_panel(g, light);
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_name(GtkWidget *GtkEntry, t_gtk_tools *g)
{
	char		*name;
	t_light 	*light;
	GtkWidget	*widget;

	printf("sig_update_light_name\n");
	light = get_selected_light(g);
	name = ft_strdup((char *)gtk_entry_get_text((struct _GtkEntry *)GtkEntry));
	free(light->name);
	light->name = name;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxLights"));
	gtk_label_set_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(gtk_list_box_get_selected_row(GTK_LIST_BOX(widget))))), name);

	return (NULL);
}

void	*sig_update_light_pos_x(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_pos_x\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->pos.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_pos_y(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_pos_y\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}


void	*sig_update_light_pos_z(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_pos_z\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_dir_x(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;
	GtkWidget	*widget;

	printf("sig_update_light_dir_x\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	if (g->updating_gui)
	{
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirY"));
		l_ptr->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirZ"));
		l_ptr->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		l_ptr->dir = v_norm(l_ptr->dir);
	}
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, true);
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}


void	*sig_update_light_dir_y(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;
	GtkWidget	*widget;

	printf("sig_update_light_dir_y\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	if (g->updating_gui)
	{
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirX"));
		l_ptr->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirZ"));
		l_ptr->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		l_ptr->dir = v_norm(l_ptr->dir);
	}
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, true);
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}


void	*sig_update_light_dir_z(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;
	GtkWidget	*widget;
	
	printf("sig_update_light_dir_z\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	if (g->updating_gui)
	{
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirX"));
		l_ptr->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirY"));
		l_ptr->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
		l_ptr->dir = v_norm(l_ptr->dir);
	}
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, true);
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_light_dir_normalize(GtkWidget *button, t_gtk_tools *g)
{
	t_light 	*light;
	GtkWidget	*widget;

	(void)button;
	printf("sig_light_dir_normalize\n");
	light = get_selected_light(g);
	light->dir = v_norm(light->dir);
	printf("normalizing light direction: [%f][%f][%f]\n", light->dir.x, light->dir.y, light->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonLightDirNormalize"));
	gtk_widget_set_sensitive(widget, FALSE);
	if (g->updating_gui)
		return (NULL);
	g->updating_gui = true;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.z);
	g->updating_gui = false;
	light_render_sig(g);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonLightDirNormalize"));
	gtk_widget_set_sensitive (widget, FALSE);
	return (NULL);
}


void	*sig_update_light_color(GtkWidget *color_chooser, t_gtk_tools *g)
{
	t_light			*l_ptr;
	GdkRGBA			color;

	printf("sig_update_light_color\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(color_chooser), &color);
	l_ptr->col.x = color.red * 255;
	l_ptr->col.y = color.green * 255;
	l_ptr->col.z = color.blue * 255;
	(g->updating_gui) ? 0 : light_render_sig(g);
	return (NULL);
}

void	*sig_update_light_intensity(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_intensity\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->intensity = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	(g->updating_gui) ? 0 : light_render_sig(g);
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