/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:38:53 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 11:07:19 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

static void			get_obj_direction(t_scene *scene, t_object *obj);
static void			set_parent(t_object *objects, t_object *o_ptr);
static void			get_cone_angle(t_object *cone);
static void			check_material(t_scene *scene, t_object *obj);

/*
** Checks the validity of objects and their attributes.
** Sets default values if necessary.
*/

void				check_objects(t_scene *scene, t_object *objects)
{
	t_object	*o_ptr;

	o_ptr = objects;
	while (o_ptr)
	{
		v_isnan(o_ptr->pos) ? set_default_pos(scene, o_ptr->type,
			o_ptr, &o_ptr->pos) : 0;
		o_ptr->type != T_SPHERE ? get_obj_direction(scene, o_ptr) : 0;
		v_isnan(o_ptr->col) ? set_default_col(scene, o_ptr->type,
			o_ptr, &o_ptr->col) : 0;
		if ((o_ptr->type != T_PLANE) && isnan(o_ptr->rad))
			set_default_radius(scene, o_ptr->type, o_ptr, &o_ptr->rad);
		(o_ptr->type == 9 || o_ptr->type == 10) && isnan(o_ptr->height)
			? set_default_height(scene, o_ptr->type, o_ptr, &o_ptr->height) : 0;
		check_material(scene, o_ptr);
		o_ptr->type == T_CONE ? get_cone_angle(o_ptr) : 0;
		if (o_ptr->parent_index)
			set_parent(objects, o_ptr);
		o_ptr = o_ptr->next;
	}
}

static void			check_material(t_scene *scene, t_object *obj)
{
	isnan(obj->ks) ? set_default_ks(scene, obj->type,
		obj, &obj->ks) : 0;
	isnan(obj->kd) ? set_default_kd(scene, obj->type,
		obj, &obj->kd) : 0;
	isnan(obj->specular_exp) ? set_default_specular_exp(scene,
		obj->type, obj, &obj->specular_exp) : 0;
	isnan(obj->ior) ? set_default_ior(scene,
		obj->type, obj, &obj->ior) : 0;
	isnan(obj->transparency) ? set_default_transparency(scene,
		obj->type, obj, &obj->transparency) : 0;
	isnan(obj->reflection) ? set_default_reflection(scene,
		obj->type, obj, &obj->reflection) : 0;
}

static void			set_parent(t_object *objects, t_object *o_ptr)
{
	int	i;

	i = 0;
	while (objects && ++i != o_ptr->parent_index)
	{
		printf("i = %d, object = %p\n", i, objects);
		objects = objects->next;
	}
	if (i == o_ptr->parent_index)
		o_ptr->parent = objects;
	else
	{
		o_ptr->parent = NULL;
		o_ptr->parent_index = 0;
	}
}

static void			get_obj_direction(t_scene *scene, t_object *obj)
{
	if (!v_isnan(obj->look_at) && !v_isnan(obj->pos))
		obj->dir = v_sub(obj->look_at, obj->pos);
	if (v_isnan(obj->dir) || (!obj->dir.x && !obj->dir.y && !obj->dir.z))
		set_default_obj_dir(scene, obj->type, obj, &obj->dir);
	obj->dir = v_norm(obj->dir);
	if (v_isnan(obj->look_at))
		obj->look_at = v_new(0, 0, 0);
}

static void			get_cone_angle(t_object *cone)
{
	if (cone->height)
		cone->angle = atan(cone->rad / cone->height);
}
