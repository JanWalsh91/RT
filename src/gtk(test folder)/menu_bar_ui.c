/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bar_ui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:54:57 by tgros             #+#    #+#             */
/*   Updated: 2017/04/05 14:49:03 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

GtkWidget	*get_file_menu()
{
	GtkWidget	*filemenu;
    GtkWidget	*file;
	GtkWidget	*f_open;
	GtkWidget	*f_quit;

	filemenu = gtk_menu_new();
    file = gtk_menu_item_new_with_label("File");
	f_open = gtk_menu_item_new_with_label("Open");
	f_quit = gtk_menu_item_new_with_label("Quit");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), f_open);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), f_quit);

	return (file);
}

GtkWidget	*get_menu_bar()
{
	GtkWidget	*menu;

	GtkWidget	*editmenu;
	GtkWidget	*optsmenu;
	
	GtkWidget	*edit;
	GtkWidget	*options;
	
	GtkWidget	*paste;
	GtkWidget	*help;

	menu = gtk_menu_bar_new();
	editmenu = gtk_menu_new();
	optsmenu = gtk_menu_new();

	edit = gtk_menu_item_new_with_label("Edit");
	options = gtk_menu_item_new_with_label("Options");

	paste = gtk_menu_item_new_with_label("Paste");
	help = gtk_menu_item_new_with_label("Help");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit), editmenu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(options), optsmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), paste);
	gtk_menu_shell_append(GTK_MENU_SHELL(optsmenu), help);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), get_file_menu());
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), edit);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), options);

	return (menu);
}
