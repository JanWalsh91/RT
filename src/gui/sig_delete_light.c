/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_delete_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:42:52 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 21:07:22 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.cuh"

static void	set_gui_no_light_left(t_gtk_tools *g);

void		*sig_delete_light(GtkWidget *widget, t_gtk_tools *g)
{
	t_light			*light;
	GtkListBoxRow	*list_box_row;
	GtkWidget		*list_box;
	int				id;

	(void)widget;
	list_box = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxLights"));
	list_box_row = gtk_list_box_get_selected_row(GTK_LIST_BOX(list_box));
	id = gtk_list_box_row_get_index(list_box_row);
	light = get_selected_light(g);
	gtk_container_remove(GTK_CONTAINER(list_box), GTK_WIDGET(list_box_row));
	remove_light(&g->r->scene->lights, light);
	g->r->update.lights = 2;
	if (g->r->scene->lights)
	{
		gtk_list_box_select_row(GTK_LIST_BOX(list_box),
			gtk_list_box_get_row_at_index(GTK_LIST_BOX(list_box),
				id - 1 >= 0 ? id - 1 : 0));
		update_lights_info_panel(g, get_selected_light(g));
	}
	else
		set_gui_no_light_left(g);
	return (NULL);
}

static void	set_gui_no_light_left(t_gtk_tools *g)
{
	GtkWidget	*widg;

	widg = GTK_WIDGET(gtk_builder_get_object(g->builder, "ScrollWindowLight"));
	gtk_widget_set_sensitive(widg, false);
	widg = GTK_WIDGET(gtk_builder_get_object(g->builder, "ButtonDeleteLight"));
	gtk_widget_set_sensitive(widg, false);
	g->r->update.render = 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
}
