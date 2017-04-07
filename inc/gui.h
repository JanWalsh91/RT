/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:39:46 by tgros             #+#    #+#             */
/*   Updated: 2017/04/07 18:06:27 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

#include "rt.cuh"
#include <gtk/gtk.h>

/*
**
*/

typedef struct	s_gtk_tools
{
	struct s_parse_tools 		*t;
	struct s_raytracing_tools 	*r;
	struct _GtkBuilder 	*builder;
}				t_gtk_tools;

/*
** Scene GUI panel
*/

void			*sig_update_res_x(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_res_y(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_udpate_ambient_light_color(GtkWidget *color_chooser, t_gtk_tools *g);
void			*sig_update_ambient_light_coeff(GtkWidget *spin_button, t_gtk_tools *g);
void 			*update_scene_panel(t_gtk_tools *g);

/*
** Objects GUI panel
*/

void			*update_objects_panel(t_gtk_tools *g); //Camel
void			*sig_update_current_object(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g);
void			update_objects_info_panel(t_gtk_tools *g, t_object *obj);

/*
** Lights GUI panel
*/

void			*update_lights_panel(t_gtk_tools *g); //Camel
void			update_lights_info_panel(t_gtk_tools *g, t_light *light);

void			*sig_update_current_light(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g);
void			*sig_update_light_pos_x(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_light_pos_y(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_light_pos_z(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_light_dir_x(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_light_dir_y(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_light_dir_z(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_light_rot_x(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_light_rot_y(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_light_rot_z(GtkWidget *SpeedButton, t_gtk_tools *g);
void			*sig_update_light_color(GtkWidget *color_chooser, t_gtk_tools *g);
void			*sig_update_light_intensity(GtkWidget *color_chooser, t_gtk_tools *g);




#endif
