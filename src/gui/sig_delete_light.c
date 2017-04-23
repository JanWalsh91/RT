/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_delete_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:42:52 by tgros             #+#    #+#             */
/*   Updated: 2017/04/23 10:49:01 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_delete_light(GtkWidget *widget, t_gtk_tools *g)
{
    t_light			*light;
	GtkListBoxRow 	*list_box_row;
	GtkWidget		*list_box;
	int				id;

    printf("sig_delete_light\n");
	list_box = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxLights"));
	list_box_row = gtk_list_box_get_selected_row (GTK_LIST_BOX(list_box));
	id = gtk_list_box_row_get_index(list_box_row);
	light = get_selected_light(g);
	gtk_container_remove(GTK_CONTAINER(list_box), GTK_WIDGET(list_box_row));
	remove_light(&g->r->scene->lights, light);
	if (g->r->scene->lights)
	{
		gtk_list_box_select_row(GTK_LIST_BOX(list_box), gtk_list_box_get_row_at_index(GTK_LIST_BOX(list_box), id - 1 >= 0 ? id - 1 : 0));
		update_lights_info_panel(g, get_selected_light(g));
	}
	else
	{
		list_box = GTK_WIDGET(gtk_builder_get_object(g->builder, "ScrollWindowLight"));
		gtk_widget_set_sensitive(list_box, false);
		list_box = GTK_WIDGET(gtk_builder_get_object(g->builder, "ButtonDeleteLight"));
		gtk_widget_set_sensitive(list_box, false);
	}
	return (NULL);
}
