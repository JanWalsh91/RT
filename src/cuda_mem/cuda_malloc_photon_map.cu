/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc_photon_map.cu                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:15:30 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/22 11:07:55 by jwalsh           ###   ########.fr       */
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

void	cuda_malloc_photon_map(t_raytracing_tools *r)
{
	int i;
	
	// printf("cuda_malloc_photon_map: is_photon_mapping: [%d], r->update.photon_map: [%d]\n", r->scene->is_photon_mapping, r->update.photon_map);
	// printf("selected photon address: %p\n", r->scene->selected_photons);
	if (r->scene->is_photon_mapping && r->update.photon_map == 2 ) 
	{
		gpuErrchk(cudaMallocHost(&(r->h_d_scene->photon_list), sizeof(t_photon *) * (r->scene->photon_count + 1)));
		// printf("size of photon: %lu\n", sizeof(t_photon));
		i = -1;
		while (++i < r->scene->photon_count)
			gpuErrchk(cudaMallocHost(&(r->h_d_scene->photon_list[i]), sizeof(t_photon) * r->scene->ray_depth));
		//SWICTH 10 WITH K (NUM OF PHOTONS TO GATHER)
		gpuErrchk(cudaMallocHost(&(r->h_d_scene->selected_photons), sizeof(t_selected_photon *) * (r->scene->res.x * r->scene->res.y)));
		i = -1;
		while (++i < r->scene->res.x * r->scene->res.y)
			gpuErrchk(cudaMallocHost(&(r->h_d_scene->selected_photons[i]), sizeof(t_selected_photon) * (10 + 1)));
		r->scene->photon_map = r->h_d_scene->photon_map;
		// printf("selected_photons: [%p]\n", r->h_d_scene->selected_photons);
		// printf("selected_photons: [%p]\n", r->h_d_scene->selected_photons[1]);
	}
	// printf("selected photon address: %p\n", r->scene->selected_photons);
	// printf("end cuda_malloc_photon_map\n");
}