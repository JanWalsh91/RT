/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_delete_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:39:38 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 16:42:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.h"

static void		remove_link(t_object *obj, t_object *list);
static void		reset_indexes(t_object *list);
static void		update_object_gui(t_gtk_tools *g, int id, GtkWidget *widget);

void			*sig_delete_object(GtkWidget *button, t_gtk_tools *g)
{
	t_object		*obj;
	GtkListBoxRow	*list_box_row;
	GtkWidget		*widget;
	int				id;

	(void)button;
	printf("sig_delete_object\n");
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxObjects"));
	list_box_row = gtk_list_box_get_selected_row(GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index(list_box_row);
	obj = get_selected_object(g);
	remove_link(obj, g->r->scene->objects);
	gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(list_box_row));
	remove_object(&g->r->scene->objects, obj);
	g->r->update.objects = 2;
	update_object_gui(g, id, widget);
	g->r->update.render = 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
	return (NULL);
}

static void		update_object_gui(t_gtk_tools *g, int id, GtkWidget *widget)
{
	if (g->r->scene->objects)
	{
		gtk_list_box_select_row(GTK_LIST_BOX(widget),
			gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget),
				id - 1 >= 0 ? id - 1 : 0));
		update_objects_info_panel(g, get_selected_object(g));
	}
	else
	{
		widget = GTK_WIDGET(gtk_builder_get_object(
				g->builder, "ScrollWindowObject"));
		gtk_widget_set_sensitive(widget, false);
		widget = GTK_WIDGET(gtk_builder_get_object(
				g->builder, "ButtonDeleteObject"));
		gtk_widget_set_sensitive(widget, false);
		cuda_malloc(g->r);
	}
}

static void		remove_link(t_object *obj, t_object *list)
{
	t_object	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->parent == obj)
		{
			tmp->parent = NULL;
			tmp->parent_index = 0;
		}
		tmp = tmp->next;
	}
	reset_indexes(list);
}

static void		reset_indexes(t_object *list)
{
	t_object	*tmp;
	t_object	*find_parent;
	int			i;

	tmp = list;
	while (tmp)
	{
		if (tmp->parent)
		{
			find_parent = list;
			i = -1;
			while (find_parent && find_parent != tmp->parent)
			{
				i++;
				if (find_parent == tmp->parent)
					tmp->parent_index = i;
				find_parent = find_parent->next;
			}
		}
		tmp = tmp->next;
	}
}
