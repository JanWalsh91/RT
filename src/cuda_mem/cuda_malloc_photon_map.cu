/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc_photon_map.cu                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:15:30 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/26 21:33:33 by jwalsh           ###   ########.fr       */
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
	int	i;
	int	res;

	if (r->scene->is_photon_mapping && r->update.photon_map == 2) 
	{
		res = (r->scene->res.x * r->scene->res.y);
		
		printf("cuda_malloc_photon_map\n");
		gpuErrchk(cudaMallocHost(&(r->h_d_scene->photon_list), sizeof(t_photon) * PHOTON_BOUNCE_MAX * r->scene->photon_count));
		printf("Size mallocated : %lu\n", sizeof(t_photon[PHOTON_GATHER_MAX]) * (r->scene->photon_count + 1));
		//list of photons we gather per thread.
		gpuErrchk(cudaMallocHost(&(r->h_d_scene->selected_photons), sizeof(t_selected_photon) * PHOTON_GATHER_MAX * res));
		printf("END cuda_malloc_photon_map\n");
		// exit(0);
	}
}
