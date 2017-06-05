/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_export_scene_bmp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:31:50 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 14:11:39 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"

static void		update_loading_bar(GtkWidget *dialog, t_gtk_tools *g,
							t_th_export *th_export);
static void		export_accept(GtkWidget *dialog, t_th_export *th_export,
									t_gtk_tools *g);

void			*sig_export_scene_bmp(GtkWidget *widget, t_gtk_tools *g)
{
	GtkWidget		*dialog;
	t_th_export		th_export;

	(void)widget;
	if (!g->r->scene)
		return (NULL);
	if (!g->pixbuf)
	{
		display_error_popup(NULL, g,
			"Please render the scene once before exporting.");
		return (NULL);
	}
	th_export.progress = 0;
	th_export.g = g;
	dialog = gtk_file_chooser_dialog_new("Save as .bmp", GTK_WINDOW(
		gtk_builder_get_object(g->builder, "window_main")),
		GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL,
		"_Save", GTK_RESPONSE_ACCEPT, NULL);
	gtk_window_set_attached_to(GTK_WINDOW(gtk_builder_get_object(
			GTK_BUILDER(g->builder), "window_main")), dialog);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
		export_accept(dialog, &th_export, g);
	return (NULL);
}

static void		export_accept(GtkWidget *dialog, t_th_export *th_export,
														t_gtk_tools *g)
{
	GtkFileChooser	*chooser;

	chooser = GTK_FILE_CHOOSER(dialog);
	th_export->filename = ft_strdup(gtk_file_chooser_get_filename(chooser));
	if (!check_file_ext(th_export->filename, "BMP"))
		th_export->filename = ft_strjoinfree(th_export->filename, ".bmp", 'l');
	gtk_widget_destroy(dialog);
	dialog = gtk_dialog_new();
	gtk_window_set_attached_to(GTK_WINDOW(gtk_builder_get_object(
				GTK_BUILDER(g->builder), "window_main")), dialog);
	update_loading_bar(dialog, g, th_export);
	free(th_export->filename);
	gtk_widget_destroy(dialog);
}

static void		update_loading_bar(GtkWidget *dialog, t_gtk_tools *g,
										t_th_export *th_export)
{
	GtkWidget		*loading_bar;
	pthread_t		export_thread;

	loading_bar = gtk_progress_bar_new();
	gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(
							GTK_DIALOG(dialog))), loading_bar);
	if (!g->win)
		render_wrapper(g);
	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(loading_bar), TRUE);
	gtk_widget_show_all(dialog);
	pthread_create(&export_thread, NULL, export_image, th_export);
	while (th_export->progress < 1.0)
	{
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(loading_bar),
											th_export->progress);
		gtk_main_iteration_do(TRUE);
	}
	pthread_join(export_thread, NULL);
}
