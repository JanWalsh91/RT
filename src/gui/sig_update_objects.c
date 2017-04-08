/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:39:53 by tgros             #+#    #+#             */
/*   Updated: 2017/04/08 16:53:51 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"


void	*update_objects_panel(t_gtk_tools *g) //change name
{
	GtkWidget	*widget;
	GtkWidget	*label;
	GdkRGBA		color;
	t_object	*obj;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxObjects"));

	obj = g->r->scene->objects;
	while (obj)
	{
		label = gtk_label_new(obj->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		obj = obj->next;
	}
	if (!g->r->scene->objects)
		return (NULL);
	gtk_list_box_select_row(GTK_LIST_BOX(widget), gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), 0));
	update_objects_info_panel(g, g->r->scene->objects);
	
	gtk_widget_show_all(widget);
	return (NULL);
}

void	update_objects_info_panel(t_gtk_tools *g, t_object *obj)
{
	GtkWidget	*widget;
	GdkRGBA		color;
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "EntryObjectName"));	
	gtk_entry_set_text (GTK_ENTRY(widget), obj->name);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ComboBoxObjectType"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), obj->type - 6);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectPosX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->pos.x);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectPosY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->pos.y);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectPosZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->pos.z);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.x);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.y);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.z);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectKS"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->ks);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectSepcularExponent"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->specular_exp);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectKS"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->ks);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectKD"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->kd);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectKT"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->transparency);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectKRefraction"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->refraction);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectKReflection"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->reflection);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectRadius"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->rad);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectHeight"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->height);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ColorButtonObject"));
	color.red = obj->col.x / 255.0;
	color.green = obj->col.y / 255.0;
	color.blue = obj->col.z / 255.0;
	color.alpha = 1;
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER(widget), &color);
}

void	*sig_update_current_object(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g)
{
	int			 index;
	int			i;
	t_object	*o_ptr;

	i = -1;
	index = gtk_list_box_row_get_index (row);
	o_ptr = g->r->scene->objects;
	while (++i != index && o_ptr)
		o_ptr = o_ptr->next;
	if (i != index || !o_ptr)
		return (NULL);
	update_objects_info_panel(g, o_ptr);
	return (NULL);
}

t_object	*get_selected_object(t_gtk_tools *g)
{
	GtkWidget	*widget;
	int			id;
	int			i;
	t_object	*obj;

	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxObjects"));
	widget = GTK_WIDGET(gtk_list_box_get_selected_row (GTK_LIST_BOX(widget)));
	id = gtk_list_box_row_get_index (GTK_LIST_BOX_ROW(widget));
	i = -1;
	obj = g->r->scene->objects;
	while (++i != id && obj)
		obj = obj->next;
	return ((obj && id == i) ? obj : NULL);
}

void	*sig_update_obj_type(GtkWidget *ComboBox, t_gtk_tools *g)
{
	int			id;
	t_object 	*obj;

	obj = get_selected_object(g);
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(ComboBox));
	obj->type = id + 6;
	printf("udpate object [%s] to type: [%i]\n", obj->name, obj->type);
	return (NULL);
}

void	*sig_update_obj_name(GtkWidget *GtkEntry, t_gtk_tools *g)
{
	char		*name;
	t_object 	*obj;

	obj = get_selected_object(g);
	name = ft_strdup(gtk_entry_get_text((struct _GtkEntry *)GtkEntry));
	free(obj->name);
	printf("update object name from [%s] ", obj->name);
	obj->name = name;
	printf("to [%s].\n", obj->name);
	return (NULL);
}

void	*sig_update_obj_pos_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->pos.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	printf("udpate object [%s]'s pos.x: [%f]\n", obj->name, obj->pos.x);
	return (NULL);
}

void	*sig_update_obj_pos_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	printf("udpate object [%s]'s pos.y: [%f]\n", obj->name, obj->pos.y);
	return (NULL);
}

void	*sig_update_obj_pos_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	printf("udpate object [%s]'s pos.z: [%f]\n", obj->name, obj->pos.z);
	return (NULL);
}

// void	*sig_update_obj_lookat_x(GtkWidget *spin_button, t_gtk_tools *g)
// {
// 	t_object 	*obj;

// 	obj = get_selected_object(g);
// 	obj->look_at.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
// 	printf("udpate object [%s]'s pos.x: [%f]\n", obj->name, obj->pos.x);
// 	return (NULL);
// }

// void	*sig_update_obj_lookat_y(GtkWidget *spin_button, t_gtk_tools *g)
// {
// 	t_object 	*obj;

// 	obj = get_selected_object(g);
// 	obj->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
// 	printf("udpate object [%s]'s pos.y: [%f]\n", obj->name, obj->pos.y);
// 	return (NULL);
// }

// void	*sig_update_obj_lookat_z(GtkWidget *spin_button, t_gtk_tools *g)
// {
// 	t_object 	*obj;

// 	obj = get_selected_object(g);
// 	obj->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
// 	printf("udpate object [%s]'s pos.z: [%f]\n", obj->name, obj->pos.z);
// 	return (NULL);
// }

// void	*sig_update_obj_lookat_name(GtkWidget *ComboBox, t_gtk_tools *g)
// {
// 	int			id;
// 	t_object 	*look_at_obj;
// 	t

// 	look_at_obj = get_selected_object(g);

// 	id = gtk_combo_box_get_active(GTK_COMBO_BOX(ComboBox));
// 	obj->type = id + 6;
// 	printf("udpate object [%s] to type: [%i]\n", obj->name, obj->type);
// 	return (NULL);
// }