/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:54:14 by tgros             #+#    #+#             */
/*   Updated: 2017/04/05 11:05:13 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

	//gtk_widget_set_sensitive (pos, FALSE); // Desactive un widget

void	whut(GtkWidget *pos_x, gpointer pos_y)
{
	gtk_widget_set_sensitive (GTK_WIDGET(pos_y), FALSE); // Desactive un widget
}

void	dewhut(GtkWidget *pos_z, gpointer pos_y)
{
	gtk_widget_set_sensitive (GTK_WIDGET(pos_y), TRUE); // Desactive un widget
}

GtkWidget	*get_modify_object_ui()
{
	// ==========================
	// D�clarations des variables
	// ==========================
	GtkWidget	*ui;
	// Position
	GtkWidget	*pos;
	GtkWidget	*pos_x;
	GtkWidget	*pos_y;
	GtkWidget	*pos_z;
	GtkAdjustment	*adj_pos_x;
	GtkAdjustment	*adj_pos_y;
	GtkAdjustment	*adj_pos_z;
	// Rotation
	GtkWidget	*rot;
	GtkWidget	*rot_x;
	GtkWidget	*rot_y;
	GtkWidget	*rot_z;
	GtkAdjustment	*adj_rot_x;
	GtkAdjustment	*adj_rot_y;
	GtkAdjustment	*adj_rot_z;
	
	// Size
	GtkWidget	*height;
	GtkWidget	*radius;
	GtkWidget	*height_v;
	GtkWidget	*radius_v;
	GtkAdjustment	*adj_height;
	GtkAdjustment	*adj_radius;
	
	// K*
	GtkWidget	*kd_l;
	GtkWidget	*ks_l;
	GtkWidget	*spec_exp_l;
	GtkWidget	*kd_v;
	GtkWidget	*ks_v;
	GtkWidget	*spec_exp_v;
	GtkAdjustment	*adj_kd;
	GtkAdjustment	*adj_ks;
	GtkAdjustment	*adj_spec_exp;

	// Color
	GtkWidget	*color_l;
	GtkWidget	*color;

	GtkWidget	*lst_obj;
	GtkWidget	*label1;
	GtkWidget	*label2;
	GtkWidget	*label3;

	// Separators
	GtkWidget	*sep1;

	// Textures file loader
	GtkWidget	*texture_l;
	GtkWidget	*texture_v;
	
	// ==========================
	// Instanciations
	// ==========================

	ui = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(ui), 10);
	gtk_grid_set_column_spacing(GTK_GRID(ui), 20);
	//gtk_grid_set_column_homogeneous(GTK_GRID(ui), 1);

	// Faire ca dans une loop, pour chaque objet. R�cup�rer le nom par d�faut, et le display.
	lst_obj = gtk_list_box_new();
	label1 = gtk_label_new("Sphere s1");
	label2 = gtk_label_new("Blue sphere");
	label3 = gtk_label_new("Uggly cylinder");
	gtk_list_box_prepend(GTK_LIST_BOX(lst_obj), label3);
	gtk_list_box_prepend(GTK_LIST_BOX(lst_obj), label2);
	gtk_list_box_prepend(GTK_LIST_BOX(lst_obj), label1);

	// #define for default values in the header file
	adj_pos_x = gtk_adjustment_new(0, -300, 300, 0.5, 0.5, 0);
	adj_pos_y = gtk_adjustment_new(0, -300, 300, 0.5, 0.5, 0);
	adj_pos_z = gtk_adjustment_new(0, -300, 300, 0.5, 0.5, 0);
	adj_rot_x = gtk_adjustment_new(0, -180, 180, 0.5, 0.5, 0);
	adj_rot_y = gtk_adjustment_new(0, -180, 180, 0.5, 0.5, 0);
	adj_rot_z = gtk_adjustment_new(0, -180, 180, 0.5, 0.5, 0);
	adj_kd = gtk_adjustment_new(0.5, 0, 1, 0.1, 0.1, 0);
	adj_ks = gtk_adjustment_new(0.5, 0, 1, 0.1, 0.1, 0);
	adj_spec_exp = gtk_adjustment_new(20, 2, 5000, 20, 20, 0);

	pos = gtk_label_new("Position");
	pos_x = gtk_spin_button_new(adj_pos_x, 0.5, 2);
	pos_y = gtk_spin_button_new(adj_pos_y, 0.5, 2);
	pos_z = gtk_spin_button_new(adj_pos_z, 0.5, 2);

	rot = gtk_label_new("Rotation");
	rot_x = gtk_spin_button_new(adj_rot_x, 0.5, 2);
	rot_y = gtk_spin_button_new(adj_rot_y, 0.5, 2);
	rot_z = gtk_spin_button_new(adj_rot_z, 0.5, 2);

	height = gtk_label_new("Height");
	radius = gtk_label_new("Radius");
	adj_height = gtk_adjustment_new(1, 0, 5000, 0.5, 0.5, 0);
	adj_radius = gtk_adjustment_new(1, 0, 5000, 0.5, 0.5, 0);
	height_v = gtk_spin_button_new(adj_height, 0.5, 2);
	radius_v = gtk_spin_button_new(adj_radius, 0.5, 2);


	kd_l = gtk_label_new("Kd");
	ks_l = gtk_label_new("Ks");
	spec_exp_l = gtk_label_new("Spec exp");

	kd_v = gtk_spin_button_new(adj_kd, 0.1, 2);
	ks_v = gtk_spin_button_new(adj_ks, 0.1, 2);
	spec_exp_v = gtk_spin_button_new(adj_spec_exp, 0.1, 2);

	sep1 = gtk_separator_new(GTK_ORIENTATION_VERTICAL);

	color_l = gtk_label_new("Color");
	color = gtk_color_button_new();

	texture_l = gtk_label_new("Texture");
	//texture_v = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_OPEN);
	texture_v = gtk_file_chooser_button_new("Texture", GTK_FILE_CHOOSER_ACTION_OPEN);

	g_signal_connect(pos_x, "value-changed", G_CALLBACK(whut), pos_y);
	g_signal_connect(pos_z, "value-changed", G_CALLBACK(dewhut), pos_y);


	// ==========================
	//	Ajout dans la grille
	// ==========================

	int line = -1;

	gtk_grid_set_column_homogeneous (GTK_GRID(ui), FALSE);

	gtk_grid_attach(GTK_GRID(ui), lst_obj, 0, ++line, 1, 10);

	gtk_grid_attach(GTK_GRID(ui), sep1, 1, line, 1, 10);

	gtk_grid_attach(GTK_GRID(ui), pos, 2, line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), pos_x, 3, line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), pos_y, 4, line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), pos_z, 5, line, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), rot, 2, ++line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), rot_x, 3, line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), rot_y, 4, line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), rot_z, 5, line, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), height, 2, ++line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), height_v, 3, line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), radius, 2, ++line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), radius_v, 3, line, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), kd_l, 2, ++line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), kd_v, 3, line, 1, 1);
	
	gtk_grid_attach(GTK_GRID(ui), ks_l, 2, ++line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), ks_v, 3, line, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), spec_exp_l, 2, ++line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), spec_exp_v, 3, line, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), color_l, 2, ++line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), color, 3, line, 1, 1);

	gtk_grid_attach(GTK_GRID(ui), texture_l, 2, ++line, 1, 1);
	gtk_grid_attach(GTK_GRID(ui), texture_v, 3, line, 1, 1);

	return (ui);
}