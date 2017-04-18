/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/18 13:14:17 by jwalsh           ###   ########.fr       */
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
		// update_grid_objects(g);
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

void *sig_open_scene(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkWidget 	*dialog;
	gint		res;
	GtkWidget	*widget;

	if (g->filename)
		g_free(g->filename);
	dialog = gtk_file_chooser_dialog_new ("Open File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
                                      "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT,
                                      NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		g->filename = gtk_file_chooser_get_filename (chooser);
		init_parse_tools(g->t);
		if (ft_strstr(g->filename, ".rt") && *(ft_strstr(g->filename, ".rt") + 3) == '\0')
			get_file(g->filename, g->t);
		else
			rt_file_warning(NULL, "Skipped invalid file.");
		clock_t start = clock();
		parse_input(g->t);
		check_scenes(g->t->scenes);
		clock_t stop = clock();
		printf("\n0. Parsing : %f milliseconds\n",
		(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);

		//TODO: change parser to read only one scene.
		g->r->scene = g->t->scenes;
		update_grid_scene(g);
		update_grid_objects(g);
		update_grid_lights(g);
		update_grid_cameras(g);

		free_parse_tools(g->t);
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "NoteBookMenu"));
		gtk_widget_set_visible(widget, TRUE);	
		gtk_widget_destroy (dialog);
	}
	return (NULL);
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
	g.filename = NULL;
	gtk_init(&ac, &av);
	
    g.builder = gtk_builder_new();
    gtk_builder_add_from_file (g.builder, "RT_glade.glade", NULL);

	if (ac >= 2)
	{
		// Some code duplication. Create function ?
		init_parse_tools(g.t);
		if (ft_strstr(av[1], ".rt") && *(ft_strstr(av[1], ".rt") + 3) == '\0')
		{
			get_file(av[1], g.t);
			g.filename = ft_strdup(av[1]);
		}
		else
			rt_file_warning(NULL, "Skipped invalid file.");
		parse_input(g.t);
		check_scenes(g.t->scenes);
		g.r->scene = g.t->scenes;
		update_grid_scene(&g);
		update_grid_objects(&g);
		update_grid_lights(&g);
		update_grid_cameras(&g);
		free_parse_tools(g.t);
		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g.builder), "NoteBookMenu"));
		gtk_widget_set_visible(widget, TRUE);
	}

    window = GTK_WIDGET(gtk_builder_get_object(g.builder, "window_main"));

	//passing g instead of null means that &g is the user data that will be read by signals.
	//Now, any signal function which takes in g can be connected in the .ui file and can all be
	//connected at once with one call to the following function. 
    gtk_builder_connect_signals(g.builder, &g);

	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "MenuItemQuit"));
	g_signal_connect(widget, "activate", G_CALLBACK(on_window_main_destroy), NULL);
	gtk_widget_show(window);
	// gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_activate_focus (GTK_WINDOW(window));    
	gtk_widget_show(window);    
	// gtk_widget_set_can_focus(window, TRUE);
	// gtk_widget_grab_focus (window);
	// gtk_window_activate_focus (GTK_WINDOW(window));
    gtk_main();
	return (0);

    // g_object_unref(g.builder);
	// free_scenes(r.scene);
}

