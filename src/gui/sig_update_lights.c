/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 17:02:19 by tgros             #+#    #+#             */
/*   Updated: 2017/04/17 15:29:45 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*update_grid_lights(t_gtk_tools *g) //change name
{
	GtkWidget	*widget;
	GtkWidget	*label;
	GdkRGBA		color;
	t_light		*light;

	printf("update_grid_lights\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxLights"));
	gtk_container_foreach (GTK_CONTAINER(widget), G_CALLBACK(gtk_widget_destroy), NULL);
	light = g->r->scene->lights;
	while (light)
	{
		label = gtk_label_new(light->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		light = light->next;
	}
	if (!g->r->scene->lights)
		return (NULL);
	// label = gtk_button_new_with_label("+");
	// gtk_list_box_insert(widget, label, -1);
	// g_signal_connect(label, "clicked", G_CALLBACK (sig_new_light), g);
	gtk_list_box_select_row(GTK_LIST_BOX(widget), gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), 0));
	update_lights_info_panel(g, g->r->scene->lights);
	
	gtk_widget_show_all(widget);
	return (NULL);
}

void	update_lights_info_panel(t_gtk_tools *g, t_light *light)
{
	GtkWidget	*widget;
	GdkRGBA		color;

	printf("update_lights_info_panel\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "EntryLightName"));
	gtk_entry_set_text (GTK_ENTRY(widget), light->name);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightPosX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->pos.x);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightPosY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->pos.y);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightPosZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->pos.z);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.x);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.y);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightDirZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->dir.z);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightRotX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->rot.x);
	gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightRotY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->rot.y);
	gtk_widget_set_sensitive (widget, FALSE);
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightRotZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->rot.z);
	gtk_widget_set_sensitive (widget, FALSE);
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonLightIntensity"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), light->intensity);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ColorButtonLight"));
	color.red = light->col.x / 255.0;
	color.green = light->col.y / 255.0;
	color.blue = light->col.z / 255.0;
	color.alpha = 1;
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER(widget), &color);
}

// On va devoir faire ca pour chaque evenement de modification, donc autant en faire une fonction! Il faudra probablement la 
// meme chose avec les objets si l'idee tient debout
t_light	*get_light_from_list_box(t_gtk_tools *g)
{
	t_light		*l_ptr;
	int			index;
	int			i;

	printf("get_light_from_list_box\n");
	i = -1;
	index = gtk_list_box_row_get_index(gtk_list_box_get_selected_row(GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxLights"))));
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

void	*sig_update_current_light(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g)
{
	int			index;
	int			i;
	t_light		*l_ptr;

	printf("sig_update_current_light\n");
	i = -1;
	index = gtk_list_box_row_get_index (row);
	l_ptr = g->r->scene->lights;
	while (++i != index && l_ptr)
		l_ptr = l_ptr->next;
	if (i != index || !l_ptr)
		return (NULL);
	update_lights_info_panel(g, l_ptr);
	return (NULL);
}

// UPDATE LIGHT NAME
void	*sig_update_light_name(GtkWidget *GtkEntry, t_gtk_tools *g)
{
	char		*name;
	t_light 	*light;

	printf("sig_update_light_name\n");
	light = get_selected_light(g);
	name = ft_strdup((char *)gtk_entry_get_text((struct _GtkEntry *)GtkEntry));
	free(light->name);
	light->name = name;
	update_grid_lights(g);
	return (NULL);
}

void	*sig_update_light_pos_x(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_pos_x\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->pos.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	return (NULL);
}


void	*sig_update_light_pos_y(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_pos_y\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	return (NULL);
}


void	*sig_update_light_pos_z(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_pos_z\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	return (NULL);
}

void	*sig_update_light_dir_x(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_dir_x\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	return (NULL);
}


void	*sig_update_light_dir_y(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_dir_y\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	return (NULL);
}


void	*sig_update_light_dir_z(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_dir_z\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	return (NULL);
}

void	*sig_update_light_rot_x(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->rot.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	return (NULL);
}


void	*sig_update_light_rot_y(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->rot.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	return (NULL);
}


void	*sig_update_light_rot_z(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->rot.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
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
	return (NULL);
}

void	*sig_update_light_intensity(GtkWidget *SpinButton, t_gtk_tools *g)
{
	t_light		*l_ptr;

	printf("sig_update_light_intensity\n");
	if (!(l_ptr = get_light_from_list_box(g)))
		return (NULL);
	l_ptr->intensity = gtk_spin_button_get_value(GTK_SPIN_BUTTON(SpinButton));
	return (NULL);
}