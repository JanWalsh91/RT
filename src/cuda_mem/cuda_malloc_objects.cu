/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc_objects.cu                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:06:29 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 14:14:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.cuh"

/*
** Allocated memory on the device for objects.
*/

static t_object		*list_to_array_objects(t_object *object);
static size_t		get_objects_array_length(t_object *objects);
static void			update_child_info(t_object *parent, t_object *obj);
static t_object		*list_to_array_objects2(t_object *object, t_object *array);

bool				cuda_malloc_objects(t_raytracing_tools *r, t_scene
					*h_scene_to_array)
{
	if (r->update.objects >= 1)
	{
		h_scene_to_array->objects = list_to_array_objects(r->scene->objects);
		if (r->update.objects == 2)
		{
			if(test_cuda_malloc((void **)(&(r->h_d_scene->objects)), 
				get_objects_array_length(h_scene_to_array->objects)) == false)
				return (false);
		}
		gpu_errchk((cudaMemcpy(r->h_d_scene->objects, h_scene_to_array->objects,
			get_objects_array_length(h_scene_to_array->objects),
			cudaMemcpyHostToDevice)));
		free(h_scene_to_array->objects);
	}
	return (true);
}

static t_object		*list_to_array_objects(t_object *object)
{
	int			size;
	t_object	*head;
	t_object	*array;

	size = 0;
	head = object;
	while (object)
	{
		++size;
		object = object->next;
	}
	if (!(array = (t_object *)malloc(sizeof(t_object) * (size + 1))))
	{
		write(2, "Malloc error.\n", 14);
		exit(1);
	}
	array[size].type = T_INVALID_TOKEN;
	object = head;
	return (list_to_array_objects2(object, array));
}

static t_object		*list_to_array_objects2(t_object *object, t_object *array)
{
	int size;

	size = -1;
	while (object)
	{
		memcpy(&array[++size], object, sizeof(t_object));
		if (object->parent)
			update_child_info(object->parent, &array[size]);
		object = object->next;
	}
	return (array);
}

static void			update_child_info(t_object *parent, t_object *obj)
{
	obj->pos = v_add(obj->pos, parent->pos);
	obj->pos = p_rotate_axis(v_new(0, 1, 0), parent->dir, parent->pos,
		obj->pos);
	obj->dir = v_norm(p_rotate_axis(v_new(0, 1, 0), parent->dir,
		v_new(0, 0, 0), obj->dir));
	if (parent->parent)
		update_child_info(parent->parent, obj);
}

static size_t		get_objects_array_length(t_object *objects)
{
	size_t	size;

	size = 0;
	if (!objects)
		return (0);
	while (objects[size].type != T_INVALID_TOKEN)
		++size;
	return ((size + 1) * sizeof(t_object));
}
