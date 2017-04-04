/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:53:19 by tgros             #+#    #+#             */
/*   Updated: 2017/03/30 10:55:18 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

#include <gtk/gtk.h>

GtkWidget	*get_scene_ui();
GtkWidget	*get_modify_object_ui();
GtkWidget	*get_menu_bar();

#endif