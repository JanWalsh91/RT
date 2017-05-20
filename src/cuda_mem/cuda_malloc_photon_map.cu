/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc_photon_map.cu                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:15:30 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/19 14:51:38 by jwalsh           ###   ########.fr       */
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
	
	if (r->scene->is_photon_mapping && r->update.photon_map == 2 ) 
	{
		r->scene->photon_count = 100;
		gpuErrchk(cudaMallocHost(&(r->h_d_scene->photon_list), sizeof(t_photon *) * (r->scene->photon_count + 1)));
		i = -1;
		while (++i < r->scene->photon_count)
			gpuErrchk(cudaMallocHost(&(r->h_d_scene->photon_list[i]), sizeof(t_photon) * r->scene->ray_depth));
		//SWICTH 10 WITH K (NUM OF PHOTONS TO GATHER)
		gpuErrchk(cudaMallocHost(&(r->h_d_scene->selected_photons), sizeof(t_selected_photon *) * (r->scene->res.x * r->scene->res.y)));
		i = -1;
		while (++i < r->scene->res.x * r->scene->res.y)
			gpuErrchk(cudaMallocHost(&(r->h_d_scene->selected_photons[i]), sizeof(t_selected_photon) * (10 + 1)));
		r->scene->photon_map = r->h_d_scene->photon_map;
		printf("selected_photons: [%p]\n", r->h_d_scene->selected_photons);
		printf("selected_photons: [%p]\n", r->h_d_scene->selected_photons[1]);
	}
}