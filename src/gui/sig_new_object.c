/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_new_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:08:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/28 16:54:05 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"

void    *sig_new_object(GtkWidget *widget, t_gtk_tools *g)
{
    t_object	*obj; 
	GtkWidget	*list_box;
	int			i;

    printf("sig_new_object\n");

	if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
		return (NULL);
	ft_bzero(obj, sizeof(t_object));
	
	g->updating_gui = 1;
	obj->type = T_SPHERE;
	obj->rad = DEFAULT_RADIUS;
	obj->col = v_new(DEFAULT_COL_R, DEFAULT_COL_G, DEFAULT_COL_B);
	obj->kd = DEFAULT_KD;
	obj->ks = DEFAULT_KS;
	obj->ior = DEFAULT_IOR;
	obj->transparency = DEFAULT_TRANSPARENCY;
	obj->reflection = DEFAULT_REFLECTION;
	obj->specular_exp = DEFAULT_SPECULAR_EXP;
	obj->dir = v_new(DEFAULT_DIR_X, DEFAULT_DIR_Y, DEFAULT_DIR_Z);
	obj->height = DEFAULT_HEIGHT;
	obj->name = ft_strdup("New Object");
	obj->next = NULL;
	push_object(&(g->r->scene->objects), obj);
	g->r->update.render = 1;
	g->r->update.objects = 2;
	cuda_free(g->r, 0);
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(g->builder, "ScrollWindowObject")), true);
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(g->builder, "ButtonDeleteObject")), true);
	list_box = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxObjects"));
	gtk_list_box_insert(GTK_LIST_BOX(list_box), gtk_label_new (obj->name), -1);
	obj = g->r->scene->objects;
	i = -1;
	while (obj)
	{
		obj = obj->next;
		i++;
	}
	gtk_list_box_select_row(GTK_LIST_BOX(list_box), gtk_list_box_get_row_at_index(GTK_LIST_BOX(list_box), i));
	update_objects_info_panel(g, get_selected_object(g));
	gtk_widget_show_all(list_box);

	if (g->win)
		gtk_widget_queue_draw(g->win);
	g->updating_gui = 0;
	return (NULL);
}
