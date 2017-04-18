/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 11:08:11 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/18 15:24:28 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

//combine save and save as
//check menu_item text contents
//ADD OPEN PROTECTIONS
void    *sig_save(GtkWidget *menu_item, t_gtk_tools *g)
{
    int             fd;

	fd = -1;
    printf("sig_save: filename: [%s]\n", g->filename);
	fd = open(g->filename, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		printf("file not found: [%s]\n", g->filename);
		g->filename = get_new_filename(g);
	}
	printf("fd: [%i]\n", fd);
	if (!g->filename)
		return (NULL);
	if (fd == -1)
		fd = open(g->filename, O_CREAT | O_WRONLY);
	save_scene(fd, g->r->scene);
	close(fd);
    return (NULL);
}


//ADD OPEN PROTECTIONS
void	*sig_save_as(GtkWidget *menu_item, t_gtk_tools *g)
{
	int fd;

	fd = -1;
	printf("sig_save_as\n");
	g->filename = get_new_filename(g);
	fd = open(g->filename, O_CREAT | O_WRONLY);
	save_scene(fd, g->r->scene);
	close(fd);
	return (NULL);
}

char       *get_new_filename(t_gtk_tools *g)
{
    GtkWidget       *dialog;
    char			*filename;

	printf("get_new_filename\n");
	filename = NULL;
    dialog = gtk_file_chooser_dialog_new("Save as .rt", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
    "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_set_attached_to(GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(g->builder), "window_main")), dialog);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
		printf("saving as [%s]\n", filename);
    }
    gtk_widget_destroy(dialog);
	return (filename);
}

void	save_scene(int fd, t_scene *scene)
{
	t_object	*o_ptr;
	t_light		*l_ptr;
	t_camera	*c_ptr;

	if (!scene)
		return ;
	write(fd, "scene: ", 7);
	write(fd, scene->name, ft_strlen(scene->name));
	write(fd, "\n{\n", 3);
	write(fd, "\tresolution: ", 13);
	write_int(fd, scene->res.x);
	write(fd, ", ", 2);
	write_int(fd, scene->res.y);
	write(fd, "\n", 1);
	write(fd, "\tray depth: ", 12);
	write_int(fd, scene->ray_depth);
	write(fd, "\n", 1);
	if (!v_isnan(scene->background_color))
	{
		write(fd, "\tbackgound color: ", 17);
		write_vector(fd, (t_vec3)scene->background_color);
		write(fd, "\n", 1);
	}
	write(fd, "\tambient light color: ", 22);
	write_vector(fd, (t_vec3)scene->ambient_light_color);
	write(fd, "\n", 1);
	write(fd, "\tka: ", 5);
	write_double(fd, scene->ka);
	write(fd, "\n", 1);
	o_ptr = scene->objects;
	while (o_ptr)
	{
		save_object(fd, o_ptr);
		o_ptr = o_ptr->next;
	}
	l_ptr = scene->lights;
	while (l_ptr)
	{
		save_light(fd, l_ptr);
		l_ptr = l_ptr->next;
	}
	c_ptr = scene->cameras;
	while (c_ptr->prev)
		c_ptr = c_ptr->prev;
	while (c_ptr)
	{
		save_camera(fd, c_ptr);
		c_ptr = c_ptr->next;
	}
	write(fd, "}\n", 2);
}

