/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radiance_estimation_pass.cu                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:16:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/30 10:56:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "photon_mapping.h"
#include "rt.cuh"
#include "../../inc/cuda_call.h"
#include <cuda.h>
#include <curand.h>
#include <curand_kernel.h>

#define N 32
#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

void	radiance_estimation_pass(t_raytracing_tools *r)
{
	printf("radiance_estimation_pass\n");
	// dim3 		blockSize;
	// dim3 		gridSize;

	// //prepare kernel
	// blockSize = dim3(BLOCK_DIM, BLOCK_DIM, 1);
	// gridSize = dim3(r->scene->res.x / BLOCK_DIM, r->scene->res.y / BLOCK_DIM);
	// estimate_region_radiance<<<gridSize, blockSize>>>(r->d_scene, r->d_pixel_map, r->d_region_map);
}

// __global__
// void	estimate_region_radiance(t_scene *scene, t_color *pixel_map, t_region *region_map)
// {
// 	t_raytracing_tools	r;

// 	r.pix.x = (blockDim.x * blockIdx.x) + threadIdx.x;
// 	r.pix.y = (blockDim.y * blockIdx.y) + threadIdx.y;
// 	r.scene = scene;
//     r.idx = scene->res.x * r.pix.y + r.pix.x;
// }