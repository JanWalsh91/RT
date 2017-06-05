/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:39:46 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 12:15:58 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# define SAVE_FLOAT_PRECISION 4

# include "rt.cuh"
# include <gtk/gtk.h>

/*
**
*/

typedef struct	s_gtk_tools
{
	struct s_parse_tools		*t;
	struct s_raytracing_tools	*r;
	GtkWidget					*win;
	GtkWidget					*drawing_area;
	char						*filename; //current open file
	struct _GtkBuilder 			*builder;
	struct _GtkBuilder 			*builder_texture;
	int							ac;
	char						**av;
	GdkPixbuf					*pixbuf;
	cairo_t						*cr;
	size_t						stack_size;
	bool						updating_gui;
	char						generate_id;
	t_vec3						old_dir;
	GtkCssProvider				*font_size;
}				t_gtk_tools;

/*
** Menu Item
*/

void			*main_gtk(t_gtk_tools *g);
void			build_gui(t_gtk_tools *g);
int				clean_exit(t_gtk_tools *g);
int				open_scene(t_gtk_tools *g, GtkWidget *filechooser);
void 			*sig_open_scene(GtkWidget *menu_item, t_gtk_tools *g);
void			*sig_save(GtkWidget *menu_item, t_gtk_tools *g);
void			*sig_save_as(GtkWidget *menu_item, t_gtk_tools *g);
void   			*sig_open_settings(GtkWidget *menu_item, t_gtk_tools *g);
gboolean		update_available_memory(gpointer data);
/*
** Render Functions
*/

void 			*sig_render(GtkWidget *widget, t_gtk_tools *g);
gboolean 		draw_callback(GtkWidget *widget, cairo_t *cr, t_gtk_tools *g);
void			*render_wrapper(gpointer data);
void			init_tile(t_tile *tile, t_gtk_tools *g);


/*
** Save Functions
*/

char     	 	*get_new_filename(t_gtk_tools *g);
void			save_scene(int fd, t_scene *scene);
void			save_object(int fd, t_object *obj, t_object *objects);
void			save_camera(int fd, t_camera *cam);
void			save_light(int fd, t_light *light);
void			write_vector(int fd, t_vec3 vec);
void			write_int(int fd, int i);
void			write_float(int fd, float d);
void			*sig_export_scene_bmp(GtkWidget *widget, t_gtk_tools *g);
int				get_parent_index(t_object *parent, t_object *objects);

/*
** Scene GUI panel
*/

