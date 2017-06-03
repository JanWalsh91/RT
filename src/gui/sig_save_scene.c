/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_save_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 16:35:34 by tgros             #+#    #+#             */
/*   Updated: 2017/06/03 16:52:56 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	save_scene1(int fd, t_scene *scene);
static void	save_scene2(int fd, t_scene *scene);

void		save_scene(int fd, t_scene *scene)
{
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
	save_scene1(fd, scene);
	save_scene2(fd, scene);
}

static void	save_scene1(int fd, t_scene *scene)
{
	if (!v_isnan(scene->background_color))
	{
		write(fd, "\tbackground color: ", 19);
		write_vector(fd, (t_vec3)scene->background_color);
		write(fd, "\n", 1);
	}
	write(fd, "\tambient light color: ", 22);
	write_vector(fd, (t_vec3)scene->ambient_light_color);
	write(fd, "\n", 1);
	write(fd, "\tka: ", 5);
	write_float(fd, scene->ka);
	write(fd, "\n", 1);
}

static void	save_scene2(int fd, t_scene *scene)
{
	t_object	*o_ptr;
	t_light		*l_ptr;
	t_camera	*c_ptr;

	o_ptr = scene->objects;
	while (o_ptr)
	{
		save_object(fd, o_ptr, scene->objects);
		o_ptr = o_ptr->next;
	}
	l_ptr = scene->lights;
	while (l_ptr)
	{
		save_light(fd, l_ptr);
		l_ptr = l_ptr->next;
	}
	c_ptr = scene->cameras;
	while (c_ptr && c_ptr->prev)
		c_ptr = c_ptr->prev;
	while (c_ptr)
	{
		save_camera(fd, c_ptr);
		c_ptr = c_ptr->next;
	}
	write(fd, "}\n", 2);
}
