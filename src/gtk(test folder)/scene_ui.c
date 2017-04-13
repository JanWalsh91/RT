/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:53:00 by tgros             #+#    #+#             */
/*   Updated: 2017/03/30 11:23:44 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

GtkWidget	*get_scene_ui()
{
	// ==========================
	// D�clarations des variables
	// ==========================
	GtkWidget	*ui;

	GtkWidget	*name_l;
	GtkWidget	*rt_l;
	GtkWidget	*name_v;

	GtkWidget	*res_l;
	GtkWidget	*res_x;
	GtkWidget	*res_y;
	GtkAdjustment	*adj_x;
	GtkAdjustment	*adj_y;

	GtkWidget	*ka_l;
	GtkWidget	*ka_v;
	GtkAdjustment	*ka_adj;
	GtkWidget	*ka_color_l;
	GtkWidget	*ka_color;

	GtkWidget	*recur_l;
	GtkWidget	*recur_v;
	GtkAdjustment	*recur_adj;

	GtkWidget	*filter_l;
	GtkWidget	*filter_v;

	GdkRGBA		default_color;

	// ==========================
	// Instanciations
	// ==========================
	ui = gtk_grid_new();

	name_l = gtk_label_new("Scene name");
	name_v = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(name_v), 20); // constante + add .rt at the end
	rt_l = gtk_label_new(".rt");
	gtk_widget_set_halign(rt_l, GTK_ALIGN_START); // justify on the left for one single line

	res_l = gtk_label_new("Resolution");
	adj_x = gtk_adjustment_new(150, 100, 2500, 10, 10, 0);
	adj_y = gtk_adjustment_new(150, 100, 2500, 10, 10, 0);
	res_x = gtk_spin_button_new(adj_x, 0, 0);
	res_y = gtk_spin_button_new(adj_y, 0, 0);

	ka_l = gtk_label_new("Ka");
	ka_adj = gtk_adjustment_new(0.1, 0, 1, 0.1, 0.1, 0);
	ka_v = gtk_spin_button_new(ka_adj, 0.1, 2);

	ka_color_l = gtk_label_new("Ambiant color");
	ka_color = gtk_color_button_new();

	recur_l = gtk_label_new("Recursion");
	recur_adj = gtk_adjustment_new(5, 1, 50, 1, 1, 0);
	recur_v = gtk_spin_button_new(recur_adj, 3, 0);

	default_color.red = 1;
	default_color.green = 1;
	default_color.blue = 1;
	default_color.alpha = 1;
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(ka_color), &default_color); // TODO with internet

	filter_l = gtk_label_new("Filter");
	filter_v = gtk_combo_box_text_new();
	// TODO: loop with the API to get every filter
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filter_v), "None", "None");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filter_v), "Sepia", "Sepia");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filter_v), "Black and white", "Black and white");

	// ==========================
	// Placement sur la grille
	// ==========================
	gtk_grid_set_row_spacing(GTK_GRID(ui), 10);
	gtk_grid_set_column_spacing(GTK_GRID(ui), 20);

	gtk_grid_attach(GTK_GRID(ui), name_l, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), name_v, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), rt_l, 2, 0, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), res_l, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), res_x, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), res_y, 2, 1, 1, 1);
	
	gtk_grid_attach(GTK_GRID(ui), ka_l, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), ka_v, 1, 2, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), ka_color_l, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), ka_color, 1, 3, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), recur_l, 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), recur_v, 1, 4, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), filter_l, 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), filter_v, 1, 5, 1, 1);
	return (ui);
}