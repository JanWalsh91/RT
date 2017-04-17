/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_cameras.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 14:41:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/17 16:57:29 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*update_grid_cameras(t_gtk_tools *g) //change name
{
	GtkWidget	*widget;
	GtkWidget	*label;
	GdkRGBA		color;
	t_camera    *camera;

    printf("update_grid_cameras\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxCameras"));
	gtk_container_foreach (GTK_CONTAINER(widget), G_CALLBACK(gtk_widget_destroy), NULL);
	camera = get_first_camera(g);
	while (camera)
	{  
		label = gtk_label_new(camera->name);
		gtk_list_box_insert(GTK_LIST_BOX(widget), label, -1);
		camera = camera->next;
	}
	if (!g->r->scene->cameras)
		return (NULL);
	gtk_list_box_select_row(GTK_LIST_BOX(widget), gtk_list_box_get_row_at_index(GTK_LIST_BOX(widget), 0));
	update_cameras_info_panel(g, get_first_camera(g));
	gtk_widget_show_all(widget);
	return (NULL);
}

void	update_cameras_info_panel(t_gtk_tools *g, t_camera *camera)
{
	GtkWidget	*widget;

    printf("update_cameras_info_panel\n");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "EntryCameraName"));
	gtk_entry_set_text (GTK_ENTRY(widget), camera->name);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraPosX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->pos.x);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraPosY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->pos.y);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraPosZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->pos.z);

    widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraLookAtX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->look_at.x);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraLookAtY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->look_at.y);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraLookAtZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->look_at.z);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ComboBoxTextCamLookAtName"));
	gtk_widget_set_sensitive (widget, TRUE);
	init_cam_look_at_combo_box(widget, g);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->dir.x);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->dir.y);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->dir.z);

    widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive (widget, FALSE);
    
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraRotationX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->rot.x);
	gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraRotationY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->rot.y);
	gtk_widget_set_sensitive (widget, FALSE);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraRotationZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->rot.z);
	gtk_widget_set_sensitive (widget, FALSE);
	
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraFov"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), camera->fov);
}

void	init_cam_look_at_combo_box(GtkWidget *widget, t_gtk_tools *g)
{
	t_object	*obj;
	t_light		*light;
	t_camera	*camera;
	int			id;

	printf("init_cam_look_at_combo_box\n");
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
	camera = get_first_camera(g);
	while (camera)
	{
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(widget), (const gchar *)camera->name);
		camera = camera->next;
	}
	gtk_combo_box_set_active (GTK_COMBO_BOX(widget), id);
	gtk_widget_show_all(widget);
}

t_camera		*get_first_camera(t_gtk_tools *g)
{
	t_camera	*cam;

	cam = g->r->scene->cameras;
	while (cam->prev)
		cam = cam->prev;
	return (cam);
}

void	*sig_update_current_cam(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g)
{
	int			 index;
	int			i;
	t_camera	*c_ptr;

	printf("sig_update_current_cam\n");
	i = -1;
	index = gtk_list_box_row_get_index (row);
	c_ptr = get_first_camera(g);
	while (++i != index && c_ptr)
		c_ptr = c_ptr->next;
	if (i != index || !c_ptr)
		return (NULL);
	update_cameras_info_panel(g, c_ptr);
	return (NULL);
}

t_camera	*get_selected_camera(t_gtk_tools *g)
{
	GtkWidget	    *widget;
	GtkListBoxRow	*listBoxRow;
	int			    id;
	int			    i;
	t_camera	    *cam;

	printf("get_selected_camera\n");
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ListBoxCameras"));
	listBoxRow = gtk_list_box_get_selected_row (GTK_LIST_BOX(widget));
	id = gtk_list_box_row_get_index (listBoxRow);
	i = -1;
	cam = get_first_camera(g);
	while (++i != id && cam)
		cam = cam->next;
	// printf("end of get_selected_camera. id: [%i] i: [%i]\n", id, i);
	return ((cam && id == i) ? cam : NULL);
}

// UPDATE CAMERA NAME
void	*sig_update_cam_name(GtkWidget *GtkEntry, t_gtk_tools *g)
{
	GtkWidget	*widget;
	char		*name;
	t_camera 	*cam;

	printf("sig_update_cam_name\n");
	cam = get_selected_camera(g);
	name = ft_strdup((char *)gtk_entry_get_text((struct _GtkEntry *)GtkEntry));
	free(cam->name);
	cam->name = name;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxCameras"));
	gtk_label_set_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(gtk_list_box_get_selected_row(GTK_LIST_BOX(widget))))), name);

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "LabelCurrentCamera"));
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras->name);
	return (NULL);
}

