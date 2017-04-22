/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_delete_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:39:38 by tgros             #+#    #+#             */
/*   Updated: 2017/04/21 17:46:52 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void    *sig_delete_object(GtkWidget *button, t_gtk_tools *g)
{
    t_object		*obj;
	GtkListBoxRow 	*list_box_row;
	GtkWidget		*widget;
	int				id;

    printf("sig_delete_object\n");
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxObjects"));
	list_box_row = gtk_list_box_get_selected_row (GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index(list_box_row);
	obj = get_selected_object(g);
	gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(list_box_row));
	remove_object(&g->r->scene->objects, obj);
	if (g->r->scene->objects)
	{
		gtk_list_box_select_row(GTK_LIST_BOX(widget), gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), id - 1 >= 0 ? id - 1 : 0));
		update_objects_info_panel(g, get_selected_object(g));
	}
	else
	{
		widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ScrollWindowObject"));
		gtk_widget_set_sensitive(widget, false);
		widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ButtonDeleteObject"));
		gtk_widget_set_sensitive(widget, false);
	}
	return (NULL);
}
