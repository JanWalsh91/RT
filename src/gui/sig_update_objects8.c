/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects8.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:56:33 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 12:12:37 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include <cuda_runtime.h>

static int	get_new_texture(t_object *obj, t_gtk_tools *g, GtkWidget *chooser);
static void	activate_texture_gui(t_gtk_tools *g, GtkWidget *chooser);
static void	check_all_objects_for_texture(t_gtk_tools *g, t_object *obj);

void		*sig_update_obj_texture(GtkWidget *chooser, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_texture\n");
	obj = get_selected_object(g);
	if (obj->texture)
		cudaFreeHost(obj->texture);
	if (obj->texture_name)
		free(obj->texture_name);
	if (gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser)) == NULL ||
		!get_new_texture(obj, g, chooser))
		return (NULL);
	activate_texture_gui(g, chooser);
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}

static void	activate_texture_gui(t_gtk_tools *g, GtkWidget *chooser)
{
	GtkWidget	*widget;

	widget = get_widget(g, "LabelObjectTexture");
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
	widget = get_widget(g, "ComboBoxGeneratedTexture");
	gtk_widget_set_sensitive(widget, false);
}

static int	get_new_texture(t_object *obj, t_gtk_tools *g, GtkWidget *chooser)
{
	t_object	*tmp;

	obj->texture_name = ft_strdup(gtk_file_chooser_get_filename(
										GTK_FILE_CHOOSER(chooser)));
	tmp = find_texture(g->r->scene->objects, obj, obj->texture_name,
													obj->texture_dim);
	if (!tmp)
	{
		if (!(obj->texture = read_bmp(gtk_file_chooser_get_filename(
					GTK_FILE_CHOOSER(chooser)), &obj->texture_dim)))
		{
			display_error_popup(NULL, g, "Invalid .bmp file");
			return (0);
		}
	}
	else
	{
		obj->texture = tmp->texture;
		obj->texture_dim = tmp->texture_dim;
	}
	return (1);
}

void		*sig_delete_obj_texture(GtkWidget *button, t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;

	(void)button;
	obj = get_selected_object(g);
	if (obj->texture)
	{
		widget = get_widget(g, "FileChooserTexture");
		widget = get_widget(g, "LabelObjectTexture");
		gtk_label_set_text(GTK_LABEL(widget), "");
		widget = get_widget(g, "ComboBoxGeneratedTexture");
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
		gtk_widget_set_sensitive(widget, true);
		check_all_objects_for_texture(g, obj);
		cudaFreeHost(obj->texture);
		obj->texture = NULL;
		free(obj->texture_name);
		obj->texture_name = NULL;
		update_objects_info_panel(g, obj);
		(g->updating_gui) ? 0 : obj_render_sig(g);
	}
	return (NULL);
}

static void	check_all_objects_for_texture(t_gtk_tools *g, t_object *obj)
{
	t_object	*tmp;

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
}
