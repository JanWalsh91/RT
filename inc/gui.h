/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:39:46 by tgros             #+#    #+#             */
/*   Updated: 2017/04/10 14:07:39 by jwalsh           ###   ########.fr       */
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
void 			*sig_open_scene(GtkWidget *menu_item, t_gtk_tools *g);
void			*sig_render(GtkWidget *widget, t_gtk_tools *g);

/*
** Objects GUI panel
*/

void			*update_objects_panel(t_gtk_tools *g); //Camel
void			*sig_update_current_object(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g);
void			update_objects_info_panel(t_gtk_tools *g, t_object *obj);
void			init_obj_look_at_combo_box(GtkWidget *widget, t_gtk_tools *g);
t_object		*get_selected_object(t_gtk_tools *);
void			*sig_update_obj_type(GtkWidget *ComboBox, t_gtk_tools *g);
void			*sig_update_obj_name(GtkWidget *GtkEntry, t_gtk_tools *g);
void			*sig_update_obj_pos_x(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_pos_y(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_pos_z(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_lookat_x(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_lookat_y(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_lookat_z(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_lookat_name(GtkWidget *ComboBox, t_gtk_tools *g);
void			*sig_update_obj_dir_x(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_dir_y(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_dir_z(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_color(GtkWidget *color_chooser, t_gtk_tools *g);
void			*sig_update_obj_ks(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_spec_exp(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_kd(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_kt(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_krefraction(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_kreflection(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_radius(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_height(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_obj_dir_normalize(GtkWidget *button, t_gtk_tools *g);

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
void			*sig_update_light_intensity(GtkWidget *SpeedButton, t_gtk_tools *g);



#endif
