/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:51:28 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 14:14:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.cuh"

static void		reset_update_struct(t_raytracing_tools *r);
bool	cuda_malloc_scene(t_raytracing_tools *r);

/*
** Allocates memory on the device and on pinned memory the various sturctures
** in the scene.
*/

bool				cuda_malloc(t_raytracing_tools *r)
{
	t_scene		h_scene_to_array;

	memcpy(&h_scene_to_array, r->scene, sizeof(t_scene) - (sizeof(void *) * 3));
	memcpy(r->h_d_scene, r->scene, sizeof(t_scene) - (sizeof(void *) * 3));
	if (cuda_malloc_objects(r, &h_scene_to_array) == false)
		return(false);
	if (cuda_malloc_lights(r, &h_scene_to_array) == false)
		return(false);
	if (cuda_malloc_camera(r) == false)
		return(false);
	if (cuda_malloc_scene(r) == false)
		return(false);
	gpu_errchk(cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene),
		cudaMemcpyHostToDevice));
	reset_update_struct(r);
	return (true);
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

 bool		cuda_malloc_scene(t_raytracing_tools *r)
{
	if (r->update.resolution == 2)
	{
		gpu_errchk((cudaMallocHost(&r->d_pixel_map, sizeof(t_color) *
			r->scene->res.y * r->scene->res.x)));
		if (r->scene->is_3d)
			gpu_errchk((cudaMallocHost(&r->d_pixel_map_3d, sizeof(t_color) *
				r->scene->res.y * r->scene->res.x)));
	}
	if (r->update.ray_depth == 2)
	{
		gpu_errchk(cudaSetDevice(0));
		cudaDeviceSetLimit(cudaLimitStackSize, 1024 * r->scene->ray_depth);
	}
	if (r->update.anaglyph == 2)
		gpu_errchk((cudaMallocHost(&r->d_pixel_map_3d, sizeof(t_color) *
			r->scene->res.y * r->scene->res.x)));
	if (r->update.scene == 2)
	{
		if(test_cuda_malloc((void **)(&r->d_scene), sizeof(t_scene)) == false)
			return(false);
	}
	return(true);
}
