/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_open_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 13:46:54 by tgros             #+#    #+#             */
/*   Updated: 2017/05/03 11:40:02 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"


void *sig_open_scene(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkFileFilter	*file_filter;
	GtkWidget 		*dialog;
	GtkWidget		*widget;
	char			*ret;

	if (g->filename)
		g_free(g->filename);
	dialog = gtk_file_chooser_dialog_new ("Open File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
										"_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	file_filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(file_filter, "*.rt");
	gtk_file_filter_set_name(file_filter, "RT files");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), file_filter);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		g->filename = gtk_file_chooser_get_filename (chooser);
		open_scene(g, dialog);
	}
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
	if ((ret = parse_input(g->t)) || (ret = check_scenes(g->t->scenes)))
		return (display_error_popup(filechooser, g, ret));
	if (g->r->scene)
		cuda_free(g->r, 0);
	g->r->scene = g->t->scenes;
	// g->r->scene->is_3d = 1;
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
	free_parse_tools(g->t);
	filechooser ? gtk_widget_destroy(filechooser) : 0;
	return (0);
}
