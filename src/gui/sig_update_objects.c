/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:39:53 by tgros             #+#    #+#             */
/*   Updated: 2017/05/16 16:47:18 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.h"

int		cudaFreeHost(void *ptr);


void	*populate_list_box_objects(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GtkWidget	*label;
	GdkRGBA		color;
	t_object	*obj;
	printf("populate_list_box_objects\n");

	if (!g->r->scene->objects)
		return (NULL);
	obj = g->r->scene->objects;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxObjects"));
	while (obj)
	{
		label = gtk_label_new (obj->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		obj = obj->next; 
	}
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

	// to change when adding textures to spheres....
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
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ScaleObjectKS"));
	gtk_range_set_value(GTK_RANGE(widget), obj->ks);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectSepcularExponent"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->specular_exp);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ScaleObjectKD"));
	gtk_range_set_value(GTK_RANGE(widget), obj->kd);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ScaleObjectKT"));
	gtk_range_set_value(GTK_RANGE(widget), obj->transparency);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectIOR"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->ior);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ScaleObjectKR"));
	gtk_range_set_value(GTK_RANGE(widget), obj->reflection);

	// widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "FileChooserTexture"));
	// if (gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget)))
		// gtk_file_chooser_unselect_filename(GTK_FILE_CHOOSER(widget), gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget)));
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelObjectTexture"));
	gtk_label_set_text(GTK_LABEL(widget), obj->texture_name ? get_file_name(obj->texture_name) : "");
	if (obj->texture)
	{
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureX"));
		gtk_widget_set_sensitive(widget, true);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->texture_ratio.x);

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureY"));
		gtk_widget_set_sensitive(widget, true);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->texture_ratio.y);
		
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateX"));
		gtk_widget_set_sensitive(widget, true);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->texture_translate.x);
		
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateY"));
		gtk_widget_set_sensitive(widget, true);

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ComboBoxGeneratedTexture"));
		gtk_widget_set_sensitive(widget, false);

		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->texture_translate.x);
	}
	else
	{

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureX"));
		gtk_widget_set_sensitive(widget, false);

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureY"));
		gtk_widget_set_sensitive(widget, false);
		
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateX"));
		gtk_widget_set_sensitive(widget, false);
		
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateY"));
		gtk_widget_set_sensitive(widget, false);
		
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ComboBoxGeneratedTexture"));
		gtk_widget_set_sensitive(widget, true);
	}
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelObjectNormalMap"));
	gtk_label_set_text(GTK_LABEL(widget), obj->normal_map_name ? get_file_name(obj->normal_map_name) : "");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectRadius"));
	gtk_widget_set_sensitive(widget, TRUE);
	(obj->type == T_CYLINDER || obj->type == T_CONE || obj->type == T_SPHERE || obj->type == T_DISK || obj->type == T_PARABOLOID) ?
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), obj->rad) :
		gtk_widget_set_sensitive(widget, FALSE);

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

	printf("sig_update_current_object\n");
	i = -1;
	index = gtk_list_box_row_get_index (row);
	o_ptr = g->r->scene->objects;
	while (++i != index && o_ptr)
		o_ptr = o_ptr->next;
	if (i != index || !o_ptr)
		return (NULL);
	g->updating_gui = 1;
	update_objects_info_panel(g, o_ptr);
	g->updating_gui = 0;
	return (NULL);
}

t_object	*get_selected_object(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GtkListBoxRow	*listBoxRow;
	int			id;
	int			i;
	t_object	*obj;

	printf("get_selected_object\n");
	// C(1)
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxObjects"));
	listBoxRow = gtk_list_box_get_selected_row (GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index (listBoxRow);
	i = -1;
	obj = g->r->scene->objects;
	while (++i != id && obj)
		obj = obj->next;
	return ((obj && id == i) ? obj : NULL);
}

void	obj_render_sig(t_gtk_tools *g)
{
	GtkWidget	*widget;

	g->r->update.render = 1;
	g->r->update.objects = g->r->update.objects > 1 ? 2 : 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
}

// UPDATE OBJECT TYPE
void	*sig_update_obj_type(GtkWidget *ComboBox, t_gtk_tools *g)
{
	int			id;
	t_object 	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_type\n");
	obj = get_selected_object(g);
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(ComboBox));
	obj->type = id + 6;
	// update_objects_info_panel(g, g->r->scene->objects);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectHeight"));
	if (obj->type == T_CYLINDER || obj->type == T_CONE)
		gtk_widget_set_sensitive(widget, TRUE);
	else
		gtk_widget_set_sensitive(widget, FALSE);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectRadius"));
	if (obj->type == T_DISK || obj->type == T_SPHERE || obj->type == T_CYLINDER || obj->type == T_CONE || obj->type == T_PARABOLOID)
		gtk_widget_set_sensitive(widget, TRUE);
	else
		gtk_widget_set_sensitive(widget, FALSE);
	if (obj->type == T_CONE)
		obj->angle = atan(obj->rad / obj->height);
	if ((obj->type == T_PLANE || obj->type == T_DISK) && v_isnan(obj->dir))
		obj->dir = v_new(DEFAULT_DIR_X, DEFAULT_DIR_Y, DEFAULT_DIR_Z);
	update_objects_info_panel(g, obj);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// UPDATE OBJECT NAME
void	*sig_update_obj_name(GtkWidget *GtkEntry, t_gtk_tools *g)
{
	char		*name;
	t_object 	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_name\n");
	obj = get_selected_object(g);
	name = ft_strdup((char *)gtk_entry_get_text((struct _GtkEntry *)GtkEntry));	
	free(obj->name);
	obj->name = name;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxObjects"));
	gtk_label_set_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(gtk_list_box_get_selected_row(GTK_LIST_BOX(widget))))), name);
	return (NULL);
}

// UPDATE OBJECT POSITION
void	*sig_update_obj_pos_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_pos_x\n");
	obj = get_selected_object(g);
	obj->pos.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_pos_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_pos_y\n");
	obj = get_selected_object(g);
	obj->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_pos_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_pos_z\n");
	obj = get_selected_object(g);
	obj->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

//UNIFINISHED
// UPDATE OBJECT LOOK AT
void	*sig_update_obj_lookat_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_lookat_x\n");
	obj = get_selected_object(g);
	obj->look_at.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	obj->dir = v_norm(v_sub(obj->look_at, obj->pos));

	if (obj->dir.x == 0 && obj->dir.y == 0 && obj->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with floats?)
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
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_lookat_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

printf("sig_update_obj_lookat_y\n");
	obj = get_selected_object(g);
	obj->look_at.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	obj->dir = v_norm(v_sub(obj->look_at, obj->pos));

	if (obj->dir.x == 0 && obj->dir.y == 0 && obj->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with floats?)
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
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_lookat_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_lookat_z\n");
	obj = get_selected_object(g);
	obj->look_at.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	obj->dir = v_norm(v_sub(obj->look_at, obj->pos));

	if (obj->dir.x == 0 && obj->dir.y == 0 && obj->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with floats?)
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
	(g->updating_gui) ? 0 : obj_render_sig(g);
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

	printf("get_look_at_obj\n");
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
		return (NULL); // NUll direction is invalid (comparision works with floats?)
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
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// UPDATE OBJECT DIRECTION
void	*sig_update_obj_dir_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_dir_x\n");
	obj = get_selected_object(g);
	obj->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_dir_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_dir_y\n");
	obj = get_selected_object(g);
	obj->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_dir_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	printf("sig_update_obj_dir_z\n");
	obj = get_selected_object(g);
	obj->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_obj_dir_normalize(GtkWidget *button, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	obj->dir = v_norm(obj->dir);
	printf("normalizing obj direction: [%f][%f][%f]\n", obj->dir.x, obj->dir.y, obj->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	gtk_widget_set_sensitive (widget, FALSE);
	update_objects_info_panel(g, obj);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}
// TODO: UPDATE OBJECT ROTATION

// TODO: UPDATE OBJECT COLOR

void	*sig_update_obj_color(GtkWidget *color_chooser, t_gtk_tools *g)
{
	t_object 	*obj;
	GdkRGBA		color;

	printf("sig_update_obj_color\n");
	obj = get_selected_object(g);
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (color_chooser), &color);
	obj->col.x = color.red * 255;
	obj->col.y = color.green * 255;
	obj->col.z = color.blue * 255;
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// TOUPDATE OBJECT KS

void	*sig_update_obj_ks(GtkWidget *scale, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_ks\n");
	obj = get_selected_object(g);
	obj->ks = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// TODO: UPDATE OBJECT SPEC EXP

void	*sig_update_obj_spec_exp(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_spec_exp\n");
	obj = get_selected_object(g);
	obj->specular_exp = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// TODO: UPDATE OBJECT KD

void	*sig_update_obj_kd(GtkWidget *scale, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_kd\n");
	obj = get_selected_object(g);
	obj->kd = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// TODO: UPDATE OBJECT TRANSPARENCY

void	*sig_update_obj_kt(GtkWidget *scale, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_transparency\n");
	obj = get_selected_object(g);
	obj->transparency = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// TODO: UPDATE OBJECT REFRACTION K

void	*sig_update_obj_ior(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_ior\n");
	obj = get_selected_object(g);
	obj->ior = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// TODO: UPDATE OBJECT REFLECTION K

void	*sig_update_obj_kreflection(GtkWidget *scale, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_kreflection\n");
	obj = get_selected_object(g);
	obj->reflection = gtk_range_get_value(GTK_RANGE(scale));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// when user change texture
void	*sig_update_obj_texture(GtkWidget *file_chooser, t_gtk_tools *g)
{
	t_object 	*obj;
	t_object	*tmp;
	GtkWidget	*widget;

	printf("sig_update_obj_texture\n");
	
	obj = get_selected_object(g);
	if (obj->texture) // set to NULL?
		cudaFreeHost(obj->texture);
	if (gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)) == NULL)
		return (NULL);
	free(obj->texture_name);
	obj->texture_name = ft_strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)));
	tmp = is_texture_loaded(g->r->scene->objects, obj, obj->texture_name, obj->texture_dim);
	if (!tmp)
	{
		if (!(obj->texture = read_bmp(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)), &obj->texture_dim)))
			exit (0); // Hehe TODO! ><
	}
	else
	{
		obj->texture = tmp->texture;
		obj->texture_dim = tmp->texture_dim;
		printf("===\nRecyclage\n===\n");
	}
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelObjectTexture"));
	gtk_label_set_text(GTK_LABEL(widget), get_file_name(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser))));
	

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureX"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureY"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateX"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateY"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ComboBoxGeneratedTexture"));
	gtk_widget_set_sensitive(widget, false);

	// update_objects_info_panel(g, obj);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_delete_obj_texture(GtkWidget *button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;
	t_object	*tmp;

	obj = get_selected_object(g);
	if (obj->texture)
	{
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "FileChooserTexture"));
		// gtk_file_chooser_unselect_filename(GTK_FILE_CHOOSER(widget), gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget)));
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelObjectTexture"));
		gtk_label_set_text(GTK_LABEL(widget), "");
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ComboBoxGeneratedTexture"));
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
		gtk_widget_set_sensitive(widget, true);
		tmp = g->r->scene->objects;
		while (tmp)
		{
			if (tmp != obj)
			{
				if (tmp->texture == obj->texture)
				{
					free(tmp->texture_name);
					tmp->texture_name = 0;
					ft_bzero(&tmp->texture_dim, sizeof(t_pt2));
					ft_bzero(&tmp->texture_ratio, sizeof(t_pt2));
					ft_bzero(&tmp->texture_translate, sizeof(t_pt2));
					tmp->texture = NULL;
				}
			}
			tmp = tmp->next;
		}
		cudaFreeHost(obj->texture);
		obj->texture = NULL;
		free(obj->texture_name);
		obj->texture_name = NULL;
		update_objects_info_panel(g, obj);
		(g->updating_gui) ? 0 : obj_render_sig(g);
	}
	return (NULL);
}
void	*sig_delete_obj_normal_map(GtkWidget *button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	if (obj->normal_map)
	{
		cudaFreeHost(obj->normal_map);
		obj->normal_map = NULL;
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "FileChooserNormalMap"));
		// gtk_file_chooser_unselect_filename(GTK_FILE_CHOOSER(widget), gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget)));
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelObjectNormalMap"));
		gtk_label_set_text(GTK_LABEL(widget), "");
		free(obj->normal_map_name);
		obj->normal_map_name = NULL;
		update_objects_info_panel(g, obj);
		(g->updating_gui) ? 0 : obj_render_sig(g);
	}
	return (NULL);
}

void	*sig_update_obj_normal_map(GtkWidget *file_chooser, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	obj = get_selected_object(g);
	if (obj->normal_map) // set to NULL?
		cudaFreeHost(obj->normal_map);
	if (gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)) == NULL)
		return (NULL);
	if (!(obj->normal_map = read_bmp(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)), &obj->normal_map_dim))) // check dim diff
		exit (0); // Hehe TODO! ><
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelObjectNormalMap"));
	gtk_label_set_text(GTK_LABEL(widget), get_file_name(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser))));
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureX"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureY"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateX"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateY"));
	gtk_widget_set_sensitive(widget, true);

	// t_pt2 dim = obj->normal_map_dim;
	// printf("Normal map dim: %d, %d\n", dim.x, dim.y);
	// obj->normal_map_dim = obj->texture_dim;

	obj->texture_dim = obj->normal_map_dim;

	printf("text dim: %d, %d, text ratio : %d, %d \n", obj->texture_dim.x, obj->texture_dim.y, obj->texture_ratio.x, obj->texture_ratio.y);

	// if existe deja ?
	free(obj->normal_map_name);
	obj->normal_map_name = ft_strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)));

	// Only sensitive if texture loaded
	/*
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureX"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureY"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateX"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonObjectTextureTranslateY"));
	gtk_widget_set_sensitive(widget, true);
	*/
	
	// update_objects_info_panel(g, obj);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_uptate_obj_texture_ratio_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_texture_ratio\n");
	obj = get_selected_object(g);
	obj->texture_ratio.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	obj->texture_ratio.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_uptate_obj_texture_ratio_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;
	
	printf("sig_update_obj_texture_ratio\n");
	obj = get_selected_object(g);
	obj->texture_ratio.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}


void	*sig_uptate_obj_texture_translate_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_texture_translate\n");
	obj = get_selected_object(g);
	obj->texture_translate.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_uptate_obj_texture_translate_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_texture_translate\n");
	obj = get_selected_object(g);
	obj->texture_translate.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// TODO: UPDATE OBJECT RADIUS

void	*sig_update_obj_radius(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_radius\n");
	obj = get_selected_object(g);
	obj->rad = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (obj->type == T_CONE)
		obj->angle = atan(obj->rad / obj->height);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

// TODO: UPDATE OBJECT HEIGHT

void	*sig_update_obj_height(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_height\n");
	obj = get_selected_object(g);
	obj->height = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	if (obj->type == T_CONE)
		obj->angle = atan(obj->rad / obj->height);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void	*sig_update_obj_texture_negative(GtkWidget *toggle_button, gboolean state, t_gtk_tools *g)
{
	t_object 	*obj;

	printf("sig_update_obj_texture_negative\n");
	obj = get_selected_object(g);
	obj->texture_color_style = state;
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}
