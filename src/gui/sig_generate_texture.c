/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_generate_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 15:40:05 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 14:01:11 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	update_gui_texture(t_gtk_tools *g);
static void	adapt_texture_dim(t_vec3 *dim);
static void	generate_texture(t_gtk_tools *g, t_object *obj, t_vec3 *dim,
														t_vec3 *dim_tmp);

void		*sig_generated_texture_get_dimensions(GtkWidget *button,
													t_gtk_tools *g)
{
	t_object	*obj;
	GtkWidget	*widget;
	t_vec3		dim;
	t_vec3		dim_tmp;

	(void)button;
	printf("Getting dimensions of generated texture");
	obj = get_selected_object(g);
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder_texture,
						"SpinButtonResolutionGeneratedTextureX"));
	dim.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder_texture,
						"SpinButtonResolutionGeneratedTextureY"));
	dim.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder_texture,
						"SpinButtonResolutionGeneratedPrecision"));
	dim.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	dim_tmp.x = dim.x;
	dim_tmp.y = dim.y;
	generate_texture(g, obj, &dim, &dim_tmp);
	obj->texture_dim = dim;
	update_gui_texture(g);
	return (NULL);
}

static void	generate_texture(t_gtk_tools *g, t_object *obj, t_vec3 *dim,
														t_vec3 *dim_tmp)
{
	t_object	*tmp;

	if (g->generate_id == 1)
	{
		obj->texture_name = ft_strdup("Perlin");
		tmp = find_texture(g->r->scene->objects, obj, "Perlin", *dim_tmp);
		obj->texture = !tmp ? generate_perlin_noise(dim) : tmp->texture;
	}
	else if (g->generate_id == 2)
	{
		obj->texture_name = ft_strdup("Checkerboard");
		tmp = find_texture(g->r->scene->objects, obj, "Checkerboard", *dim_tmp);
		adapt_texture_dim(dim);
		obj->texture = !tmp ? generate_checkerboard(dim) : tmp->texture;
	}
	else if (g->generate_id == 3)
	{
		obj->texture_name = ft_strdup("Noise");
		tmp = find_texture(g->r->scene->objects, obj, "Noise", *dim_tmp);
		obj->texture = !tmp ? generate_noise(dim) : tmp->texture;
	}
}

static void	adapt_texture_dim(t_vec3 *dim)
{
	while ((int)dim->x % (int)dim->z != 0)
		dim->x++;
	dim->x += (((int)dim->x / (int)dim->z) % 2 == 1) ? dim->z : 0;
	while ((int)dim->y % (int)dim->z != 0)
		dim->y++;
	dim->y += (((int)dim->y / (int)dim->z) % 2 == 1) ? dim->z : 0;
}

static void	update_gui_texture(t_gtk_tools *g)
{
	GtkWidget	*widget;
	GtkBuilder	*b;

	b = GTK_BUILDER(g->builder);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "ComboBoxGeneratedTexture"));
	gtk_widget_set_sensitive(widget, false);
	gtk_widget_destroy(GTK_WIDGET(gtk_builder_get_object(g->builder_texture,
													"window_generate")));
	g->r->update.render = 1;
	g->r->update.objects = g->r->update.objects > 1 ? 2 : 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
	g->generate_id = 0;
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonObjectTextureX"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "SpinButtonObjectTextureY"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b,
									"SpinButtonObjectTextureTranslateX"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b,
									"SpinButtonObjectTextureTranslateY"));
	gtk_widget_set_sensitive(widget, true);
	widget = GTK_WIDGET(gtk_builder_get_object(b, "FileChooserTexture"));
	gtk_widget_set_sensitive(widget, false);
}

void		*sig_generate_texture(GtkWidget *combo_box, t_gtk_tools *g)
{
	int				id;
	t_object		*obj;
	GtkWidget		*widget;
	GtkAdjustment	*adj;
	GtkBuilder		*builder;

	printf("sig_generate_texture\n");
	obj = get_selected_object(g);
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
	if (id == 0)
		return (NULL);
	g->generate_id = id;
	builder = gtk_builder_new_from_file(GENERATE_TEXTURE_GLADE);
	gtk_builder_connect_signals(builder, g);
	adj = GTK_ADJUSTMENT(gtk_builder_get_object(builder,
									"AdjTexturePrecision"));
	gtk_adjustment_set_lower(adj, id == 3 ? 0.01 : 10);
	gtk_adjustment_set_upper(adj, id == 3 ? 100 : 2000);
	widget = GTK_WIDGET(gtk_builder_get_object(builder, "window_generate"));
	gtk_window_set_transient_for(GTK_WINDOW(widget), GTK_WINDOW(
				gtk_builder_get_object(g->builder, "window_main")));
	g->builder_texture = builder;
	gtk_widget_show(widget);
	return (NULL);
}
