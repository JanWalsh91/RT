/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 17:07:51 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 12:12:27 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	set_look_at_sensitive(t_gtk_tools *g, bool sensitive);

void		*sig_update_current_object(GtkListBox *box, GtkListBoxRow *row,
														t_gtk_tools *g)
{
	int			index;
	int			i;
	t_object	*o_ptr;

	(void)box;
	printf("sig_update_current_object\n");
	i = -1;
	index = gtk_list_box_row_get_index(row);
	o_ptr = g->r->scene->objects;
	while (++i != index && o_ptr)
		o_ptr = o_ptr->next;
	if (i != index || !o_ptr)
		return (NULL);
	update_objects_info_panel(g, o_ptr);
	return (NULL);
}

void		*sig_update_object_parent(GtkWidget *combo_box, t_gtk_tools *g)
{
	int			id;
	t_object	*obj;
	t_object	*current_obj;
	int			i;

	printf("update parent\n");
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
	current_obj = get_selected_object(g);
	i = 0;
	obj = g->r->scene->objects;
	if (i == id)
	{
		current_obj->parent_index = 0;
		current_obj->parent = NULL;
		set_look_at_sensitive(g, true);
	}
	while (obj && ++i != id)
		obj = obj->next;
	if (i == id && obj != current_obj)
	{
		current_obj->parent_index = i;
		current_obj->parent = obj;
		set_look_at_sensitive(g, false);
	}
	return (NULL);
}

static void	set_look_at_sensitive(t_gtk_tools *g, bool sensitive)
{
	GtkWidget	*widget;

	widget = get_widget(g, "SpinButtonObjectLookAtX");
	gtk_widget_set_sensitive(widget, sensitive);
	widget = get_widget(g, "SpinButtonObjectLookAtY");
	gtk_widget_set_sensitive(widget, sensitive);
	widget = get_widget(g, "SpinButtonObjectLookAtZ");
	gtk_widget_set_sensitive(widget, sensitive);
}

t_object	*get_selected_object(t_gtk_tools *g)
{
	GtkWidget		*widget;
	GtkListBoxRow	*list_box_row;
	int				id;
	int				i;
	t_object		*obj;

	printf("get_selected_object: ");
	widget = get_widget(g, "ListBoxObjects");
	if (!widget)
		return (NULL);
	list_box_row = gtk_list_box_get_selected_row(GTK_LIST_BOX(widget));
	if (!list_box_row)
		return (NULL);
	id = gtk_list_box_row_get_index(list_box_row);
	i = -1;
	obj = g->r->scene->objects;
	while (++i != id && obj)
		obj = obj->next;
	return ((obj && id == i) ? obj : NULL);
}

void		*sig_update_obj_color(GtkWidget *color_chooser, t_gtk_tools *g)
{
	t_object	*obj;
	GdkRGBA		color;

	printf("sig_update_obj_color\n");
	obj = get_selected_object(g);
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(color_chooser), &color);
	obj->col.x = color.red * 255;
	obj->col.y = color.green * 255;
	obj->col.z = color.blue * 255;
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}
