/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_mapping.cu                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:56:52 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/30 10:59:14 by jwalsh           ###   ########.fr       */
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

// TO DO add interaction with user to be able to stop

void	render_ppm(t_raytracing_tools *r)
{
	printf("render_ppm\n");
	int	photons_shot;
	
	photons_shot = 0;
	r->settings.photon_count_per_pass = 10;

	//malloc space for photons on GPU
	gpuErrchk(cudaMalloc(&(r->h_d_scene->photon_list), sizeof(t_photon) * PHOTON_BOUNCE_MAX * r->settings.photon_count_per_pass));
	gpuErrchk(cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice));
	while (photons_shot < r->scene->photon_count)
	{
		//photon_mapping_pass
		photon_mapping_pass(r);
		//radiance estimation pass
		radiance_estimation_pass(r);
		//reset photon map // necessary? will be set to 0 inside the kernel anyway...
		photons_shot += r->settings.photon_count_per_pass;
	}
	cudaFree(r->h_d_scene->photon_list);
}

// static void	reset_photon_map(t_raytracing_tools *r)
// {
// 	cudaFree(r->h_d_scene->photon_list);
// 	gpuErrchk(cudaMalloc(&(r->h_d_scene->photon_list), sizeof(t_photon) * PHOTON_BOUNCE_MAX * r->settings.photon_count_per_pass));
// 	gpuErrchk(cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice));	
// }