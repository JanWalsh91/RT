/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/20 16:14:10 by jwalsh           ###   ########.fr       */
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
		update_objects_info_panel(g, obj);
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

void *sig_open_scene(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkFileFilter	*file_filter;
	GtkWidget 		*dialog;
	GtkWidget		*widget;
	char			*ret;
	gint			res;

	if (g->filename)
		g_free(g->filename);
	dialog = gtk_file_chooser_dialog_new ("Open File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
										"_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	file_filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(file_filter, "*.rt");
	gtk_file_filter_set_name(file_filter, "RT files");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), file_filter);
	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		g->filename = gtk_file_chooser_get_filename (chooser);
		init_parse_tools(g->t);
		if (ft_strstr(g->filename, ".rt") && *(ft_strstr(g->filename, ".rt") + 3) == '\0')
		{
			if ((ret = get_file(g->filename, g->t)))
			{
				gtk_widget_destroy(dialog);
				gtk_popup_dialog(ret, g);
				return (NULL);
			}
		}
		else
		{
			gtk_widget_destroy(dialog);
			gtk_popup_dialog("Invalid file format.", g);
			return (NULL);
		}
		clock_t start = clock();
		if ((ret = parse_input(g->t)))
		{
			gtk_widget_destroy(dialog);
			gtk_popup_dialog(ret, g);
			return (NULL);
		}
		if ((ret = check_scenes(g->t->scenes)))
		{
			// big code duplication ! ><
			gtk_widget_destroy(dialog);
			gtk_popup_dialog(ret, g);
			return (NULL);
		}
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

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonPreviousCamera"));
		gtk_widget_set_sensitive(widget, TRUE);

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonNextCamera"));
		gtk_widget_set_sensitive(widget, TRUE);

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonRender"));
		gtk_widget_set_sensitive(widget, TRUE);
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
		{
			rt_file_warning(NULL, "Skipped invalid file.");
			// gtk_popup_dialog("Invalid file.", &g);
		}
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

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g.builder), "ButtonPreviousCamera"));
		gtk_widget_set_sensitive(widget, TRUE);

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g.builder), "ButtonNextCamera"));
		gtk_widget_set_sensitive(widget, TRUE);

		widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g.builder), "ButtonRender"));
		gtk_widget_set_sensitive(widget, TRUE);
	}

    window = GTK_WIDGET(gtk_builder_get_object(g.builder, "window_main"));

	//passing g instead of null means that &g is the user data that will be read by signals.
	//Now, any signal function which takes in g can be connected in the .ui file and can all be
	//connected at once with one call to the following function. 
    gtk_builder_connect_signals(g.builder, &g);

	widget = GTK_WIDGET(gtk_builder_get_object(g.builder, "MenuItemQuit"));
	g_signal_connect(widget, "activate", G_CALLBACK(on_window_main_destroy), NULL);

	GtkStyleContext *context;
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g.builder), "ButtonRender"));
	context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_class(context, "enter_button");
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g.builder), "ListBoxObjects"));
	gtk_style_context_add_class(context, "listbox");


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

