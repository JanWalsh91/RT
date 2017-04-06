/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:54:01 by tgros             #+#    #+#             */
/*   Updated: 2017/04/03 12:00:57 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static GtkWidget	*get_all_ui()
{
	GtkWidget	*tab;
	GtkWidget	*modify_obj_l;
	GtkWidget	*add_object;
	GtkWidget	*test2;
	GtkWidget	*grid;


	tab = gtk_notebook_new();
	grid = gtk_grid_new();

	modify_obj_l = gtk_label_new("Modify objects");
	add_object = gtk_label_new("Add object");
	test2 = gtk_label_new("Test");
	
	gtk_notebook_append_page(GTK_NOTEBOOK(tab), get_scene_ui(), gtk_label_new("Scene"));
	gtk_notebook_append_page(GTK_NOTEBOOK(tab), get_modify_object_ui(), modify_obj_l);
	gtk_notebook_append_page(GTK_NOTEBOOK(tab), test2, add_object);


	gtk_grid_attach(GTK_GRID(grid), get_menu_bar(), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), tab, 0, 1, 1, 1);


	//gtk_notebook_set_tab_pos(GTK_NOTEBOOK(tab), 1);
	return (grid);
}

static void activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget	*window;
	GtkWidget	*tab;

	window = gtk_application_window_new(app);
	tab = get_all_ui();

	gtk_window_set_title(GTK_WINDOW(window), "RT properties");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);
	gtk_container_add(GTK_CONTAINER(window), tab);
	// gtk_window_move (GTK_WINDOW(window), 1000, 1000); // Changer la position initiale de la fenetre. Essayer peut etre de la mettre sur le bord gauche, un peu decolle
	gtk_widget_show_all(window);
}

GMenuModel	*get_menu_model()
{
	GMenuModel	*menu_model;

	menu_model = G_MENU_MODEL(g_menu_new());

	return (menu_model);
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	gtk_application_set_app_menu(app, get_menu_model());
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}
