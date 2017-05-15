/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_generate_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 15:40:05 by tgros             #+#    #+#             */
/*   Updated: 2017/05/15 09:13:50 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_generated_texture_get_dimensions(GtkWidget *button, t_gtk_tools *g)
{
	t_object 	*obj;
	t_object	*tmp;
	GtkWidget	*widget;
	t_vec3		dim;
	t_pt2		dim_tmp;

	printf("Getting dimensions of generated texture");
	obj = get_selected_object(g);
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder_texture, "SpinButtonResolutionGeneratedTextureX"));
	dim.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder_texture, "SpinButtonResolutionGeneratedTextureY"));
	dim.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder_texture, "SpinButtonResolutionGeneratedPrecision"));
	dim.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
	if (obj->texture)
	{
		printf("Do something fucking idiot!\n"); // free, etc.
	}
	dim_tmp.x = dim.x;
	dim_tmp.y = dim.y;
	
	if (g->generate_id == 1)
	{
		obj->texture_name = ft_strdup("Perlin");
		tmp = is_texture_loaded(g->r->scene->objects, obj, "Perlin", dim_tmp);
		if (!tmp)
			obj->texture = generate_perlin_noise(&dim);
		else
			obj->texture = tmp->texture;
	}
	else if (g->generate_id == 2)
	{
		C(1)
		obj->texture_name = ft_strdup("Checkerboard");
		tmp = is_texture_loaded(g->r->scene->objects, obj, "Checkerboard", dim_tmp);
		C(2)
		if (!obj->texture)
			obj->texture = generate_checkerboard(&dim);
		else
			obj->texture = tmp->texture;
		C(3)
	}
	obj->texture_dim.x = (int)dim.x;
	obj->texture_dim.y = (int)dim.y;
	widget = GTK_WIDGET(gtk_builder_get_object(g->builder, "ComboBoxGeneratedTexture"));
	gtk_widget_set_sensitive(widget, false);
	gtk_widget_destroy(GTK_WIDGET(gtk_builder_get_object(g->builder_texture, "window_generate")));
	g->r->update.render = 1;
	g->r->update.objects = g->r->update.objects > 1 ? 2 : 1;
	if (g->win)
		gtk_widget_queue_draw(g->win);
	g->generate_id = 0;
	return (NULL);
}

void	*sig_generate_texture(GtkWidget *combo_box, t_gtk_tools *g)
{
	int			id;
	t_object 	*obj;
	GtkWidget	*widget;
    GtkBuilder	*builder;

	printf("sig_generate_texture\n");
	obj = get_selected_object(g);
	id = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));

	if (id == 0)
		return (NULL);
	g->generate_id = id;
	builder = gtk_builder_new_from_file("GenerateTexture.glade");
	gtk_builder_connect_signals(builder, g);
	widget = GTK_WIDGET(gtk_builder_get_object(builder, "window_generate"));
	g->builder_texture = builder;
	gtk_widget_show(widget);
	return (NULL);
}