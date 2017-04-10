/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:39:53 by tgros             #+#    #+#             */
/*   Updated: 2017/04/10 16:41:29 by jwalsh           ###   ########.fr       */
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
	printf("update_objects_panel\n");

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
	t_token		type;
	
	printf("update_objects_info_panel\n");
	type = obj->type;
	obj->dir = v_norm(obj->dir);
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
	gtk_widget_set_sensitive (widget, TRUE);
	type != T_SPHERE ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.x) :
						gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtY"));
	gtk_widget_set_sensitive (widget, TRUE);
	type != T_SPHERE ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.y) :
						gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtZ"));
	gtk_widget_set_sensitive (widget, TRUE);
	type != T_SPHERE ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.z) :
						gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ComboBoxTextObjLookAtName"));
	gtk_widget_set_sensitive (widget, TRUE);
	type != T_SPHERE ? init_obj_look_at_combo_box(widget, g) :
						gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionX"));
	gtk_widget_set_sensitive (widget, TRUE);
	type != T_SPHERE ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x) :
						gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionY"));
	gtk_widget_set_sensitive (widget, TRUE);
	type != T_SPHERE ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y) :
						gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionZ"));
	gtk_widget_set_sensitive (widget, TRUE);
	type != T_SPHERE ? gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z) :
						gtk_widget_set_sensitive (widget, FALSE);
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectRotationX"));
	gtk_widget_set_sensitive (widget, FALSE);
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectRotationY"));
	gtk_widget_set_sensitive (widget, FALSE);
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectRotationZ"));
	gtk_widget_set_sensitive (widget, FALSE);
	
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
	gtk_widget_set_sensitive (widget, TRUE);
	(type != T_SPHERE && type != T_DISK && type != T_PLANE) ?
						gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->height) :
						gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ColorButtonObject"));
	color.red = obj->col.x / 255.0;
	color.green = obj->col.y / 255.0;
	color.blue = obj->col.z / 255.0;
	color.alpha = 1;
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER(widget), &color);
}

void	init_obj_look_at_combo_box(GtkWidget *widget, t_gtk_tools *g)
{
	t_object	*obj;
	t_light		*light;
	t_camera	*camera;
	int			id;

	printf("init_obj_look_at_combo_box\n");
	id = (gtk_combo_box_get_has_entry (GTK_COMBO_BOX(widget))) ?
		gtk_combo_box_get_active (GTK_COMBO_BOX(widget)) : 0;
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(widget));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "");
	obj = g->r->scene->objects;
	while (obj)
	{
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(widget), (const gchar *)obj->name);
		obj = obj->next;
	}
	light = g->r->scene->lights;
	while (light)
	{
		if (!v_isnan(light->pos))
			gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(widget), (const gchar *)light->name);
		light = light->next;
	}
	camera = g->r->scene->cameras;
	while (camera)
	{
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(widget), (const gchar *)camera->name);
		camera = camera->next;
	}
	gtk_combo_box_set_active (GTK_COMBO_BOX(widget), id);
	gtk_widget_show_all(widget);
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
	GtkListBoxRow	*listBoxRow;
	int			id;
	int			i;
	t_object	*obj;

	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxObjects"));
	listBoxRow = gtk_list_box_get_selected_row (GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index (listBoxRow);
	i = -1;
	obj = g->r->scene->objects;
	while (++i != id && obj)
		obj = obj->next;
	return ((obj && id == i) ? obj : NULL);
}

// UPDATE OBJECT TYPE
void	*sig_update_obj_type(GtkWidget *ComboBox, t_gtk_tools *g)
{
	int			id;
	t_object 	*obj;

	printf("sig_update_obj_type\n");
	obj = get_selected_object(g);
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(ComboBox));
	obj->type = id + 6;
	// update_objects_info_panel(g, g->r->scene->objects);
	return (NULL);
}

// UPDATE OBJECT NAME
void	*sig_update_obj_name(GtkWidget *GtkEntry, t_gtk_tools *g)
{
	char		*name;
	t_object 	*obj;

	obj = get_selected_object(g);
	name = ft_strdup((char *)gtk_entry_get_text((struct _GtkEntry *)GtkEntry));
	free(obj->name);
	obj->name = name;
	return (NULL);
}

// UPDATE OBJECT POSITION
void	*sig_update_obj_pos_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->pos.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

