/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:43:54 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 17:50:48 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.cuh"
#include <cuda_runtime.h>

static void	init_render_window(t_gtk_tools *g);
void		get_cartoon_effect(struct s_raytracing_tools *r);

void		*sig_render(GtkWidget *widget, t_gtk_tools *g)
{
	t_object		*obj;

	g->r->update.render = 1;
	update_camera_ctw(g->r->scene->cameras);
	widget = get_widget(g, "ButtonObjectDirNormalize");
	if (gtk_widget_get_sensitive(widget))
	{
		obj = get_selected_object(g);
		if (obj != NULL)
		{
			obj->dir = v_norm(obj->dir);
			update_objects_info_panel(g, obj);
			gtk_widget_set_sensitive(widget, FALSE);
		}
	}
	if (!g->win)
		init_render_window(g);
	return (NULL);
}

static void	init_render_window(t_gtk_tools *g)
{
	GtkAccelGroup	*accel_group;
	GClosure		*closure;
	GdkRectangle	res;
	t_pt2			s_res;

	s_res = g->r->scene->res;
	g->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(g->win, "destroy", G_CALLBACK(window_destroy), g);
	closure = g_cclosure_new(G_CALLBACK(window_destroy_esc), g, 0);
	accel_group = gtk_accel_group_new();
	gtk_accel_group_connect(accel_group, GDK_KEY_Escape, 0, 0, closure);
	gtk_window_add_accel_group(GTK_WINDOW(g->win), accel_group);
	g->drawing_area = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(g->win), g->drawing_area);
	gtk_widget_set_size_request(g->drawing_area, s_res.x, s_res.y);
	g_signal_connect(G_OBJECT(g->drawing_area), "draw",
							G_CALLBACK(draw_callback), g);
	gdk_monitor_get_geometry(gdk_display_get_monitor(
							gdk_display_get_default(), 0), &res);
	gtk_window_set_gravity(GTK_WINDOW(g->win), GDK_GRAVITY_EAST);
	gtk_window_move(GTK_WINDOW(g->win), res.width - s_res.x - 100,
							res.height - s_res.y - 150);
	gtk_widget_show_all(g->win);
}

void		render_tile(t_gtk_tools *g, t_tile tile)
{
	while (g->win && tile.id.x != tile.col && tile.id.y != tile.row)
	{
		get_region_map_tile(g->r, tile);
		render(g->r, tile);
		copy_region_map_tile(g->r, tile);
		ft_memcpy(gdk_pixbuf_get_pixels(g->pixbuf), g->r->d_pixel_map,
			g->r->scene->res.x * 3 * g->r->scene->res.y);
		g->win ? gtk_widget_queue_draw(g->win) : 0;
		increment_tile(&tile.id, tile.col);
	}
	if (g->win)
	{
		get_flares(g->r);
		ft_memcpy(gdk_pixbuf_get_pixels(g->pixbuf), g->r->d_pixel_map,
			g->r->scene->res.x * 3 * g->r->scene->res.y);
		g->win ? gtk_widget_queue_draw(g->win) : 0;
	}
	if (g->r->scene->is_photon_mapping)
		render_ppm(g, tile);
}

void		*render_wrapper(gpointer data)
{
	t_gtk_tools	*g;
	t_tile		tile;

	g = (t_gtk_tools *)data;
	init_tile(&tile, g);
	if (g->r->update.resolution)
	{
		g->pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8,
				g->r->scene->res.x, g->r->scene->res.y);
		gdk_pixbuf_fill(g->pixbuf, 0);
	}
	if (!cuda_malloc(g->r))
		return (NULL);
	malloc_region_map(g->r, tile);
	cuda_malloc_region_map_tile(g->r, tile);
	render_tile(g, tile);
	if (g->r->scene->is_cartoon_effect)
	{
		get_cartoon_effect(g->r);
		ft_memcpy(gdk_pixbuf_get_pixels(g->pixbuf), g->r->d_pixel_map,
			g->r->scene->res.x * 3 * g->r->scene->res.y);
		gtk_widget_queue_draw(g->win);
	}
	g->r->rendering = 0;
	return (NULL);
}

gboolean	draw_callback(GtkWidget *widget, cairo_t *cr, t_gtk_tools *g)
{
	(void)widget;
	if (!g->cr)
		g->cr = cr;
	if (g->r->update.render == 1 && !g->r->rendering)
	{
		g->r->update.render = 0;
		g->r->rendering = 1;
		g_thread_new("Thread_Render_Wrapper", render_wrapper, g);
	}
	if (g->pixbuf)
	{
		gdk_cairo_set_source_pixbuf(g->cr, g->pixbuf, 0, 0);
		cairo_paint(g->cr);
	}
	return (false);
}
