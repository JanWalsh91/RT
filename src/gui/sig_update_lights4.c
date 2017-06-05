/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_lights4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 16:13:23 by tgros             #+#    #+#             */
/*   Updated: 2017/06/04 16:14:27 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

t_light		*get_light_from_list_box(t_gtk_tools *g)
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
	GtkWidget		*widget;
	GtkListBoxRow	*list_box_row;
	int				id;
	int				i;
	t_light			*light;

	printf("get_selected_light\n");
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxLights"));
	list_box_row = gtk_list_box_get_selected_row(GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index(list_box_row);
	i = -1;
	light = g->r->scene->lights;
	while (++i != id && light)
		light = light->next;
	return ((light && id == i) ? light : NULL);
}

void		light_render_sig(t_gtk_tools *g)
{
	g->r->update.render = 1;
	g->r->update.lights = g->r->update.lights > 1 ? 2 : 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
}
