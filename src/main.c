/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/18 13:25:22 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.cuh"
#include "../inc/gui.h"
#include "../inc/cuda_call.h"
#include <time.h>

void	gtk_popup_dialog(char *mesg, t_gtk_tools *g)
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
	dialog = gtk_message_dialog_new (GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")),
									GTK_DIALOG_MODAL,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"%s", error_mesg);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

void	init_raytracing_tools(t_raytracing_tools *r)
{
	r->update.resolution = 2;
	r->update.objects = 2;
	r->update.lights = 2;
	r->update.cameras = 2;
	r->update.scene = 2;
	r->update.ray_depth = 2;
	r->update.photon_map = 0;
	r->update.render = 0;
	r->rendering = 0;
	r->scene = NULL;
	r->d_scene = NULL;
	r->h_d_scene = NULL;
	r->d_pixel_map = NULL;
	r->h_d_scene = (t_scene *)malloc(sizeof(t_scene));
}


int main(int ac, char **av)
{
	t_gtk_tools			g;
	t_parse_tools		t;
	t_raytracing_tools	r;

	g.ac = ac;
	g.av = av;
	g.win = NULL;
	g.cr = NULL;
	g.updating_gui = 0;
	g.t = &t;
	g.r = &r;
	g.filename = (ac >= 2) ? ft_strdup(av[1]) : NULL;
	main_gtk(&g);
	return (0);
}

void	*main_gtk(t_gtk_tools *g)
{

	gtk_init(&g->ac, &g->av);
	init_raytracing_tools(g->r);
	build_gui(g);
	init_window(g);
	(g->filename) ? open_scene(g, NULL) : 0;
    gtk_main();
	clean_exit(g);
	return (NULL);
}

void	init_window(t_gtk_tools *g)
{
	GtkWidget       *window;
	GtkWidget		*widget;
	GtkAdjustment	*adj;
	GdkRectangle	res;
	
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "MenuItemQuit"));
	g_signal_connect(widget, "activate", G_CALLBACK(on_window_main_destroy), NULL);
	gdk_monitor_get_geometry(gdk_display_get_monitor(gdk_display_get_default(), 0), &res);
	adj = GTK_ADJUSTMENT(gtk_builder_get_object(g->builder, "AdjResolutionX"));
	gtk_adjustment_set_upper(adj, res.width);
	adj = GTK_ADJUSTMENT(gtk_builder_get_object(g->builder, "AdjResolutionY"));
	gtk_adjustment_set_upper(adj, res.height);
    window = GTK_WIDGET(gtk_builder_get_object(g->builder, "window_main"));
	gtk_widget_show(window);
	gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
}

void	build_gui(t_gtk_tools *g)
{
	GtkCssProvider		*cssProvider;

	cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, CSS_PATH, NULL); //NULL instead of GError**
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
		GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g->builder = gtk_builder_new();
    gtk_builder_add_from_file (g->builder, "RT_glade.glade", NULL);
    gtk_builder_connect_signals(g->builder, g);
}

int	clean_exit(t_gtk_tools *g)
{
	// cuda_free(&g->r, 1);
    g_object_unref(g->builder);
	// free_scenes(g->r->scene);
	return (1);
}

int		display_error_popup(GtkWidget *filechooser, t_gtk_tools *g, char *ret)
{
	filechooser ? gtk_widget_destroy(filechooser) : 0;
	gtk_popup_dialog(ret, g);
	return (1);
}
