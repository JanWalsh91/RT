/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/27 17:22:39 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.cuh"
#include "../inc/gui.h"
#include "../inc/cuda_call.h"
#include <time.h>
 
 
 #include <pthread.h>

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

void window_destroy(GtkWidget *widget, void *ouais)
{
	gtk_widget_destroy (ouais ? GTK_WIDGET(ouais) : widget);
}

void window_destroy_esc(GtkWidget *widget, void *ouais)
{
	gtk_widget_destroy (GTK_WIDGET(ouais));
}

void	increment_tile(t_pt2 *tileId, int size, t_pt2 res)
{
	if (++tileId->x == res.x / size + 1)
	{
		tileId->x = 0;
		++tileId->y;
	}
}

void *render_wrapper(gpointer data)
{
	t_gtk_tools	*g;
	t_pt2		tileId;
	int			max_tile;
	printf("render_wa\n");

	g = (t_gtk_tools *)data;
	// if (!g->pixbuf)
	// 	free(g->pixbuf); // leaks / WTF
	g->r->settings.tile_size = 32 * 3;
	g->pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, 0, 8, g->r->scene->res.x, g->r->scene->res.y);
	tileId.x = 0;
	tileId.y = 0;
	// max_tile = (g->r->scene->res.x / g->r->settings.tile_size + (g->r->scene->res.x % g->r->settings.tile_size) ? 1 : 0) *
	// 		   (g->r->scene->res.y / g->r->settings.tile_size + (g->r->scene->res.y % g->r->settings.tile_size) ? 1 : 0);
	max_tile = (g->r->scene->res.x / g->r->settings.tile_size + 1) *
			(g->r->scene->res.y / g->r->settings.tile_size + 1);
	cuda_malloc(g->r);
	while (tileId.x * tileId.y < max_tile && g->win) //to FIX (theo)
	{
		printf("[%d, %d], max tile: [%d]\n", tileId.x, tileId.y, max_tile);
		render(g->r, tileId);
		// sleep(1);
		ft_memcpy (gdk_pixbuf_get_pixels (g->pixbuf), g->r->d_pixel_map, gdk_pixbuf_get_rowstride (g->pixbuf) * g->r->scene->res.y);
		gtk_widget_queue_draw(g->win);
		increment_tile(&tileId, g->r->settings.tile_size, g->r->scene->res);
		printf("tileId.x * tileId.y: [%d]\n", tileId.x * tileId.y);
	}
	g->r->rendering = 0;
	return (FALSE);
}



gboolean draw_callback(GtkWidget *widget, cairo_t *cr, t_gtk_tools *g)
{
	printf("maman ?\n");
	pthread_t	render_thread;

	if (!g->cr)
	{
		// fill bbc
		g->cr = cr;
	}
	if (g->r->update.render == 1 && !g->r->rendering)
	{
		g->r->update.render = 0;
		g->r->rendering = 1;
		// g_thread_new (NULL, render_wrapper, g);
		printf("Create a new thread\n");
		// pthread_create(&render_thread, NULL, render_wrapper, g);
		
		g_thread_new ("Swaggy_turkey", render_wrapper, g);

		
		// gdk_threads_add_idle_full(1, render_wrapper, g, NULL);
		// gtk_threads_idle_add(render_wrapper, g);

		// GTask *task = g_task_new (NULL, NULL, shit, g);
		// g_task_set_task_data (task, g, g_free);
		// g_task_run_in_thread (task, render_wrapper);


		//	/* Runs the count_to_five() function in a thread, and calls
		// * count_to_five_done() when the thread terminates
		// */
		// GTask *task = g_task_new (label, cancellable, count_to_five_done, data);
		// g_task_set_task_data (task, data, g_free);
		// g_task_run_in_thread (task, count_to_five);
		// g_object_unref (task);
	}
	if (g->pixbuf)
	{
		clock_t start = clock();
		gdk_cairo_set_source_pixbuf(g->cr, g->pixbuf, 0, 0);
		cairo_paint(g->cr);
		clock_t end = clock();
		printf("g_threas_new time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	}
	return FALSE;
}

void *sig_render(GtkWidget *widget, t_gtk_tools *g)
{
	t_object 		*obj;
	GtkWidget		*widget2;
	GtkAccelGroup 	*accel_group;
	GClosure		*closure;
	GtkWidget 		*drawing_area;

	g->r->update.render = 1;
	update_camera_ctw(g->r->scene->cameras);
	widget2 = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	if (gtk_widget_get_sensitive (widget2))
	{
		obj = get_selected_object(g);
		obj->dir = v_norm(obj->dir);
		update_objects_info_panel(g, obj);
		gtk_widget_set_sensitive (widget2, FALSE);
	}

	g->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(g->win, "destroy", G_CALLBACK(window_destroy), NULL);
	closure = g_cclosure_new(G_CALLBACK(window_destroy_esc), g->win, 0);
    accel_group = gtk_accel_group_new();
    gtk_accel_group_connect(accel_group, GDK_KEY_Escape, 0, 0, closure);
	gtk_window_add_accel_group(GTK_WINDOW(g->win), accel_group);
	drawing_area = gtk_drawing_area_new();
	gtk_container_add (GTK_CONTAINER (g->win), drawing_area);
	gtk_widget_set_size_request(drawing_area, g->r->scene->res.x, g->r->scene->res.y);

	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), g);

	gtk_widget_show_all(g->win);
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
	r->update.ray_depth = 2;
	r->update.render = 0;
	r->rendering = 0;
	r->scene = NULL;
	r->d_scene = NULL;
	r->h_d_scene = NULL;
	r->d_pixel_map = NULL;
	r->h_d_scene = (t_scene *)malloc(sizeof(t_scene));
	printf("%p\n", r->h_d_scene);
}


