/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_new_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 13:54:20 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 14:14:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "cuda_call.cuh"

static void	set_default_values_scene(t_gtk_tools *g);
static void	set_default_values_camera(t_gtk_tools *g);
static void	free_old_scene(t_gtk_tools *g);
static void	update_gui(t_gtk_tools *g);

void		*sig_new_scene(GtkWidget *menu_item, t_gtk_tools *g)
{
	GtkWidget	*widget;

	(void)menu_item;
	free_old_scene(g);
	if (!(g->r->scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	set_default_values_scene(g);
	if (!(g->r->scene->cameras = (t_camera *)ft_memalloc(sizeof(t_camera))))
		ft_error_exit("Malloc error.");
	set_default_values_camera(g);
	widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(g->builder),
														"NoteBookMenu"));
	gtk_widget_set_visible(widget, TRUE);
	g->r->update.cameras = 2;
	g->r->update.scene = 2;
	if (cuda_malloc(g->r) == false)
		return (0);
	update_gui(g);
	return (NULL);
}

static void	update_gui(t_gtk_tools *g)
{
	GtkWidget	*widget;

	update_grid_scene(g);
	gtk_container_foreach(GTK_CONTAINER(gtk_builder_get_object(GTK_BUILDER(
				g->builder), "ListBoxObjects")),
				(GtkCallback)G_CALLBACK(gtk_widget_destroy), NULL);
	update_grid_lights(g);
	update_grid_cameras(g);
	populate_list_box_objects(g);
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder,
									"ScrollWindowObject"));
	gtk_widget_set_sensitive(widget, false);
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder,
										"ScrollWindowLight"));
	gtk_widget_set_sensitive(widget, false);
}

static void	free_old_scene(t_gtk_tools *g)
{
	if (g->filename)
	{
		g_free(g->filename);
		g->filename = NULL;
	}
	if (g->r->scene)
	{
		cuda_free(g->r, 1);
		free_scene(g->r->scene);
	}
	if (g->win)
		gtk_widget_destroy(g->win);
}

static void	set_default_values_scene(t_gtk_tools *g)
{
	g->r->scene->res.x = DEFAULT_RES_W;
	g->r->scene->res.y = DEFAULT_RES_H;
	g->r->scene->ray_depth = DEFAULT_RAY_DEPTH;
	g->r->scene->objects = NULL;
	g->r->scene->cameras = NULL;
	g->r->scene->lights = NULL;
	g->r->scene->background_color = v_new(0, 0, 0);
	g->r->scene->ambient_light_color = v_new(255, 255, 255);
	g->r->scene->ka = 0.1;
	g->r->scene->image_aspect_ratio = 1;
	g->r->scene->name = NULL;
	g->r->scene->is_diffuse = true;
	g->r->scene->is_shadow = true;
	g->r->scene->is_specular = true;
	g->r->scene->is_fresnel = true;
	g->r->scene->is_raytracing = true;
	g->r->scene->is_photon_mapping = false;
	g->r->scene->photon_kd_tree = NULL;
	g->r->scene->is_aa = 1;
}

static void	set_default_values_camera(t_gtk_tools *g)
{
	g->r->scene->cameras->name = ft_strdup("New Camera");
	g->r->scene->cameras->dir.z = 1.0;
	g->r->scene->cameras->prev = NULL;
	g->r->scene->cameras->next = NULL;
	g->r->scene->cameras->fov = 45;
	g->r->scene->cameras->filter = 0;
	g->r->scene->cameras->ior = 1.01;
}
