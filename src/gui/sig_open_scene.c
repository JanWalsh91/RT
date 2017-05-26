/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_open_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 13:46:54 by tgros             #+#    #+#             */
/*   Updated: 2017/05/26 15:29:37 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"
#include <cuda_runtime.h>

/*
** 
*/

static void	set_default_values_scene(t_gtk_tools *g);
static void	set_default_values_camera(t_gtk_tools *g);

void	*sig_new_scene(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkWidget	*widget;

	printf("sig_new_scene\n");
	if (g->filename)
	{
		g_free(g->filename);
		g->filename = NULL;
	}
	if (g->r->scene)
	{
		// cudaDeviceReset(); //unsafe to use with CPU multithreading.
		cuda_free(g->r, 1);
		free_scene(g->r->scene);
	}
	if (g->win)
		gtk_widget_destroy(g->win);
		// cuda_free(g->r, 0);
	if (!(g->r->scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	set_default_values_scene(g);
	if (!(g->r->scene->cameras = (t_camera *)ft_memalloc(sizeof(t_camera))))
		ft_error_exit("Malloc error.");
	set_default_values_camera(g);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "NoteBookMenu"));
	gtk_widget_set_visible(widget, TRUE);
	g->r->update.cameras = 2;
	g->r->update.scene = 2;
	cuda_malloc(g->r);
	update_grid_scene(g);
	gtk_container_foreach (GTK_CONTAINER(gtk_builder_get_object(GTK_BUILDER(g->builder), "ListBoxObjects")), (GtkCallback)G_CALLBACK(gtk_widget_destroy), NULL);
	update_grid_lights(g);
	update_grid_cameras(g);
	populate_list_box_objects(g);
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ScrollWindowObject"));
	gtk_widget_set_sensitive(widget, false);
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ScrollWindowLight"));
	gtk_widget_set_sensitive(widget, false);
	return (NULL);
}

static void	set_default_values_scene(t_gtk_tools *g)
{
	g->r->scene->res.x = DEFAULT_RES_W;
	g->r->scene->res.y = DEFAULT_RES_H;
	g->r->scene->ray_depth = DEFAULT_RAY_DEPTH;
	g->r->scene->objects = NULL;
	g->r->scene->cameras = NULL;
	g->r->scene->lights = NULL;
	g->r->scene->background_color = v_new(0, 0, 0);
	g->r->scene->ambient_light_color = v_new(255, 255, 255);
	g->r->scene->ka = 0.1;
	g->r->scene->image_aspect_ratio = 1;
	g->r->scene->name = NULL;
	g->r->scene->is_diffuse = true;
	g->r->scene->is_shadow = true;
	g->r->scene->is_specular = true;
	g->r->scene->is_fresnel = true;
	g->r->scene->is_photon_mapping = false; 
	g->r->scene->photon_map = NULL;
	g->r->scene->selected_photons = NULL;
	g->r->scene->is_aa = 1;
}

static void	set_default_values_camera(t_gtk_tools *g)
{
	g->r->scene->cameras->name = ft_strdup("New Camera");
	g->r->scene->cameras->dir.z = 1.0;
	g->r->scene->cameras->prev = NULL;
	g->r->scene->cameras->next = NULL;
	g->r->scene->cameras->fov = 45;
	g->r->scene->cameras->filter = 0;
	g->r->scene->cameras->ior = 1.01;
}

void 	*sig_open_scene(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkFileFilter	*file_filter;
	GtkWidget 		*dialog;
	GtkWidget		*widget;
	char			*ret;
	int				dialog_ret;

	printf("sig open scene\n");

	dialog = gtk_file_chooser_dialog_new ("Open File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
										"_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(gtk_builder_get_object(g->builder, "window_main")));
	file_filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(file_filter, "*.rt");
	gtk_file_filter_set_name(file_filter, "RT files");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), file_filter);
	dialog_ret = gtk_dialog_run(GTK_DIALOG (dialog));
	if (dialog_ret == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		if (g->filename)
		{
			g_free(g->filename);
			g->filename = NULL;
		}
		g->filename = gtk_file_chooser_get_filename (chooser);
		open_scene(g, dialog);
	}
	else
		gtk_widget_destroy(dialog);
	return (NULL);
}

int		open_scene(t_gtk_tools *g, GtkWidget *filechooser)
{
	GtkWidget 		*dialog;
	GtkWidget		*widget;
	char			*ret;
	
	printf("open_scene: [%s]\n", g->filename);
	init_parse_tools(g->t);
	if (ft_strstr(g->filename, ".rt") && *(ft_strstr(g->filename, ".rt") + 3) == '\0')
	{
		if ((ret = get_file(g->filename, g->t)))
			return (display_error_popup(filechooser, g, ret));
	}
	else
		return (display_error_popup(filechooser, g, "Invalid file format."));
	if ((ret = parse_input(g->t)) || (ret = check_scene(g->t->scene)))
		return (display_error_popup(filechooser, g, ret));
	if (g->r->scene)
		cuda_free(g->r, 0);
	g->r->scene = g->t->scene;
	cuda_malloc(g->r);
	update_grid_scene(g);
	populate_list_box_objects(g);
	update_grid_lights(g);
	update_grid_cameras(g);
	g->r->update.resolution = 2;
	g->r->update.objects = 2;
	g->r->update.lights = 2;
	g->r->update.cameras = 2;
	g->r->update.scene = 2;
	g->r->update.ray_depth = 2;
	g->r->update.photon_map = 0;
	g->r->scene->is_aa = 1;
	g->r->scene->is_3d = 0;
	free_parse_tools(g->t);
	filechooser ? gtk_widget_destroy(filechooser) : 0;
	gtk_window_set_title(GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")), g->filename);
	return (0);
}
