/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_save_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 16:36:18 by tgros             #+#    #+#             */
/*   Updated: 2017/06/04 13:59:12 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	save_object1(int fd, t_object *obj);
static void	save_object2(int fd, t_object *obj);
static void	save_object3(int fd, t_object *obj);
static void	save_object4(int fd, t_object *obj, t_object *objects);

void		save_object(int fd, t_object *obj, t_object *objects)
{
	save_object1(fd, obj);
	write(fd, obj->name, ft_strlen(obj->name));
	write(fd, "\n\t{\n", 4);
	write(fd, "\t\tposition: ", 12);
	write_vector(fd, obj->pos);
	write(fd, "\n", 1);
	write(fd, "\t\tdirection: ", 13);
	write_vector(fd, obj->dir);
	write(fd, "\n", 1);
	save_object2(fd, obj);
	save_object3(fd, obj);
	save_object4(fd, obj, objects);
}

static void	save_object1(int fd, t_object *obj)
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
	else if (obj->type == T_CUBE_TROUE)
		write(fd, "\tcube troue: ", 12);
	else if (obj->type == T_PARABOLOID)
		write(fd, "\tparaboloid: ", 13);
	else if (obj->type == T_TORUS)
		write(fd, "\ttorus: ", 8);
}

static void	save_object2(int fd, t_object *obj)
{
	if (!v_isnan(obj->look_at) && (obj->look_at.x != 0 &&
		obj->look_at.y != 0 && obj->look_at.z != 0))
	{
		write(fd, "\t\tlook at: ", 11);
		write_vector(fd, obj->look_at);
		write(fd, "\n", 1);
	}
	write(fd, "\t\tcolor: ", 9);
	write_vector(fd, (t_vec3)obj->col);
	write(fd, "\n", 1);
	if (obj->type == T_SPHERE || obj->type == T_CYLINDER ||
		obj->type == T_CONE || obj->type == T_DISK || obj->type == T_TORUS)
	{
		write(fd, "\t\tradius: ", 10);
		write_float(fd, obj->rad);
		write(fd, "\n", 1);
	}
	if (obj->type == T_TORUS)
	{
		write(fd, "\t\tradius 2: ", 12);
		write_float(fd, obj->rad_torus);
		write(fd, "\n", 1);
	}
}

static void	save_object3(int fd, t_object *obj)
{
	if (obj->type == T_CYLINDER || obj->type == T_CONE ||
		obj->type == T_PARABOLOID)
	{
		write(fd, "\t\theight: ", 10);
		write_float(fd, obj->height);
		write(fd, "\n", 1);
	}
	write(fd, "\t\tkd: ", 6);
	write_float(fd, obj->kd);
	write(fd, "\n", 1);
	write(fd, "\t\tks: ", 6);
	write_float(fd, obj->ks);
	write(fd, "\n", 1);
	write(fd, "\t\tspecular exponent: ", 21);
	write_float(fd, obj->specular_exp);
	write(fd, "\n", 1);
	write(fd, "\t\tior: ", 7);
	write_float(fd, obj->ior);
	write(fd, "\n", 1);
	write(fd, "\t\ttransparency: ", 16);
	write_float(fd, obj->transparency);
	write(fd, "\n", 1);
	write(fd, "\t\treflection: ", 14);
	write_float(fd, obj->reflection);
	write(fd, "\n", 1);
}

static void	save_object4(int fd, t_object *obj, t_object *objects)
{
	if (obj->texture_name)
	{
		write(fd, "\n\t\ttexture: ", 12);
		write(fd, obj->texture_name, ft_strlen(obj->texture_name));
		if (ft_strcmp(obj->texture_name, "Perlin") == 0 ||
			ft_strcmp(obj->texture_name, "Checkerboard") == 0 ||
			ft_strcmp(obj->texture_name, "Noise") == 0)
		{
			write(fd, " ", 1);
			write_vector(fd, obj->texture_dim);
		}
	}
	if (obj->normal_map_name)
	{
		write(fd, "\n\t\tnormal map: ", 15);
		write(fd, obj->normal_map_name, ft_strlen(obj->normal_map_name));
	}
	if (obj->parent)
	{
		write(fd, "\n\t\tparent index: ", 17);
		write_float(fd, get_parent_index(obj->parent, objects));
	}
	write(fd, "\n\t}\n", 4);
}