void	save_object(int fd, t_object *obj)
{
	if (obj->type == T_PLANE)
		write(fd, "\tplane: ", 8);
	else if (obj->type == T_DISK)
		write(fd, "\tdisk: ", 7);
	else if (obj->type == T_SPHERE)
		write(fd, "\tsphere: ", 9);
	else if (obj->type == T_CYLINDER)
		write(fd, "\tcylinder: ", 11);
	else if (obj->type == T_CONE)
		write(fd, "\tcone: ", 7);
	write(fd, obj->name, ft_strlen(obj->name));
	write(fd, "\n\t{\n", 4);
	write(fd, "\t\tposition: ", 12);
	write_vector(fd, obj->pos);
	write(fd, "\n", 1);
	if (obj->type != T_SPHERE)
	{
		write(fd, "\t\tdirection: ", 13);
		write_vector(fd, obj->dir);
		write(fd, "\n", 1);
		if (!v_isnan(obj->look_at) && (obj->look_at.x != 0 && obj->look_at.y != 0 && obj->look_at.z != 0))
		{
			write(fd, "\t\tlook at: ", 11);
			write_vector(fd, obj->look_at);
			write(fd, "\n", 1);
		}
	}
	write(fd, "\t\tcolor: ", 9);
	write_vector(fd, (t_vec3)obj->col);
	write(fd, "\n", 1);
	if (obj->type == T_SPHERE || obj->type == T_CYLINDER || obj->type == T_CONE)
	{
		write(fd, "\t\tradius: ", 10);
		write_double(fd, obj->rad);
		write(fd, "\n", 1);
	}
	if (obj->type == T_CYLINDER || obj->type == T_CONE)
	{
		write(fd, "\t\theight: ", 10);
		write_double(fd, obj->height);
		write(fd, "\n", 1);
	}
	write(fd, "\t\tkd: ", 6);
	write_double(fd, obj->kd);
	write(fd, "\n", 1);
	write(fd, "\t\tks: ", 6);
	write_double(fd, obj->ks);
	write(fd, "\n", 1);
	write(fd, "\t\tspecular exponent: ", 21);
	write_double(fd, obj->specular_exp);
	write(fd, "\n\t}\n", 4);

}

void	save_camera(int fd, t_camera *cam)
{
	write(fd, "\tcamera: ", 9);
	write(fd, cam->name, ft_strlen(cam->name));
	write(fd, "\n\t{\n", 4);
	write(fd, "\t\tposition: ", 12);
	write_vector(fd, cam->pos);
	write(fd, "\n", 1);
	write(fd, "\t\tdirection: ", 13);
	write_vector(fd, cam->dir);
	write(fd, "\n", 1);
	if (!v_isnan(cam->look_at) && (cam->look_at.x != 0 && cam->look_at.y != 0 && cam->look_at.z != 0))
	{
		write(fd, "\t\tlook at: ", 11);
		write_vector(fd, cam->look_at);
		write(fd, "\n", 1);
	}
	write(fd, "\t\tfov: ", 7);
	write_int(fd, cam->fov);
	write(fd, "\n\t}\n", 4);
}

void	save_light(int fd, t_light *light)
{
	write(fd, "\tlight: ", 8);
	write(fd, light->name, ft_strlen(light->name));
	write(fd, "\n\t{\n", 4);
	write(fd, "\t\tposition: ", 12);
	write_vector(fd, light->pos);
	write(fd, "\n", 1);
	if (!v_isnan(light->dir))
	{
		write(fd, "\t\tdirection: ", 13);
		write_vector(fd, light->dir);
		write(fd, "\n", 1);
	}
	if (!v_isnan(light->look_at))
	{
		write(fd, "\t\tlook at: ", 11);
		write_vector(fd, light->look_at);
		write(fd, "\n", 1);
	}
	write(fd, "\t\tcolor: ", 8);
	write_vector(fd, (t_vec3)light->col);
	write(fd, "\n", 1);
	write(fd, "\t\tintensity: ", 13);
	write_int(fd, light->intensity);
	write(fd, "\n\t}\n", 4);
}

void	write_vector(int fd, t_vec3 vec)
{
	char 	*tmp;

	write_double(fd, vec.x);
	write(fd, ", ", 2);
	write_double(fd, vec.y);
	write(fd, ", ", 2);
	write_double(fd, vec.z);
}

void	write_double(int fd, double d)
{
	char 	*tmp;
	double	tmp2;
	int		i;
	
	if (d < 0.0)
	{
		write (fd, "-", 1);
		d = -d;
	}
	tmp = ft_itoa(d);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
	write(fd, ".", 1);
	i = -1;
	tmp2 = d - (double)(int)d;
	while (++i < SAVE_DOUBLE_PRECISION)
	{
		tmp2 *= 10.0;
		tmp = ft_itoa((int)tmp2);
		write(fd, tmp, 1);
		free(tmp);
		tmp2 -= (double)(int)tmp2;
	}
}

void	write_int(int fd, int i)
{
	char *tmp;

	tmp = ft_itoa(i);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}