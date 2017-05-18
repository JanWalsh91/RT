/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc_lights.cu                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:10:25 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/18 16:12:29 by jwalsh           ###   ########.fr       */
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

static t_light		*list_to_array_lights(t_light *light);
static size_t		get_lights_array_length(t_light *lights);

void				cuda_malloc_lights(t_raytracing_tools *r, t_scene *h_scene_to_array)
{
	if (r->update.lights >= 1)
	{
		h_scene_to_array->lights = list_to_array_lights(r->scene->lights);
		if (r->update.lights == 2)
			gpuErrchk(cudaMalloc(&(r->h_d_scene->lights), get_lights_array_length(h_scene_to_array->lights)));
		gpuErrchk((cudaMemcpy(r->h_d_scene->lights, h_scene_to_array->lights, get_lights_array_length(h_scene_to_array->lights), cudaMemcpyHostToDevice)));
		free(h_scene_to_array->lights);
	}
}

static t_light		*list_to_array_lights(t_light *light)
{
	int			size;
	t_light	*head;
	t_light	*array;

	size = 0;
	head = light; 
	while (light)
	{
		++size;
		light = light->next;
	}
	if (!(array = (t_light *)malloc(sizeof(t_light) * (size + 1))))
	{
		write(2, "Malloc error.\n", 14);
		exit(1);
	}
	array[size].col = v_new(NAN, NAN, NAN);
	light = head;
	size = -1;
	while (light)
	{
		array[++size].col = v_new(NAN, NAN, NAN);
		memcpy(&array[size], light, sizeof(t_light));
		light = light->next;
	}
	return (array);
}

static size_t		get_lights_array_length(t_light *lights)
{
	size_t	size;

	size = 0;
	while (!v_isnan(lights[size].col))
		++size;
	return ((size + 1) * sizeof(t_light));
}
