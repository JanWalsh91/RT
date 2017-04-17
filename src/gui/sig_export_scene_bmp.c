/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_export_scene_bmp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:31:50 by tgros             #+#    #+#             */
/*   Updated: 2017/04/17 13:35:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"

void *sig_export_scene_bmp(GtkWidget *widget, t_gtk_tools *g)
{
	GtkWidget		*dialog;
	GtkWidget		*loading_bar;
	t_th_export		th_export;
	pthread_t		export_thread;
	GtkFileChooser	*chooser;

	th_export.progress = 0;
	th_export.g = g;
	dialog = gtk_file_chooser_dialog_new("Save as .bmp", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
											"_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
	gtk_window_set_attached_to (GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")), dialog);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		chooser = GTK_FILE_CHOOSER (dialog);
		th_export.filename = gtk_file_chooser_get_filename (chooser);


		loading_bar = gtk_progress_bar_new();
		gtk_widget_destroy(dialog);
		dialog = gtk_dialog_new();
		gtk_window_set_attached_to (GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")), dialog);
		// dialog = gtk_dialog_new_with_buttons ("My dialog",
		// 							  GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")), 0, NULL);
		// gtk_box_pack_start(GTK_BOX(), loading_bar, TRUE, TRUE, 0);

 		gtk_container_add(GTK_CONTAINER (gtk_dialog_get_content_area(GTK_DIALOG(dialog))), loading_bar);
		render(g->r->scene);
		gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(loading_bar), TRUE);
		gtk_widget_show_all(dialog);
		pthread_create(&export_thread, NULL, export_image, &th_export);
		while (th_export.progress < 1.0)
		{
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(loading_bar), th_export.progress);
			gtk_main_iteration_do(TRUE);
		}
		pthread_join(export_thread, NULL);
		g_free (th_export.filename);
	}
	gtk_widget_destroy(dialog);
	return (NULL);
}
