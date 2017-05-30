/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_map.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 17:15:06 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/30 10:57:06 by jwalsh           ###   ########.fr       */
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

static void init_region_map(t_raytracing_tools *r, size_t size);

/*
** Allocated or reallocates memory for the CPU region map used in Progressive Photon Mapping. 
*/

void	malloc_region_map(t_raytracing_tools *r)
{
	printf("malloc_region_map\n");
	size_t size;

	r->update.photon_map = 2;
	if (r->scene->is_photon_mapping && r->update.photon_map == 2)
	{
		if (r->h_region_map)
			free(r->h_region_map);
		size = sizeof(t_region) * r->scene->res.x * r->scene->res.y;
		r->h_region_map = (t_region *)malloc(size);
		printf("%p\n", r->h_region_map);
		init_region_map(r, size);
		r->update.photon_map = 0;
	}
}

static void init_region_map(t_raytracing_tools *r, size_t size)
{
	int i;
	
	i = -1;
	while (++i < size)
	{
		r->h_region_map->radius = r->settings.photon_search_radius;
		r->h_region_map->n = 0;
		r->h_region_map->power = v_new(0, 0, 0);
		r->h_region_map->kd = NAN;
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

	printf("refresh_region_map_tile\n");
	if (r->scene->is_photon_mapping)
	{
		empty.hit_pt = v_new(NAN, NAN, NAN);
		empty.ray_dir = v_new(NAN, NAN, NAN);
		empty.normal = v_new(NAN, NAN, NAN);
		empty.kd = NAN;
		i = -1;
		while (++i < tile.size * tile.size)
			gpuErrchk((cudaMemcpy(&r->d_region_map[i], &empty, sizeof(t_region), cudaMemcpyHostToDevice)));
	}
}

void	copy_region_map_tile(t_raytracing_tools *r, t_tile tile)
{
	//copy over row of a tile into global region map
	int i;
	int current_tile;
	if (r->scene->is_photon_mapping)
	{
		current_tile = tile.id.x * tile.size + tile.id.y * tile.size * tile.size;
		printf("%p, %p\n", &(r->h_region_map[current_tile + 0]), &(r->d_region_map[0]));
		printf("copy_region_map_tile: tileX: %d, tileY: %d, current_tile: %d\n", tile.id.x, tile.id.y, current_tile);
		i = -1;
		while (++i < tile.size)
			gpuErrchk((cudaMemcpy(&(r->h_region_map[current_tile + i]), &(r->d_region_map[i]), sizeof(t_region), cudaMemcpyDeviceToHost)));
	}
}