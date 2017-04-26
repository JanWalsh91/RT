/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:51:28 by tgros             #+#    #+#             */
/*   Updated: 2017/04/25 16:56:42 by tgros            ###   ########.fr       */
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

t_light			*list_to_array_lights(t_light *light);
t_object		*list_to_array_objects(t_object *object);
size_t			get_objects_array_length(t_object *objects);
size_t			get_lights_array_length(t_light *lights);




int	cuda_malloc(t_raytracing_tools *r)
{
	t_scene		h_scene_to_array;

	if (!(memcpy(&h_scene_to_array, r->scene, sizeof ( t_scene ) - (sizeof ( void * ) * 5)  )))
		exit (0);
	memcpy(r->h_d_scene, r->scene, sizeof ( t_scene ) - (sizeof ( void * ) * 5)  );
	if (r->update.resolution == 2)
	{
		gpuErrchk((cudaMallocHost(&r->d_pixel_map, sizeof(t_color) * r->scene->res.y * r->scene->res.x)));
	}
	if (r->update.ray_depth == 2)
	{
		gpuErrchk(cudaSetDevice(0));
		cudaDeviceSetLimit(cudaLimitStackSize, 1024 * r->scene->ray_depth);
	}
	if (r->update.objects >= 1)
	{
		h_scene_to_array.objects = list_to_array_objects(r->scene->objects);
		if (r->update.objects == 2)
			gpuErrchk(cudaMalloc(&(r->h_d_scene->objects), get_objects_array_length(h_scene_to_array.objects)));
		gpuErrchk((cudaMemcpy(r->h_d_scene->objects, h_scene_to_array.objects, get_objects_array_length(h_scene_to_array.objects), cudaMemcpyHostToDevice)));
		free(h_scene_to_array.objects);
	}
	if (r->update.lights >= 1)
	{
		h_scene_to_array.lights = list_to_array_lights(r->scene->lights);
		if (r->update.lights == 2)
			gpuErrchk(cudaMalloc(&(r->h_d_scene->lights), get_lights_array_length(h_scene_to_array.lights)));
		gpuErrchk((cudaMemcpy(r->h_d_scene->lights, h_scene_to_array.lights, get_lights_array_length(h_scene_to_array.lights), cudaMemcpyHostToDevice)));
		free(h_scene_to_array.lights);
	}
	if (r->update.cameras >= 1)
	{
		if (r->update.cameras == 2)
		{
			printf("Malloc cameras\n");
			gpuErrchk(cudaMalloc(&(r->h_d_scene->cameras), sizeof(t_camera)));
		}
		gpuErrchk((cudaMemcpy(r->h_d_scene->cameras, r->scene->cameras, sizeof(t_camera), cudaMemcpyHostToDevice)));
	}
	if (r->update.scene == 2)
	{
		printf("malloc d_scene\n");
		gpuErrchk(cudaMalloc(&r->d_scene, sizeof(t_scene)));
	}
	gpuErrchk(cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice));
	r->update.resolution = 0;
	r->update.objects = 0;
	r->update.lights = 0;
	r->update.cameras = 0;
	r->update.scene = 0;
	r->update.ray_depth = 0;
	r->update.render = 1;
	// printf("RENDER ADDR %p\n", &r->update.render);
	C(2)
	return (1);
}



t_object	*list_to_array_objects(t_object *object)
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
	array = (t_object *)malloc(sizeof(t_object) * (size + 1)); // malloc error
	array[size].type = T_INVALID_TOKEN;
	object = head;
	size = -1;
	while (object)
	{
		memcpy(&array[++size], object, sizeof(t_object)); // stack memcpy ?
		object = object->next;
	}
	return (array);
}

size_t			get_objects_array_length(t_object *objects)
{
	size_t	size;

	size = 0;
	while (objects[size].type != T_INVALID_TOKEN)
		++size;
	return ((size + 1) * sizeof(t_object));
}

t_light		*list_to_array_lights(t_light *light)
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
	array = (t_light *)malloc(sizeof(t_light) * (size + 1)); // malloc error
	// bzero(array, sizeof(t_light) * (size + 1));
	array[size].col = v_new(NAN, NAN, NAN);
	light = head;
	size = -1;
	// printf("COLOR: %f\n", array[size].col.x);
	while (light)
	{
		array[++size].col = v_new(NAN, NAN, NAN);
		memcpy(&array[size], light, sizeof(t_light));
		light = light->next;
		// printf("%p\n", light);
	}
	// printf("COLOR: %f\n", array[size].col.x);
	return (array);
}

size_t			get_lights_array_length(t_light *lights)
{
	size_t	size;

	size = 0;
	// printf("%f\n", lights[size].col.x);
	while (!v_isnan(lights[size].col))
		++size;
	// C(3)
	return ((size + 1) * sizeof(t_light));
}
