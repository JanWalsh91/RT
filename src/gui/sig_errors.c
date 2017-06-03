/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 15:45:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/03 11:35:22 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	gtk_popup_dialog(char *mesg, t_gtk_tools *g);

int			display_error_popup(GtkWidget *chooser, t_gtk_tools *g, char *ret)
{
	chooser ? gtk_widget_destroy(chooser) : 0;
	gtk_popup_dialog(ret, g);
	return (1);
}

static void	gtk_popup_dialog(char *mesg, t_gtk_tools *g)
{
	GtkWidget		*dialog;
	char			error_mesg[512];
	char			*line_number;

	ft_bzero(error_mesg, 512);
	ft_strcat(error_mesg, "Error in the file:\n");
	ft_strcat(error_mesg, g->filename);
	ft_strcat(error_mesg, ".\n\n");
	ft_strcat(error_mesg, mesg);
	if (g->t->input)
	{
		line_number = ft_itoa((int)g->t->input->line_number);
		ft_strcat(error_mesg, "\nLine: ");
		ft_strcat(error_mesg, line_number);
		free(line_number);
	}
	dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_builder_get_object(
						GTK_BUILDER(g->builder), "window_main")),
						GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
						GTK_BUTTONS_CLOSE, "%s", error_mesg);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	if (ft_strncmp(mesg, "!!", 2) == 0)
		ft_strdel(&mesg);
}
