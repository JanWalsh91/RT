/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects9.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 11:22:54 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include <cuda_runtime.h>

static void	activate_normal_map_gui(t_gtk_tools *g, GtkWidget *chooser);

void		*sig_update_obj_normal_map(GtkWidget *file_chooser, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	if (obj->normal_map)
		cudaFreeHost(obj->normal_map);
	if (obj->normal_map_name)
		free(obj->normal_map_name);
	if (gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)) == NULL)
		return (NULL);
	if (!(obj->normal_map = read_bmp(gtk_file_chooser_get_filename(
					GTK_FILE_CHOOSER(file_chooser)), &obj->normal_map_dim)))
	{
		display_error_popup(NULL, g, "Invalid .bmp file");
		return (NULL);
	}
	activate_normal_map_gui(g, file_chooser);
	free(obj->normal_map_name);
	obj->normal_map_name = ft_strdup(gtk_file_chooser_get_filename(
											GTK_FILE_CHOOSER(file_chooser)));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

static void	activate_normal_map_gui(t_gtk_tools *g, GtkWidget *chooser)
{
	GtkWidget	*widget;

	widget = get_widget(g, "LabelObjectNormalMap");
	gtk_label_set_text(GTK_LABEL(widget), get_file_name(
			gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser))));
	widget = get_widget(g, "SpinButtonObjectTextureX");
	gtk_widget_set_sensitive(widget, true);
	widget = get_widget(g, "SpinButtonObjectTextureY");
	gtk_widget_set_sensitive(widget, true);
	widget = get_widget(g, "SpinButtonObjectTextureTranslateX");
	gtk_widget_set_sensitive(widget, true);
	widget = get_widget(g, "SpinButtonObjectTextureTranslateY");
	gtk_widget_set_sensitive(widget, true);
}

void		*sig_uptate_obj_texture_ratio_x(GtkWidget *button, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->texture_ratio.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
	obj->texture_ratio.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void		*sig_uptate_obj_texture_ratio_y(GtkWidget *button, t_gtk_tools *g)
{
	t_object	*obj;

	obj = get_selected_object(g);
	obj->texture_ratio.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

void		*sig_delete_obj_normal_map(GtkWidget *button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	(void)button;
	obj = get_selected_object(g);
	if (obj->normal_map)
	{
		cudaFreeHost(obj->normal_map);
		obj->normal_map = NULL;
		widget = get_widget(g, "FileChooserNormalMap");
		widget = get_widget(g, "LabelObjectNormalMap");
		gtk_label_set_text(GTK_LABEL(widget), "");
		free(obj->normal_map_name);
		obj->normal_map_name = NULL;
		update_objects_info_panel(g, obj);
		(g->updating_gui) ? 0 : obj_render_sig(g);
	}
	return (NULL);
}
