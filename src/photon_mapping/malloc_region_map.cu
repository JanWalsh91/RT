/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_region_map.cu                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:14:03 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "cuda.h"
#include "../inc/cuda_call.h"

static void init_region_map(t_region *region_map, size_t size, float search_rad);

/*
** Allocated or reallocates memory for the CPU region map used in Progressive Photon Mapping. 
*/

//TODO ADD MALLOC PROTECTIONZ

void	malloc_region_map(t_raytracing_tools *r, t_tile tile)
{
	size_t	size1;
	size_t	size2;
	int		i;
	static int	old_tile_size = 0;

	if (r->scene->is_photon_mapping)
	{

		if (r->h_region_map)
		{
			i = -1;
			while (++i < old_tile_size)
				free(r->h_region_map[i]);
			free(r->h_region_map);
			old_tile_size = tile.max;
		}
		size1 = sizeof(t_region *) * tile.col * tile.row;
		size2 = sizeof(t_region) * tile.size * tile.size;
		if (!(r->h_region_map = (t_region **)malloc(size1)))
			exit(0);
		i = -1;
		while (++i < tile.max)
		{
			if (!(r->h_region_map[i] = (t_region *)malloc(size2)))
				exit(0);
			init_region_map(r->h_region_map[i], tile.size * tile.size, r->settings.photon_search_radius);
		}
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
	size_t	size;

	if (r->scene->is_photon_mapping)
	{
		if (r->d_region_map)
			cudaFree(r->d_region_map);
		size = sizeof(t_region) * tile.size * tile.size;
		gpu_errchk(cudaMalloc(&(r->d_region_map), size));
	}
}
