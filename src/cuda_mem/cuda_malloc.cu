/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:51:28 by tgros             #+#    #+#             */
/*   Updated: 2017/05/18 14:38:51 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.h"
#include "photon_mapping.h"

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
	int			i;

	if (!(memcpy(&h_scene_to_array, r->scene, sizeof ( t_scene ) - (sizeof ( void * ) * 6)  )))
		exit (0);
	memcpy(r->h_d_scene, r->scene, sizeof ( t_scene ) - (sizeof ( void * ) * 6)  );
	// sleep(2);
	if (r->scene->is_photon_mapping && r->update.photon_map == 2 ) 
	{
		r->scene->photon_count = 1000;
		gpuErrchk(cudaMallocHost(&(r->h_d_scene->photon_list), sizeof(t_photon *) * (r->scene->photon_count + 1)));
		i = -1;
		while (++i < r->scene->photon_count)
			gpuErrchk(cudaMallocHost(&(r->h_d_scene->photon_list[i]), sizeof(t_photon) * r->scene->ray_depth));
		//allocated pinned mem list in h_d_scene
		//SWICTH 10 WITH K (NUM OF PHOTONS TO GATHER)
		gpuErrchk(cudaMallocHost(&(r->h_d_scene->selected_photons), sizeof(t_selected_photon *) * (r->scene->res.x * r->scene->res.y)));
		i = -1;
		while (++i < r->scene->res.x * r->scene->res.y)
			gpuErrchk(cudaMallocHost(&(r->h_d_scene->selected_photons[i]), sizeof(t_selected_photon) * (10 + 1)));
		r->scene->photon_map = r->h_d_scene->photon_map;
		printf("selected_photons: [%p]\n", r->h_d_scene->selected_photons);
		printf("selected_photons: [%p]\n", r->h_d_scene->selected_photons[1]);
	}
	// printf("-----%p and %p\n", r->scene->photon_map, r->h_d_scene->photon_map);
	// exit(0);
	if (r->update.resolution == 2)
	{
		gpuErrchk((cudaMallocHost(&r->d_pixel_map, sizeof(t_color) * r->scene->res.y * r->scene->res.x)));
		if (r->scene->is_3d)
			gpuErrchk((cudaMallocHost(&r->d_pixel_map_3d, sizeof(t_color) * r->scene->res.y * r->scene->res.x)));
	}
	if (r->update.ray_depth == 2)
	{
		gpuErrchk(cudaSetDevice(0));
		cudaDeviceSetLimit(cudaLimitStackSize, 1024 * r->scene->ray_depth);
	}
	// printf("Objects: %d\n", r->update.objects);
	if (r->update.objects >= 1)
	{
		h_scene_to_array.objects = list_to_array_objects(r->scene->objects);
		if (r->update.objects == 2)
			gpuErrchk(cudaMalloc(&(r->h_d_scene->objects), get_objects_array_length(h_scene_to_array.objects)));
		// printf("Cuda memcpy avec %lu bytes\n", get_objects_array_length(h_scene_to_array.objects));
		gpuErrchk((cudaMemcpy(r->h_d_scene->objects, h_scene_to_array.objects, get_objects_array_length(h_scene_to_array.objects), cudaMemcpyHostToDevice)));
		free(h_scene_to_array.objects);
	}
	// printf("Lights: %d\n", r->update.lights);
	if (r->update.lights >= 1)
	{
		h_scene_to_array.lights = list_to_array_lights(r->scene->lights);
		if (r->update.lights == 2)
			gpuErrchk(cudaMalloc(&(r->h_d_scene->lights), get_lights_array_length(h_scene_to_array.lights)));
		// printf("Cuda memcpy avec %lu bytes\n", get_lights_array_length(h_scene_to_array.lights));
		gpuErrchk((cudaMemcpy(r->h_d_scene->lights, h_scene_to_array.lights, get_lights_array_length(h_scene_to_array.lights), cudaMemcpyHostToDevice)));
		free(h_scene_to_array.lights);
	}
	if (r->update.cameras >= 1)
	{
		if (r->update.cameras == 2)
		{
			gpuErrchk(cudaMalloc(&(r->h_d_scene->cameras), sizeof(t_camera)));
		}
		if (r->scene->is_3d) // l'enlever si on decoche l'opt 3d
			r->scene->cameras->filter = F_LEFT_RED;
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
	r->update.render = 0;
	r->update.photon_map = 0;
	// printf("Resolution: %d\n", r->update.resolution);
	// printf("RENDER ADDR %p\n", &r->update.render);
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
	if (!objects)
		return (0);
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
	printf("Size of light array : %d\n", size);
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
