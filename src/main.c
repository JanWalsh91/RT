/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/07 17:07:16 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.cuh"
#include "../inc/gui.h"
#include "../inc/cuda_call.h"

/*
** Checks arg count, parses and prepares data, and sends data to rt.
*/

#include <pthread.h>
 
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}


void *sig_render(GtkWidget *widget, gpointer *data)
{
	rt((t_raytracing_tools *)data);
	return (NULL);
}

void *sig_export_scene_bmp(GtkWidget *widget, t_gtk_tools *g)
{
	GtkWidget	*dialog;
	GtkWidget	*loading_bar;
	t_th_export	th_export;
	pthread_t	export_thread;

	th_export.progress = 0;
	th_export.g = g;
	dialog = gtk_file_chooser_dialog_new("Save as .bmp", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
											"_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
	gtk_window_set_attached_to (GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")), dialog);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		th_export.filename = gtk_file_chooser_get_filename (chooser);


		loading_bar = gtk_progress_bar_new();
		gtk_widget_destroy(dialog);
		dialog = gtk_dialog_new();
		gtk_window_set_attached_to (GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")), dialog);
		// dialog = gtk_dialog_new_with_buttons ("My dialog",
		// 							  GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")), 0, NULL);
		// gtk_box_pack_start(GTK_BOX(), loading_bar, TRUE, TRUE, 0);

 		gtk_container_add(GTK_CONTAINER (gtk_dialog_get_content_area(GTK_DIALOG(dialog))), loading_bar);
		render(g->r->scenes);
		// gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(loading_bar), 0);
		gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(loading_bar), TRUE);
		gtk_widget_show_all(dialog);
		pthread_create(&export_thread, NULL, export_image, &th_export);
		while (th_export.progress < 1.0)
		{
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(loading_bar), th_export.progress);
			gtk_main_iteration_do(TRUE);
		}
		C(19)
		pthread_join(export_thread, NULL);
		C(20)
		g_free (th_export.filename);
		C(21)
		gtk_widget_destroy(dialog);
	}
	return (NULL);
}


void *sig_open_scene(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkWidget 	*dialog;
	gint		res;
	char		*filename;
	GtkWidget	*widget;

	dialog = gtk_file_chooser_dialog_new ("Open File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
                                      "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT,
                                      NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		filename = gtk_file_chooser_get_filename (chooser);
		init_parse_tools(g->t);
		if (ft_strstr(filename, ".rt") && *(ft_strstr(filename, ".rt") + 3) == '\0')
			get_file(filename, g->t);
		else
			rt_file_warning(NULL, "Skipped invalid file.");
		clock_t start = clock();
		parse_input(g->t);
		check_scenes(g->t->scenes);
		clock_t stop = clock();
		printf("\n0. Parsing : %f milliseconds\n",
		(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);

		g->r->scenes = g->t->scenes;
		update_scene_panel(g);
		update_objects_panel(g);
		update_lights_panel(g);
		// update_cameras_panel

		free_parse_tools(g->t);
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "NoteBookMenu"));
		gtk_widget_set_visible(widget, TRUE);
		//print_scenes(r.scenes);
	
		g_free (filename);
		gtk_widget_destroy (dialog);
	}
	return (filename);
}


int	main(int ac, char **av)
{
	GtkWidget       *window;
	GtkWidget		*widget;
	t_gtk_tools			g;
	t_parse_tools		t;
	t_raytracing_tools	r;
	int					i;

	g.t = &t;
	g.r = &r;

	gtk_init(&ac, &av);
	
    g.builder = gtk_builder_new();
    gtk_builder_add_from_file (g.builder, "RT_glade.glade", NULL);

	if (ac >= 2)
	{
		// Some code duplication. Create function ?
		init_parse_tools(g.t);
		if (ft_strstr(av[1], ".rt") && *(ft_strstr(av[1], ".rt") + 3) == '\0')
			get_file(av[1], g.t);
		else
			rt_file_warning(NULL, "Skipped invalid file.");
		parse_input(g.t);
		check_scenes(g.t->scenes);
		g.r->scenes = g.t->scenes;
		update_scene_panel(&g);
		update_objects_panel(&g);
		update_lights_panel(&g);
		free_parse_tools(g.t);
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g.builder), "NoteBookMenu"));
		gtk_widget_set_visible(widget, TRUE);
	}

    window = GTK_WIDGET(gtk_builder_get_object(g.builder, "window_main"));
    gtk_builder_connect_signals(g.builder, NULL);
	
	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "ButtonRender"));
	g_signal_connect(widget, "clicked", G_CALLBACK (sig_render), &r);
	
	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "MenuItemQuit"));
	g_signal_connect(widget, "activate", G_CALLBACK(on_window_main_destroy), NULL);

	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "MenuItemOpenScene"));
	g_signal_connect(widget, "activate", G_CALLBACK(sig_open_scene), &g);

	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "MenuItemExportBMP"));
	g_signal_connect(widget, "activate", G_CALLBACK(sig_export_scene_bmp), &g);

	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "AmbientLightColorPicker"));
	g_signal_connect(widget, "color-set", G_CALLBACK(sig_udpate_ambient_light_color), &g);

	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "AmbientLightCoeffSpinButton"));
	g_signal_connect(widget, "value-changed", G_CALLBACK(sig_update_ambient_light_coeff), &g);

	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "ResolutionXSpinButton"));
	g_signal_connect(widget, "value-changed", G_CALLBACK(sig_update_res_x), &g);

	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "ResolutionYSpinButton"));
	g_signal_connect(widget, "value-changed", G_CALLBACK(sig_update_res_y), &g);

	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "ListBoxObjects"));
	g_signal_connect(widget, "row-activated", G_CALLBACK(sig_update_current_object), &g);

    // g_object_unref(g.builder);
 
    gtk_widget_show(window);                
    gtk_main();
	// free_scenes(r.scenes);
	return (0);
}

