/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_cameras1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 14:32:31 by tgros             #+#    #+#             */
/*   Updated: 2017/06/04 14:42:41 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.h"

void	*sig_update_current_cam(GtkListBox *box, GtkListBoxRow *row,
													t_gtk_tools *g)
{
	int			index;
	int			i;
	t_camera	*c_ptr;

	(void)box;
	printf("sig_update_current_cam\n");
	i = -1;
	index = gtk_list_box_row_get_index(row);
	c_ptr = get_first_camera(g);
	while (++i != index && c_ptr)
		c_ptr = c_ptr->next;
	if (i != index || !c_ptr)
		return (NULL);
	update_cameras_info_panel(g, c_ptr);
	return (NULL);
}

void	*sig_update_cam_name(GtkWidget *gtk_entry, t_gtk_tools *g)
{
	GtkWidget	*widget;
	char		*name;
	t_camera	*cam;

	printf("sig_update_cam_name\n");
	cam = get_selected_camera(g);
	name = ft_strdup((char *)gtk_entry_get_text((struct _GtkEntry *)gtk_entry));
	free(cam->name);
	cam->name = name;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
														"ListBoxCameras"));
	gtk_label_set_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(
		gtk_list_box_get_selected_row(GTK_LIST_BOX(widget))))), name);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
													"LabelCurrentCamera"));
	gtk_label_set_text(GTK_LABEL(widget), g->r->scene->cameras->name);
	return (NULL);
}

void	*sig_update_cam_pos_x(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;

	printf("sig_update_cam_pos_x\n");
	cam = get_selected_camera(g);
	cam->pos.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : camera_render_sig(g);
	return (NULL);
}

void	*sig_update_cam_pos_y(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;

	printf("sig_update_cam_pos_y\n");
	cam = get_selected_camera(g);
	cam->pos.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : camera_render_sig(g);
	return (NULL);
}

void	*sig_update_cam_pos_z(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_camera	*cam;

	printf("sig_update_cam_pos_z\n");
	cam = get_selected_camera(g);
	cam->pos.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : camera_render_sig(g);
	return (NULL);
}
