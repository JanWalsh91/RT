/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_open_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 13:46:54 by tgros             #+#    #+#             */
/*   Updated: 2017/06/07 14:50:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"
#include <cuda_runtime.h>

static int	get_scene(t_gtk_tools *g, GtkWidget *filechooser);
static void	open_response_accept(t_gtk_tools *g, GtkWidget *dialog);

void		*sig_open_scene(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkFileFilter	*file_filter;
	GtkWidget		*dialog;
	int				dialog_ret;

	(void)menu_item;
	printf("sig open scene\n");
	dialog = gtk_file_chooser_dialog_new("Open File", NULL,
				GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel",
				GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(
					gtk_builder_get_object(g->builder, "window_main")));
	file_filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(file_filter, "*.rt");
	gtk_file_filter_set_name(file_filter, "RT files");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), file_filter);
	dialog_ret = gtk_dialog_run(GTK_DIALOG(dialog));
	if (dialog_ret == GTK_RESPONSE_ACCEPT)
		open_response_accept(g, dialog);
	else
		gtk_widget_destroy(dialog);
	return (NULL);
}

static void	open_response_accept(t_gtk_tools *g, GtkWidget *dialog)
{
	GtkFileChooser	*chooser;

	chooser = GTK_FILE_CHOOSER(dialog);
	if (g->filename)
	{
		g_free(g->filename);
		g->filename = NULL;
	}
	g->filename = gtk_file_chooser_get_filename(chooser);
	open_scene(g, dialog);
}

int			open_scene(t_gtk_tools *g, GtkWidget *filechooser)
{
	printf("open_scene: [%s]\n", g->filename);
	if (get_scene(g, filechooser))
		return (1);
	if (g->r->scene)
		cuda_free(g->r, 0);
	g->r->scene = g->t->scene;
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
	gtk_window_set_title(GTK_WINDOW(gtk_builder_get_object(
			GTK_BUILDER(g->builder), "window_main")), g->filename);
	return (0);
}

static int	get_scene(t_gtk_tools *g, GtkWidget *filechooser)
{
	char	*ret;

	init_parse_tools(g->t);
	if (ft_strstr(g->filename, ".rt") &&
		*(ft_strstr(g->filename, ".rt") + 3) == '\0')
	{
		if ((ret = get_file(g->filename, g->t)))
			return (display_error_popup(filechooser, g, ret));
	}
	else
		return (display_error_popup(filechooser, g, "Invalid file format."));
	if ((ret = parse_input(g->t)))
		return (display_error_popup(filechooser, g, ret));
	if ((ret = check_scene(g->t->scene)))
		return (display_error_popup(filechooser, g, ret));
	return (0);
}