// UPDATE CAMERA POSITION
void	*sig_update_cam_pos_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera 	*cam;

	printf("sig_update_cam_pos_x\n");
	cam = get_selected_camera(g);
	cam->pos.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

void	*sig_update_cam_pos_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera 	*cam;

	printf("sig_update_cam_pos_y\n");
	cam = get_selected_camera(g);
	cam->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

void	*sig_update_cam_pos_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera 	*cam;
	printf("sig_update_cam_pos_z\n");
	cam = get_selected_camera(g);
	cam->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	return (NULL);
}

// UPDATE CAMERA LOOK AT
void	*sig_update_cam_lookat_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;
	GtkWidget	*widget;
	printf("sig_update_cam_lookat_x\n");
	cam = get_selected_camera(g);
	cam->look_at.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	cam->dir = v_norm(v_sub(cam->look_at, cam->pos));

	if (cam->dir.x == 0 && cam->dir.y == 0 && cam->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with doubles?)
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraLookAtX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->look_at.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_update_cam_lookat_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera 	*cam;
	GtkWidget	*widget;
	printf("sig_update_cam_lookat_y\n");	
	cam = get_selected_camera(g);
	cam->look_at.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	cam->dir = v_norm(v_sub(cam->look_at, cam->pos));

	if (cam->dir.x == 0 && cam->dir.y == 0 && cam->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with doubles?)
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraLookAtY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->look_at.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_update_cam_lookat_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;
	GtkWidget	*widget;

	printf("sig_update_cam_lookat_z\n");	
	cam = get_selected_camera(g);
	cam->look_at.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	cam->dir = v_norm(v_sub(cam->look_at, cam->pos));

	if (cam->dir.x == 0 && cam->dir.y == 0 && cam->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with doubles?)
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraLookAtZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->look_at.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_update_cam_lookat_name(GtkWidget *ComboBox, t_gtk_tools *g)
{
	t_vec3 		look_at;
	t_camera	*cam;
	GtkWidget	*widget;

	printf("sig_update_cam_lookat_name\n");
	cam = get_selected_camera(g);
	if (v_isnan(look_at = get_look_at_obj(GTK_COMBO_BOX(ComboBox), g)))
		return (NULL); // INVALID OBJ POS
	cam->dir = v_norm(v_sub(look_at, cam->pos));
	if (cam->dir.x == 0 && cam->dir.y == 0 && cam->dir.x == 0)
		return (NULL); // NUll direction is invalid (comparision works with doubles?)
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraLookAtX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), look_at.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraLookAtY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), look_at.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraLookAtZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), look_at.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionX"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.x);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionY"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.y);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "SpinButtonCameraDirectionZ"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cam->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

// UPDATE OBJECT DIRECTION
void	*sig_update_cam_dir_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera 	*cam;
	GtkWidget	*widget;

	printf("sig_update_cam_dir_x\n");
	cam = get_selected_camera(g);
	cam->dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_update_cam_dir_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera 	*cam;
	GtkWidget	*widget;

	printf("sig_update_cam_dir_y\n");
	cam = get_selected_camera(g);
	cam->dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_update_cam_dir_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera 	*cam;
	GtkWidget	*widget;

	printf("sig_update_cam_dir_z\n");
	cam = get_selected_camera(g);
	cam->dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive (widget, TRUE);
	return (NULL);
}

void	*sig_cam_dir_normalize(GtkWidget *button, t_gtk_tools *g)
{
	t_camera 	*cam;
	GtkWidget	*widget;

	cam = get_selected_camera(g);
	cam->dir = v_norm(cam->dir);
	printf("normalizing direction: [%f][%f][%f]\n", cam->dir.x, cam->dir.y, cam->dir.z);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonCameraDirNormalize"));
	gtk_widget_set_sensitive (widget, FALSE);
	update_cameras_info_panel(g, cam);
	return (NULL);
}

void	*sig_update_cam_fov(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera 	*cam;
	
	printf("sig_update_cam_fov\n");
	cam = get_selected_camera(g);
	cam->fov = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	update_camera_scale(cam);
	return (NULL);
}