/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_new_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:08:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 20:58:45 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.cuh"

static int	set_obj_default_values(t_gtk_tools *g, t_object **obj);
static void	select_new_object(t_gtk_tools *g, t_object *obj, GtkWidget *list);

void		*sig_new_object(GtkWidget *widget, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*list;

	(void)widget;
	if (set_obj_default_values(g, &obj) == -1)
		return (NULL);
	g->r->update.render = 1;
	g->r->update.objects = 2;
	cuda_free(g->r, 0);
	gtk_widget_set_sensitive(get_widget(g, "ScrollWindowObject"), true);
	gtk_widget_set_sensitive(get_widget(g, "ButtonDeleteObject"), true);
	gtk_widget_set_sensitive(get_widget(g, "ButtonRender"), true);
	list = get_widget(g, "ListBoxObjects");
	gtk_list_box_insert(GTK_LIST_BOX(list), gtk_label_new(obj->name), -1);
	select_new_object(g, obj, list);
	update_objects_info_panel(g, get_selected_object(g));
	gtk_widget_show_all(list);
	if (g->win)
		gtk_widget_queue_draw(g->win);
	g->updating_gui = 0;
	return (NULL);
}

static void	select_new_object(t_gtk_tools *g, t_object *obj, GtkWidget *list)
{
	int	i;

	obj = g->r->scene->objects;
	i = 0;
	while (obj && ++i)
		obj = obj->next;
	gtk_list_box_select_row(GTK_LIST_BOX(list),
		gtk_list_box_get_row_at_index(GTK_LIST_BOX(list), i - 1));
}

static int	set_obj_default_values(t_gtk_tools *g, t_object **obj)
{
	if (!(*obj = (t_object *)ft_memalloc(sizeof(t_object))))
		return (-1);
	ft_bzero(*obj, sizeof(t_object));
	g->updating_gui = 1;
	(*obj)->type = T_SPHERE;
	(*obj)->rad = DEFAULT_RADIUS;
	(*obj)->col = v_new(DEFAULT_COL_R, DEFAULT_COL_G, DEFAULT_COL_B);
	(*obj)->kd = DEFAULT_KD;
	(*obj)->ks = DEFAULT_KS;
	(*obj)->ior = DEFAULT_IOR;
	(*obj)->transparency = DEFAULT_TRANSPARENCY;
	(*obj)->reflection = DEFAULT_REFLECTION;
	(*obj)->specular_exp = DEFAULT_SPECULAR_EXP;
	(*obj)->dir = v_new(DEFAULT_DIR_X, DEFAULT_DIR_Y, DEFAULT_DIR_Z);
	(*obj)->height = DEFAULT_HEIGHT;
	(*obj)->name = ft_strdup("New Object");
	(*obj)->next = NULL;
	push_object(&(g->r->scene->objects), *obj);
	return (0);
}