void	*sig_update_obj_pos_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

void	*sig_update_obj_pos_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

//UNIFINISHED
// UPDATE OBJECT LOOK AT
void	*sig_update_obj_lookat_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	obj->look_at.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	obj->dir = v_norm(v_sub(obj->look_at, obj->pos));

	if (obj->dir.x == 0 && obj->dir.y == 0 && obj->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with doubles?)
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_update_obj_lookat_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	obj->look_at.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	obj->dir = v_norm(v_sub(obj->look_at, obj->pos));

	if (obj->dir.x == 0 && obj->dir.y == 0 && obj->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with doubles?)
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_update_obj_lookat_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	obj->look_at.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	obj->dir = v_norm(v_sub(obj->look_at, obj->pos));

	if (obj->dir.x == 0 && obj->dir.y == 0 && obj->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with doubles?)
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->look_at.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

// UPDATE OBJECT LOOK AT BY NAME

t_vec3		get_look_at_obj(GtkComboBox *ComboBox, t_gtk_tools *g)
{
	t_object	*obj;
	t_light		*light;
	t_camera	*camera;
	int			id;
	int			i;

	i = 0;
	id = gtk_combo_box_get_active(ComboBox);
	obj = g->r->scene->objects;
	if (i == id) //case when first entry is selected (no look at)
		return (v_new(NAN, NAN, NAN));
	while (obj && ++i != id)
		obj = obj->next;
	if (i == id)
		return (obj->pos);
	light = g->r->scene->lights;
	while (light && ++i != id)
		light = light->next;
	if (i == id)
		return (light->pos);
	camera = g->r->scene->cameras;
	while (camera && ++i != id)
		camera = camera->next;
	if (i == id)
		return (camera->pos);
	return (v_new(NAN, NAN, NAN));
}

void	*sig_update_obj_lookat_name(GtkWidget *ComboBox, t_gtk_tools *g)
{
	t_vec3 		look_at;
	t_object	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_lookat_name\n");
	obj = get_selected_object(g);
	if (v_isnan(look_at = get_look_at_obj(GTK_COMBO_BOX(ComboBox), g)))
		return (NULL); // INVALID OBJ POS
	obj->dir = v_norm(v_sub(look_at, obj->pos));
	if (obj->dir.x == 0 && obj->dir.y == 0 && obj->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with doubles?)
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), look_at.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), look_at.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectLookAtZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), look_at.z);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

// UPDATE OBJECT DIRECTION
void	*sig_update_obj_dir_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	obj->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_update_obj_dir_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	obj->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_update_obj_dir_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	obj->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_obj_dir_normalize(GtkWidget *button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	obj->dir = v_norm(obj->dir);
	printf("normalizing direction: [%f][%f][%f]\n", obj->dir.x, obj->dir.y, obj->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, FALSE);
	update_objects_info_panel(g, obj);
	return (NULL);
}
// TODO: UPDATE OBJECT ROTATION

// TODO: UPDATE OBJECT COLOR

void	*sig_update_obj_color(GtkWidget *color_chooser, t_gtk_tools *g)
{
	t_object 	*obj;
	GdkRGBA		color;

	obj = get_selected_object(g);
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (color_chooser), &color);
	obj->col.x = color.red * 255;
	obj->col.y = color.green * 255;
	obj->col.z = color.blue * 255;
	return (NULL);
}

// TOUPDATE OBJECT KS

void	*sig_update_obj_ks(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->ks = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

// TODO: UPDATE OBJECT SPEC EXP

void	*sig_update_obj_spec_exp(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->specular_exp = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

// TODO: UPDATE OBJECT KD

void	*sig_update_obj_kd(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->kd = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

// TODO: UPDATE OBJECT TRANSPARENCY

void	*sig_update_obj_kt(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->transparency = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

// TODO: UPDATE OBJECT REFRACTION K

void	*sig_update_obj_krefraction(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->refraction = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

// TODO: UPDATE OBJECT REFLECTION K

void	*sig_update_obj_kreflection(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->reflection = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

// TODO: UPDATE OBJECT RADIUS

void	*sig_update_obj_radius(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->rad = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

// TODO: UPDATE OBJECT HEIGHT

void	*sig_update_obj_height(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	obj = get_selected_object(g);
	obj->height = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}
