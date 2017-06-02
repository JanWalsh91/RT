/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:43:54 by tgros             #+#    #+#             */
/*   Updated: 2017/06/01 17:15:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.cuh"
#include "../inc/gui.h"
#include "../inc/cuda_call.h"
#include "cuda_runtime.h"
#include "photon_mapping.h"

static void	normalize_object_dir(t_gtk_tools *g);
static void	init_render_window(t_gtk_tools *g);
static void	init_tile(t_tile *tile, t_gtk_tools *g);

void 		*sig_render(GtkWidget *widget, t_gtk_tools *g)
{
	(void)widget;
	g->r->update.render = 1;
	update_camera_ctw(g->r->scene->cameras);
	normalize_object_dir(g);
	if (!g->win)
		init_render_window(g);
	return (NULL);
}

static void	normalize_object_dir(t_gtk_tools *g)
{
	GtkWidget		*widget;
	t_object 		*obj;

	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	if (gtk_widget_get_sensitive (widget))
	{
		obj = get_selected_object(g);
		if (obj != NULL)
		{
			obj->dir = v_norm(obj->dir);
			update_objects_info_panel(g, obj);
			gtk_widget_set_sensitive (widget, FALSE);
		}
	}
}

static void	init_render_window(t_gtk_tools *g)
{
	GtkAccelGroup 	*accel_group;
	GClosure		*closure;
	GdkRectangle	res;
	
	g->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(g->win, "destroy", G_CALLBACK(window_destroy), g);
	closure = g_cclosure_new(G_CALLBACK(window_destroy_esc), g, 0);
    accel_group = gtk_accel_group_new();
    gtk_accel_group_connect(accel_group, GDK_KEY_Escape, 0, 0, closure);
	gtk_window_add_accel_group(GTK_WINDOW(g->win), accel_group);
	g->drawing_area = gtk_drawing_area_new();
	gtk_container_add (GTK_CONTAINER (g->win), g->drawing_area);
	gtk_widget_set_size_request(g->drawing_area, g->r->scene->res.x, g->r->scene->res.y);
	g_signal_connect(G_OBJECT(g->drawing_area), "draw", G_CALLBACK(draw_callback), g);
	gdk_monitor_get_geometry(gdk_display_get_monitor(gdk_display_get_default(), 0), &res);
	gtk_window_set_gravity (GTK_WINDOW(g->win), GDK_GRAVITY_EAST);
	gtk_window_move (GTK_WINDOW(g->win), res.width - g->r->scene->res.x - 100, res.height - g->r->scene->res.y - 150);
	gtk_widget_show_all(g->win);
}


void	*render_wrapper(gpointer data)
{
	t_gtk_tools	*g;
	t_tile 		tile;

	printf("render_wrapper\n");
	
	g = (t_gtk_tools *)data;
	init_tile(&tile, g);
	if (g->r->update.resolution)
		g->pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, 0, 8, g->r->scene->res.x, g->r->scene->res.y);
	cuda_malloc(g->r);
	malloc_region_map(g->r, tile);
	cuda_malloc_region_map_tile(g->r, tile);
	printf("raytracing pass:\n");
	while (g->win && (tile.id.y + 1) <= tile.col)
	{ 
		// printf("pre copy: %f\n", g->r->h_region_map[0]->radius);
		get_region_map_tile(g->r, tile);
		render(g->r, tile);
		copy_region_map_tile(g->r, tile);
		increment_tile(&tile.id, tile.row);
	}
	if (g->win)
	{
		lens_flare_wrapper(g->r);
		ft_memcpy(gdk_pixbuf_get_pixels(g->pixbuf), g->r->d_pixel_map, g->r->scene->res.x * 3 * g->r->scene->res.y);
		gtk_widget_queue_draw(g->win);
	}
	//call on the photon mapping pass and radiance estimation pass in loop.
	if (g->r->scene->is_photon_mapping)
		render_ppm(g, tile);
	g->r->rendering = 0;
	return (false);
}

static void	init_tile(t_tile *tile, t_gtk_tools *g)
{
	tile->size = g->r->settings.tile_size;
	tile->id.x = 0;
	tile->id.y = 0;
	tile->row = (g->r->scene->res.x / tile->size) + ((g->r->scene->res.x % tile->size) ? 1 : 0);
	tile->col = (g->r->scene->res.y / tile->size) + ((g->r->scene->res.y % tile->size) ? 1 : 0);
	tile->max = tile->row * tile->col;
	printf("init_tile: size: [%d], id: [%d, %d], row: %d, col: %d, max: %d\n", tile->size, tile->id.x, tile->id.y, tile->row, tile->col, tile->max);
}

void	increment_tile(t_pt2 *tileId, int tile_row)
{
	if (++tileId->x >= tile_row)
	{
		tileId->x = 0;
		++tileId->y;
	}
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, t_gtk_tools *g)
{
	(void)widget;
	if (!g->cr)
		g->cr = cr;
	if (g->r->update.render == 1 && !g->r->rendering)
	{
		g->r->update.render = 0;
		g->r->rendering = 1;
		g_thread_new ("Swaggy_turkey", render_wrapper, g);
	}
	if (g->pixbuf)
	{
		gdk_cairo_set_source_pixbuf(g->cr, g->pixbuf, 0, 0);
		cairo_paint(g->cr);
	}
	return FALSE;
}