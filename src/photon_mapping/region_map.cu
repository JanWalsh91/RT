/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_map.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 17:15:06 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 09:50:18 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "photon_mapping.h"
#include "cuda.h"
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

static void init_region_map(t_region *region_map, size_t size, float search_rad);

/*
** Allocated or reallocates memory for the CPU region map used in Progressive Photon Mapping. 
*/

//TODO ADD MALLOC PROTECTIONZ

void	malloc_region_map(t_raytracing_tools *r, t_tile tile)
{
	printf("malloc_region_map\n");
	size_t	size1;
	size_t	size2;
	int		i;

	r->update.photon_map = 2; ///////////
	if (r->scene->is_photon_mapping && r->update.photon_map == 2)
	{
		if (r->h_region_map)
			free(r->h_region_map);
		size1 = sizeof(t_region *) * tile.col * tile.row;
		size2 = sizeof(t_region) * tile.size * tile.size;
		r->h_region_map = (t_region **)malloc(size1);
		i = -1;
		// printf("----rad: %f\n", r->settings.photon_search_radius);
		// printf("region map: %p tile.col: %d tile.row: %d\n", r->h_region_map, tile.col, tile.row);
		while (++i < tile.max)
		{
			r->h_region_map[i] = (t_region *)malloc(size2);
			
			init_region_map(r->h_region_map[i], tile.size * tile.size, r->settings.photon_search_radius);
			// printf("region map[%d/%d]: %p\n", i, tile.max, r->h_region_map[i]);
		}
		r->update.photon_map = 0;
	}
}

static void init_region_map(t_region *region_map, size_t size, float search_rad)
{
	int i;
	
	i = -1;
	while (++i < size)
	{
		region_map[i].hit_pt = v_new(NAN, NAN, NAN);
		region_map[i].ray_dir = v_new(NAN, NAN, NAN);
		region_map[i].normal = v_new(NAN, NAN, NAN);
		region_map[i].radius = search_rad;
		region_map[i].n = 0;
		region_map[i].power = v_new(0, 0, 0);
		region_map[i].kd = NAN;
	}
}

/*
** Allocated or reallocates memory for the GPU region map used in Progressive Photon Mapping. 
*/

void	cuda_malloc_region_map_tile(t_raytracing_tools *r, t_tile tile)
{
	printf("cuda_malloc_region_map\n");
	size_t	size;

	if (r->scene->is_photon_mapping)
	{
		if (r->d_region_map)
			cudaFree(r->d_region_map);
		size = sizeof(t_region) * tile.size * tile.size;
		gpuErrchk(cudaMalloc(&(r->d_region_map), size));
	}
}

/*
** Sets tile region map variales to initial values
*/

void	refresh_region_map_tile(t_raytracing_tools *r, t_tile tile)
{
	t_region	empty;
	int			i;

	//does this need to be done on the host, or can it be done in the beginning of the kernel?
	// printf("refresh_region_map_tile\n");
	if (r->scene->is_photon_mapping)
	{
		empty.hit_pt = v_new(NAN, NAN, NAN);
		empty.ray_dir = v_new(NAN, NAN, NAN);
		empty.normal = v_new(NAN, NAN, NAN);
		empty.kd = NAN;
		i = -1;
		while (++i < tile.size * tile.size)
			gpuErrchk((cudaMemcpy((r->d_region_map + i), &empty, sizeof(t_region), cudaMemcpyHostToDevice)));
	}
}

void	copy_region_map_tile(t_raytracing_tools *r, t_tile tile)
{
	//copy over d_region_map over to corresponding h_region_map[i]
	int i;
	int current_tile;

	if (r->scene->is_photon_mapping)
	{
		current_tile = (tile.id.y) * tile.col + (tile.id.x);
		// printf("copy_region_map_tile: current tile: %d\n", current_tile);
		gpuErrchk((cudaMemcpy(r->h_region_map[current_tile], r->d_region_map, sizeof(t_region) * tile.size * tile.size, cudaMemcpyDeviceToHost)));
	}
}

void	get_region_map_tile(t_raytracing_tools *r, t_tile tile)
{
	//copy over h_region_map[i] over to d_region_map
	int i;
	int current_tile;

	if (r->scene->is_photon_mapping)
	{
		current_tile = (tile.id.y) * tile.col + (tile.id.x);
		// printf("get_region_map_tile: current tile: %d\n", current_tile);
		gpuErrchk((cudaMemcpy(r->d_region_map, r->h_region_map[current_tile], sizeof(t_region) * tile.size * tile.size, cudaMemcpyHostToDevice)));
	}
}

__device__
void	update_region_map(t_raytracing_tools *r, t_ray *cam_ray)
{
	if (r->scene->is_photon_mapping && !v_isnan(cam_ray->hit))
	{
		r->d_region_map->hit_pt = cam_ray->hit;
		r->d_region_map->ray_dir = cam_ray->dir;
		r->d_region_map->normal = v_scale(cam_ray->nhit, cam_ray->n_dir);
		r->d_region_map->kd = r->scene->objects[cam_ray->hit_obj].kd;
	}
}
