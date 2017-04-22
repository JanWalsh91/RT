/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_open_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 13:46:54 by tgros             #+#    #+#             */
/*   Updated: 2017/04/22 13:47:06 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

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