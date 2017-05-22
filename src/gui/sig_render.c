/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:43:54 by tgros             #+#    #+#             */
/*   Updated: 2017/05/21 17:20:46 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.cuh"
#include "../inc/gui.h"
#include "../inc/cuda_call.h"
#include "cuda_runtime.h"


static void	increment_tile(t_pt2 *tileId, int tile_col);

void 		*sig_render(GtkWidget *widget, t_gtk_tools *g)
{
	t_object 		*obj;
	GtkWidget		*widget2;
	GtkAccelGroup 	*accel_group;
	GClosure		*closure;
	GdkRectangle	res;

	g->r->update.render = 1;
	update_camera_ctw(g->r->scene->cameras);
	widget2 = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder), "ButtonObjectDirNormalize"));
	if (gtk_widget_get_sensitive (widget2))
	{
		obj = get_selected_object(g);
		if (obj != NULL)
		{
			obj->dir = v_norm(obj->dir);
			update_objects_info_panel(g, obj);
			gtk_widget_set_sensitive (widget2, FALSE);
		}
	}
	g->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(g->win, "destroy", G_CALLBACK(window_destroy), g);
	closure = g_cclosure_new(G_CALLBACK(window_destroy_esc), g, 0);
    accel_group = gtk_accel_group_new();
    gtk_accel_group_connect(accel_group, GDK_KEY_Escape, 0, 0, closure);
	gtk_window_add_accel_group(GTK_WINDOW(g->win), accel_group);
	
	g->drawing_area = gtk_drawing_area_new();
	gtk_container_add (GTK_CONTAINER (g->win), g->drawing_area);
	gtk_widget_set_size_request(g->drawing_area, g->r->scene->res.x, g->r->scene->res.y);
	// gtk_window_set_resizable (GTK_WINDOW(g->win), false);
	g_signal_connect(G_OBJECT(g->drawing_area), "draw", G_CALLBACK(draw_callback), g);
	gdk_monitor_get_geometry(gdk_display_get_monitor(gdk_display_get_default(), 0), &res);
	gtk_window_set_gravity (GTK_WINDOW(g->win), GDK_GRAVITY_EAST);
	gtk_window_move (GTK_WINDOW(g->win), res.width - g->r->scene->res.x - 100, res.height - g->r->scene->res.y - 150);
	// printf("%d, %d\n", res.width, res.height);
	gtk_widget_show_all(g->win);
	return (NULL);
}

static void	increment_tile(t_pt2 *tileId, int tile_row)
{
	if (++tileId->x >= tile_row)
	{
		tileId->x = 0;
		++tileId->y;
	}
}

void	*render_wrapper(gpointer data)
{
	t_gtk_tools	*g;
	t_pt2		tileId;
	int			max_tile;
	int			tile_row;
	int			tile_col;

	printf("render_wrapper\n");
	g = (t_gtk_tools *)data;
	// g->r->settings.tile_size = 32 * 9;
	if (g->r->update.resolution)
		g->pixbuf = gdk_pixbuf_new_from_data((unsigned char *)g->r->d_pixel_map, GDK_COLORSPACE_RGB, 0, 8, g->r->scene->res.x, g->r->scene->res.y, g->r->scene->res.x * 3, NULL, NULL);
	tileId.x = 0;
	tileId.y = 0;
	tile_row = (g->r->scene->res.x / g->r->settings.tile_size) + ((g->r->scene->res.x % g->r->settings.tile_size) ? 1 : 0);
	tile_col = (g->r->scene->res.y / g->r->settings.tile_size) + ((g->r->scene->res.y % g->r->settings.tile_size) ? 1 : 0);
	max_tile = tile_row * tile_col;
	// printf("rows: %d cols: %d total: %d\n", tile_row, tile_col, max_tile);
	cuda_malloc(g->r);
	if (g->r->scene->is_photon_mapping)
	{
		update_photon_map(g->r); //CAUSES INVALID DEVICE POINTER ERROR
		printf("-----%p and %p\n", g->r->scene->photon_map, g->r->h_d_scene->photon_map);
		g->r->h_d_scene->photon_map = g->r->scene->photon_map;
		printf("-----%p and %p\n", g->r->scene->photon_map, g->r->h_d_scene->photon_map);
		cudaMemcpy(g->r->d_scene, g->r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice);
		printf("-----%p and %p\n", g->r->scene->photon_map, g->r->h_d_scene->photon_map);
	}
	while (g->win && (tileId.y + 1) <= tile_col)
	{ 
		render(g->r, tileId); 
		increment_tile(&tileId, tile_row);
		g->pixbuf = gdk_pixbuf_new_from_data((unsigned char *)g->r->d_pixel_map, GDK_COLORSPACE_RGB, 0, 8, g->r->scene->res.x, g->r->scene->res.y, g->r->scene->res.x * 3, NULL, NULL);
		gtk_widget_queue_draw(g->win);
	}
	g->r->rendering = 0;
	return (FALSE);
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, t_gtk_tools *g)
{
	if (!g->cr)
	{
		// fill background with black
		g->cr = cr;
	}
	if (g->r->update.render == 1 && !g->r->rendering)
	{
		// printf("Create a new thread\n");
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