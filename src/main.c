/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/22 14:34:17 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.cuh"
#include "../inc/gui.h"
#include "../inc/cuda_call.h"

#include <pthread.h>
 
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

void *sig_render(GtkWidget *widget, t_gtk_tools *g)
{
	t_object 	*obj;
	GtkWidget	*widget2;

	update_camera_ctw(g->r->scene->cameras);
	widget2 = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	if (gtk_widget_get_sensitive (widget2))
	{
		obj = get_selected_object(g);
		obj->dir = v_norm(obj->dir);
		update_objects_info_panel(g, obj);
		gtk_widget_set_sensitive (widget2, FALSE);
	}
	rt(g->r);
	return (NULL);
}

void *sig_print_scenes(GtkWidget *button, t_gtk_tools *g)
{
	print_scenes(g->r->scene);
	return (NULL);
}

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
}

int	main(int ac, char **av)
{
	GtkWidget       *window;
	GtkWidget		*widget;
	t_gtk_tools			g;
	t_parse_tools		t;
	t_raytracing_tools	r;
	int					i;
	GtkCssProvider		*cssProvider;
	
	g.t = &t;
	g.r = &r;
	g.filename = NULL;
	gtk_init(&ac, &av);
	init_raytracing_tools(&g.r);
	cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, CSS_PATH, NULL); //NULL instead of GError**
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
		GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g.builder = gtk_builder_new();
    gtk_builder_add_from_file (g.builder, "RT_glade.glade", NULL);
    gtk_builder_connect_signals(g.builder, &g);
	if (ac >= 2)
	{
		g.filename = ft_strdup(av[1]);
		open_scene(&g, NULL);
	}
	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "MenuItemQuit"));
	g_signal_connect(widget, "activate", G_CALLBACK(on_window_main_destroy), NULL);
    window = GTK_WIDGET(gtk_builder_get_object(g.builder, "window_main"));
	gtk_widget_show(window);
    gtk_main();
	return (0);

    // g_object_unref(g.builder);
	// free_scenes(r.scene);
}

int		display_error_popup(GtkWidget *filechooser, t_gtk_tools *g, char *ret)
{
	filechooser ? gtk_widget_destroy(filechooser) : 0;
	gtk_popup_dialog(ret, g);
	return (1);
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
	g->r->scene = g->t->scenes;
	update_grid_scene(g);
	update_grid_objects(g);
	update_grid_lights(g);
	update_grid_cameras(g);
	free_parse_tools(g->t);
	filechooser ? gtk_widget_destroy(filechooser) : 0;
	return (0);
}