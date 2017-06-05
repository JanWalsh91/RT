/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:13:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 14:31:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include <stdio.h>

void	print_scene(t_scene *scene)
{
	t_object	*o_ptr;
	t_light		*l_ptr;
	t_camera	*c_ptr;

	ft_printf("%{u}%{red}print_scene%{}\n");
	printf("scene: %s\n", scene->name);
	printf("	res: [%i, %i]\n", scene->res.x, scene->res.y);
	printf("	ray_depth: [%i]\n", scene->ray_depth);
	printf("	background col: [%f] [%f] [%f]\n", scene->background_color.x, scene->background_color.y, scene->background_color.z);
	printf("	ambient coef: [%f]\n", scene->ka);
	printf("	ambient col: [%f] [%f] [%f]\n", scene->ambient_light_color.x, scene->ambient_light_color.y, scene->ambient_light_color.z);
	printf("	image aspect ratio: [%f]\n", scene->image_aspect_ratio);
	printf("	is_shadow: %d\n", scene->is_shadow);
	printf("	is_diffuse: %d\n", scene->is_diffuse);
	printf("	is_specular: %d\n", scene->is_specular);
	printf("	is_3d: %d\n", scene->is_3d);
	printf("	is_fresnel: %d\n", scene->is_fresnel);
	printf("	is_photon_mapping: %d\n", scene->is_photon_mapping);
	printf("	is_aa: %d\n", scene->is_aa);
	printf("	photon_count: %d\n", scene->photon_count);
	printf("	photon_list address: %p\n", scene->photon_list);
	printf("	photon_map address: %p\n", scene->photon_kd_tree);
	o_ptr = scene->objects;
	printf("	OBJECTS: %p\n", scene->objects);
	while (o_ptr)
	{
		printf("	----object name: [%s] [%p]\n", o_ptr->name, o_ptr);
		printf("		object type: [%i]\n", o_ptr->type);
		printf("		obj file address: [%p]\n", o_ptr->obj);
		printf("		object pos: [%f] [%f] [%f]\n", o_ptr->pos.x, o_ptr->pos.y, o_ptr->pos.z);
		printf("		object dir: [%f] [%f] [%f]\n", o_ptr->dir.x, o_ptr->dir.y, o_ptr->dir.z);
		printf("		object lookat: [%f] [%f] [%f]\n", o_ptr->look_at.x, o_ptr->look_at.y, o_ptr->look_at.z);
		printf("		object col: [%f] [%f] [%f]\n", o_ptr->col.x, o_ptr->col.y, o_ptr->col.z);
		printf("		object rad: [%f]\n", o_ptr->rad);
		printf("		object rad_torus: [%f]\n", o_ptr->rad_torus);
		printf("		object height: [%f]\n", o_ptr->height);
		printf("		object angle: [%f]\n", o_ptr->angle);
		printf("		object kd: [%f]\n", o_ptr->kd);
		printf("		object ks: [%f]\n", o_ptr->ks);
		printf("		object specular exponent: [%f]\n", o_ptr->specular_exp);
		printf("		object reflection: [%f]\n", o_ptr->reflection);
		printf("		object transparency: [%f]\n", o_ptr->transparency);
		printf("		object ior: [%f]\n", o_ptr->ior);
		
		printf("		object texture: [%p]\n", o_ptr->texture);
		printf("		object texture name: [%s]\n", o_ptr->texture_name);
		printf("		object texture dim: [%f] [%f] [%f]\n", o_ptr->texture_dim.x, o_ptr->texture_dim.y, o_ptr->texture_dim.z);
		printf("		object texture ratio: [%d] [%d]\n", o_ptr->texture_ratio.x, o_ptr->texture_ratio.y);
		printf("		object texture translate: [%d] [%d]\n", o_ptr->texture_translate.x, o_ptr->texture_translate.y);
		printf("		object texture_color_style: [%c](ascii: %i)\n", o_ptr->texture_color_style, o_ptr->texture_color_style);

		printf("		object normal map: [%p]\n", o_ptr->normal_map);
		printf("		object normal name: [%s]\n", o_ptr->normal_map_name);
		printf("		object normal map dim: [%f] [%f] [%f]\n", o_ptr->normal_map_dim.x, o_ptr->normal_map_dim.y, o_ptr->normal_map_dim.z);

		printf("		objet parent : %d\n", o_ptr->parent_index);
		printf("		objet parent addr : %p (%s)\n", o_ptr->parent, o_ptr->parent ? o_ptr->parent->name : "None");
		o_ptr = o_ptr->next;
	}
	c_ptr = scene->cameras;
	printf("	CAMERAS: %p\n", scene->cameras);
	while (c_ptr)
	{
		printf("	----camera name: [%s]\n", c_ptr->name);
		printf("		camera pos: [%f] [%f] [%f]\n", c_ptr->pos.x, c_ptr->pos.y, c_ptr->pos.z);
		printf("		camera dir: [%f] [%f] [%f]\n", c_ptr->dir.x, c_ptr->dir.y, c_ptr->dir.z);
		printf("		camera look at: [%f] [%f] [%f]\n", c_ptr->look_at.x, c_ptr->look_at.y, c_ptr->look_at.z);
		printf("		camera scale: [%f]\n", c_ptr->scale);
		printf("		camera fov: [%f]\n", c_ptr->fov);
		printf("		camera ior: [%f]\n", c_ptr->ior);
		printf("		camera filter: [%d]\n", c_ptr->filter);
		c_ptr = c_ptr->next;
	}
	printf("	LIGHTS: %p\n", scene->lights);
	l_ptr = scene->lights;
	while (l_ptr)
	{
		printf("	----light name: [%s]\n", l_ptr->name);
		printf("		light pos: [%f] [%f] [%f]\n", l_ptr->pos.x, l_ptr->pos.y, l_ptr->pos.z);
		printf("		light dir: [%f] [%f] [%f]\n", l_ptr->dir.x, l_ptr->dir.y, l_ptr->dir.z);	
		printf("		light look_at: [%f] [%f] [%f]\n", l_ptr->look_at.x, l_ptr->look_at.y, l_ptr->look_at.z);		
		printf("		light col: [%f] [%f] [%f]\n", l_ptr->col.x, l_ptr->col.y, l_ptr->col.z);
		printf("		light intensity: [%f]\n", l_ptr->intensity);
		l_ptr = l_ptr->next;
	}
	printf("\n");
}

void	print_attributes(t_attributes att)
{
	printf("print_attributes\n");
	printf("res:		[%i][%i]\n", att.res.x, att.res.y);
	printf("ray_depth:	[%i]\n", att.ray_depth);
	printf("pos:		[%f][%f][%f]\n", att.pos.x, att.pos.y, att.pos.z);
}

void	print_vec(t_vec3 vec)
{
	printf("print_vec: [%f][%f][%f]\n", vec.x, vec.y, vec.z);
}

void	print_matrix(t_matrix m)
{
	int i;
	int	y;

	y = -1;
	while (++y < 4)
	{
		i = -1;
		while (++i < 4)
			printf("[%f]", m[y][i]);
		printf("\n");
	}
}

// void	print_photons(t_kd_tree *tree)
// {
// 	//print in-order
// 	if (!tree)
// 		return ;
// 	print_photons(tree->left);
// 	printf("photon pos: [%f, %f, %f]\n", tree->dir.x, tree->dir.y, tree->dir.z);
// 	print_photons(tree->right);
// }