void			scene_render_sig(t_gtk_tools *g);
void			*sig_update_res_x(GtkWidget *SpinButton, t_gtk_tools *g);
void			*sig_update_res_y(GtkWidget *SpinButton, t_gtk_tools *g);
void			*sig_update_ray_depth(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_udpate_ambient_light_color(GtkWidget *color_chooser, t_gtk_tools *g);
void			*sig_update_ambient_light_coeff(GtkWidget *spin_button, t_gtk_tools *g);
void 			*update_grid_scene(t_gtk_tools *g);
void			*sig_render(GtkWidget *widget, t_gtk_tools *g);
void			*sig_next_camera(GtkWidget *button, t_gtk_tools *g);
void			*sig_prev_camera(GtkWidget *button, t_gtk_tools *g);

/*
** Objects GUI panel
*/

GtkWidget		*get_widget(t_gtk_tools *g, char *widget_name);
void			update_objects_info_panel_bis(t_gtk_tools *g, t_object *obj, int type);
void			obj_render_sig(t_gtk_tools *g);
void			*populate_list_box_objects(t_gtk_tools *g); //Camel
void			*sig_update_current_object(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g);
void			update_objects_info_panel(t_gtk_tools *g, t_object *obj);
void			init_obj_look_at_combo_box(GtkWidget *widget, t_gtk_tools *g);
void			init_obj_parent_combo_box(GtkWidget *widget, t_gtk_tools *g);
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
void			*sig_update_obj_ior(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_kreflection(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_radius(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_radius_2(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_obj_height(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_obj_dir_normalize(GtkWidget *button, t_gtk_tools *g);
t_vec3			get_look_at_obj(GtkComboBox *ComboBox, t_gtk_tools *g);

/*
** Lights GUI panel
*/

t_light			*get_light_from_list_box(t_gtk_tools *g);
void			light_render_sig(t_gtk_tools *g);
void			*update_grid_lights(t_gtk_tools *g);
void			update_lights_info_panel(t_gtk_tools *g, t_light *light);
void			*sig_update_current_light(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g);
t_light			*get_selected_light(t_gtk_tools *g);
void			*sig_update_light_name(GtkWidget *GtkEntry, t_gtk_tools *g);
void			*sig_update_light_pos_x(GtkWidget *SpinButton, t_gtk_tools *g);
void			*sig_update_light_pos_y(GtkWidget *SpinButton, t_gtk_tools *g);
void			*sig_update_light_pos_z(GtkWidget *SpinButton, t_gtk_tools *g);
void			*sig_update_light_dir_x(GtkWidget *SpinButton, t_gtk_tools *g);
void			*sig_update_light_dir_y(GtkWidget *SpinButton, t_gtk_tools *g);
void			*sig_update_light_dir_z(GtkWidget *SpinButton, t_gtk_tools *g);
void			*sig_update_light_color(GtkWidget *color_chooser, t_gtk_tools *g);
void			*sig_update_light_intensity(GtkWidget *SpinButton, t_gtk_tools *g);

/*
** Cameras GUI panel
*/

void			camera_render_sig(t_gtk_tools *g);
void			*update_grid_cameras(t_gtk_tools *g);
t_camera		*get_first_camera(t_gtk_tools *g);
void			update_cameras_info_panel(t_gtk_tools *g, t_camera *camera);
void			init_cam_look_at_combo_box(GtkWidget *widget, t_gtk_tools *g);
void			*sig_update_current_cam(GtkListBox *box, GtkListBoxRow *row, t_gtk_tools *g);
t_camera		*get_selected_camera(t_gtk_tools *g);
void			*sig_update_cam_name(GtkWidget *GtkEntry, t_gtk_tools *g);
void			*sig_update_cam_pos_x(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_cam_pos_y(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_cam_pos_z(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_cam_lookat_x(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_cam_lookat_y(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_cam_lookat_z(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_cam_lookat_name(GtkWidget *ComboBox, t_gtk_tools *g);
void			*sig_update_cam_dir_x(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_cam_dir_y(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_cam_dir_z(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_cam_dir_normalize(GtkWidget *button, t_gtk_tools *g);
void			*sig_update_cam_fov(GtkWidget *spin_button, t_gtk_tools *g);
void			*sig_update_cam_ior(GtkWidget *spin_button, t_gtk_tools *g);

/*
** New Object GUI
*/

void    		*sig_new_object(GtkWidget *widget, t_gtk_tools *g);

/*
** New Light GUI
*/

void    		*sig_new_light(GtkWidget *widget, t_gtk_tools *g);

/*
** New Camera GUI
*/

void    		*sig_new_camera(GtkWidget *widget, t_gtk_tools *g);

/*
** Delete
*/

void			*sig_delete_object(GtkWidget *widget, t_gtk_tools *g);
void			*sig_delete_light(GtkWidget *widget, t_gtk_tools *g);
void 	  	 	*sig_delete_camera(GtkWidget *widget, t_gtk_tools *g);

/*
** Window Signals
*/

void 			on_window_main_destroy();
void 			window_destroy(GtkWidget *widget, void *ouais);
void 			window_destroy_esc(GtkWidget *widget, void *ouais);

/*
** Error
*/

int				display_error_popup(GtkWidget *filechooser, t_gtk_tools *g, char *ret);

/*
** Debugging signals -- Remove
*/

void			 *sig_print_scene(GtkWidget *button, t_gtk_tools *g);

#endif
