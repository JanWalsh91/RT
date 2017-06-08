/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 09:41:30 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.cuh"
#include "../inc/gui.h"
#include "../inc/cuda_call.h"
#include <cuda_runtime.h>
#include <time.h>

static void		init_raytracing_tools(t_raytracing_tools *r);
static void		init_window(t_gtk_tools *g);

int				main(int ac, char **av)
{
	t_gtk_tools			g;
	t_parse_tools		t;
	t_raytracing_tools	r;

	srand(time(NULL));
	if (ac > 2)
		ft_error_exit(USAGE);
	g.ac = ac;
	g.av = av;
	g.win = NULL;
	g.drawing_area = NULL;
	g.cr = NULL;
	g.updating_gui = 0;
	g.t = &t;
	g.r = &r;
	g.pixbuf = NULL;
	g.r->settings.tile_size = DEFAULT_TILE_SIZE;
	// g.r->settings.photon_search_radius = PHOTON_SEARCH_RADIUS;
	g.r->settings.photon_search_radius = 5;
	g.filename = (ac >= 2) ? ft_strdup(av[1]) : NULL;
	main_gtk(&g);
	return (0);
}

void			*main_gtk(t_gtk_tools *g)
{
	gtk_init(&g->ac, &g->av);
	init_raytracing_tools(g->r);
	build_gui(g);
	init_window(g);
	(g->filename) ? open_scene(g, NULL) : 0;
	gtk_main();
	clean_exit(g);
	while (g->r->rendering)
		;
	return (NULL);
}

static void		init_raytracing_tools(t_raytracing_tools *r)
{
	r->update.resolution = 2;
	r->update.objects = 2;
	r->update.lights = 2;
	r->update.cameras = 2;
	r->update.scene = 2;
	r->update.ray_depth = 2;
	r->update.photon_map = 2;
	r->update.render = 0;
	r->rendering = 0;
	r->scene = NULL;
	r->d_scene = NULL;
	r->h_d_scene = NULL;
	r->d_pixel_map = NULL;
	r->h_region_map = NULL;
	r->d_region_map = NULL;
	if (!(r->h_d_scene = (t_scene *)malloc(sizeof(t_scene))))
		ft_error_exit("Malloc error.");
}

static void	init_window(t_gtk_tools *g)
{
	GtkWidget		*window;
	GtkWidget		*widget;
	GtkAdjustment	*adj;
	GdkRectangle	res;

	widget = get_widget(g, "MenuItemQuit");
	g_signal_connect(widget, "activate", G_CALLBACK(on_window_main_destroy),
						NULL);
	gdk_monitor_get_geometry(gdk_display_get_monitor(
			gdk_display_get_default(), 0), &res);
	adj = GTK_ADJUSTMENT(get_widget(g, "AdjResolutionX"));
	gtk_adjustment_set_upper(adj, res.width);
	adj = GTK_ADJUSTMENT(get_widget(g, "AdjResolutionY"));
	gtk_adjustment_set_upper(adj, res.height);
	window = get_widget(g, "window_main");
	gtk_widget_show(window);
	g_timeout_add_seconds(1, update_available_memory, g);
	gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
}

void	build_gui(t_gtk_tools *g)
{
	GtkCssProvider		*css_provider;

	css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css_provider, CSS_PATH, NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
		GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	g->builder = gtk_builder_new_from_file(RT_GLADE);
	gtk_builder_connect_signals(g->builder, g);
}

int	clean_exit(t_gtk_tools *g)
{
	cuda_free(g->r, 1);
	g_object_unref(g->builder);
	free_scene(g->r->scene);
	return (1);
}
