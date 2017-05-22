/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc_objects.cu                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:06:29 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/22 11:06:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.h"

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

static t_object		*list_to_array_objects(t_object *object);
static size_t		get_objects_array_length(t_object *objects);

void				cuda_malloc_objects(t_raytracing_tools *r, t_scene *h_scene_to_array)
{
	if (r->update.objects >= 1)
	{
		h_scene_to_array->objects = list_to_array_objects(r->scene->objects);
		if (r->update.objects == 2)
			gpuErrchk(cudaMalloc(&(r->h_d_scene->objects), get_objects_array_length(h_scene_to_array->objects)));
		gpuErrchk((cudaMemcpy(r->h_d_scene->objects, h_scene_to_array->objects, get_objects_array_length(h_scene_to_array->objects), cudaMemcpyHostToDevice)));
		free(h_scene_to_array->objects);
	}
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
	size = -1;
	while (object)
	{
		memcpy(&array[++size], object, sizeof(t_object));
		object = object->next;
	}
	return (array);
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
