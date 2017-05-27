/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:51:28 by tgros             #+#    #+#             */
/*   Updated: 2017/05/27 14:04:05 by jwalsh           ###   ########.fr       */
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

static void		reset_update_struct(t_raytracing_tools *r);
static void		cuda_malloc_scene(t_raytracing_tools *r);

/*
** Allocates memory on the device and on pinned memory the various sturctures in scene.
*/

int				cuda_malloc(t_raytracing_tools *r)
{
	t_scene		h_scene_to_array;

	r->scene->photon_count = 24;
	if (!(memcpy(&h_scene_to_array, r->scene, sizeof(t_scene) - (sizeof(void *) * 3))))
		exit (0);
	memcpy(r->h_d_scene, r->scene, sizeof(t_scene) - (sizeof(void *) * 3));
	cuda_malloc_photon_map(r);
	cuda_malloc_objects(r, &h_scene_to_array);
	cuda_malloc_lights(r, &h_scene_to_array);
	cuda_malloc_camera(r);
	cuda_malloc_scene(r);
	gpuErrchk(cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice));
	reset_update_struct(r);
	return (1);
}

static void		reset_update_struct(t_raytracing_tools *r)
{
	r->update.resolution = 0;
	r->update.objects = 0;
	r->update.lights = 0;
	r->update.cameras = 0;
	r->update.scene = 0;
	r->update.ray_depth = 0;
	r->update.render = 0;
	r->update.photon_map = 0;
}

static void		cuda_malloc_scene(t_raytracing_tools *r)
{
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
	if (r->update.anaglyph == 2)
			gpuErrchk((cudaMallocHost(&r->d_pixel_map_3d, sizeof(t_color) * r->scene->res.y * r->scene->res.x)));
	if (r->update.scene == 2)
		gpuErrchk(cudaMalloc(&r->d_scene, sizeof(t_scene)));
}