int main(int ac, char **av)
{
	t_gtk_tools			g;

	g.filename = NULL;
	g.ac = ac;
	g.av = av;
	g.win = NULL;
	g.cr = NULL;
	if (ac >= 2)
		g.filename = ft_strdup(av[1]);
	main_gtk(&g);
	return (0);
}


void	*main_gtk(t_gtk_tools *g)
{
	GtkWidget       *window;
	GtkWidget		*widget;
	t_parse_tools		t;
	t_raytracing_tools	r;
	int					i;
	GtkCssProvider		*cssProvider;
	GdkRectangle	res;
	GtkAdjustment	*adj;

	gtk_init(&g->ac, &g->av);

	g->t = &t;
	g->r = &r;
	init_raytracing_tools(g->r);
	cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, CSS_PATH, NULL); //NULL instead of GError**
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
		GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g->builder = gtk_builder_new();
    gtk_builder_add_from_file (g->builder, "RT_glade.glade", NULL);
    gtk_builder_connect_signals(g->builder, g);
	if (g->filename)
		open_scene(g, NULL);
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "MenuItemQuit"));
	g_signal_connect(widget, "activate", G_CALLBACK(on_window_main_destroy), NULL);

	gdk_monitor_get_geometry(gdk_display_get_monitor(gdk_display_get_default(), 0), &res);

	adj = GTK_ADJUSTMENT(gtk_builder_get_object(g->builder, "AdjResolutionX"));
	gtk_adjustment_set_upper(adj, res.width);

	adj = GTK_ADJUSTMENT(gtk_builder_get_object(g->builder, "AdjResolutionY"));
	gtk_adjustment_set_upper(adj, res.height);

    window = GTK_WIDGET(gtk_builder_get_object(g->builder, "window_main"));
	gtk_widget_show(window);
    gtk_main();
	g->r->update.resolution = 2; // Function ?
	g->r->update.objects = 2;
	g->r->update.lights = 2;
	g->r->update.cameras = 2;
	g->r->update.scene = 2;
	g->r->update.ray_depth = 2;

	// cuda_free(&r);
    g_object_unref(g->builder);
	// free_scenes(r.scene);
	return (NULL);
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
	if (g->r->scene)
		cuda_free(g->r);
	g->r->scene = g->t->scenes;
	// g->r->scene->is_3d = 1;
	cuda_malloc(g->r);
	update_grid_scene(g);
	update_grid_objects(g);
	update_grid_lights(g);
	update_grid_cameras(g);
	// print_scenes(g->r->scene);
	// rt(g->r);
	g->r->update.resolution = 2;
	g->r->update.objects = 2;
	g->r->update.lights = 2;
	g->r->update.cameras = 2;
	g->r->update.scene = 2;
	g->r->update.ray_depth = 2;
	free_parse_tools(g->t);
	filechooser ? gtk_widget_destroy(filechooser) : 0;
	return (0);
}