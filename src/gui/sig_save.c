/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 11:08:11 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/03 16:38:41 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_save(GtkWidget *menu_item, t_gtk_tools *g)
{
	int	fd;

	(void)menu_item;
	fd = -1;
	if (!g->r->scene)
		return (NULL);
	fd = open(g->filename, O_WRONLY | O_TRUNC);
	if (fd == -1)
		g->filename = get_new_filename(g);
	if (!g->filename)
		return (NULL);
	if (fd == -1)
	{
		if ((fd = open(g->filename, O_CREAT | O_WRONLY, 0644)) == -1)
		{
			display_error_popup(NULL, g, "Unable to create the file");
			return (NULL);
		}
	}
	save_scene(fd, g->r->scene);
	close(fd);
	return (NULL);
}

void	*sig_save_as(GtkWidget *menu_item, t_gtk_tools *g)
{
	int		fd;
	char	*file_name;

	(void)menu_item;
	fd = -1;
	printf("sig_save_as\n");
	file_name = get_new_filename(g);
	if (file_name)
		g->filename = file_name;
	if ((fd = open(g->filename, O_CREAT | O_WRONLY, 0644)) == -1)
	{
		display_error_popup(NULL, g, "Unable to create the file");
		return (NULL);
	}
	save_scene(fd, g->r->scene);
	close(fd);
	return (NULL);
}

char	*get_new_filename(t_gtk_tools *g)
{
	GtkWidget		*dialog;
	char			*filename;

	printf("get_new_filename\n");
	filename = NULL;
	dialog = gtk_file_chooser_dialog_new("Save as .rt", GTK_WINDOW(
			gtk_builder_get_object(g->builder, "window_main")),
				GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL,
				"_Save", GTK_RESPONSE_ACCEPT, NULL);
	gtk_window_set_attached_to(GTK_WINDOW(gtk_builder_get_object(
			GTK_BUILDER(g->builder), "window_main")), dialog);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		printf("saving as [%s]\n", filename);
	}
	gtk_widget_destroy(dialog);
	return (filename);
}

int		get_parent_index(t_object *parent, t_object *objects)
{
	int i;

	i = 0;
	while (objects && parent != objects)
	{
		++i;
		objects = objects->next;
	}
	if (parent == objects)
		return (i + 1);
	return (0);
}
