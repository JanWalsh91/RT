/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects11.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 11:34:52 by tgros             #+#    #+#             */
/*   Updated: 2017/06/06 15:29:18 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static t_vec3	get_obj_pos(t_gtk_tools *g, t_object *obj, int id);

t_vec3			get_look_at_obj(GtkComboBox *combo_box, t_gtk_tools *g)
{
	t_object	*obj;
	int			id;
	int			i;

	printf("get_look_at_obj\n");
	i = 0;
	id = gtk_combo_box_get_active(combo_box);
	obj = g->r->scene->objects;
	if (i == id)
		return (v_new(NAN, NAN, NAN));
	return (get_obj_pos(g, obj, id));
}

static t_vec3	get_obj_pos(t_gtk_tools *g, t_object *obj, int id)
{
	int			i;
	t_light		*light;
	t_camera	*camera;

	i = 0;
	printf("Cherche pour l'id %d\n", id);
	while (obj && ++i != id)
		obj = obj->next;
	if (i == id)
		return (obj->pos);
	light = g->r->scene->lights;
	while (light && ++i != id)
		light = light->next;
	printf("Apres la loop, i : %d\n", i);
	if (i == id)
		return (light->pos);
	camera = g->r->scene->cameras;
	while (camera && ++i != id)
		camera = camera->next;
	if (i == id)
		return (camera->pos);
	return (v_new(NAN, NAN, NAN));
}

void			obj_render_sig(t_gtk_tools *g)
{
	g->r->update.render = 1;
	g->r->update.objects = g->r->update.objects > 1 ? 2 : 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
}

void			init_obj_parent_combo_box(GtkWidget *widget, t_gtk_tools *g)
{
	t_object	*obj;

	printf("init_obj_parent_combo_box\n");
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(widget));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "None");
	obj = g->r->scene->objects;
	while (obj)
	{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), obj->name);
		obj = obj->next;
	}
	obj = get_selected_object(g);
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), obj->parent_index);
	gtk_widget_show_all(widget);
}
