/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc_camera.cu                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:13:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/18 16:14:28 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
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

void		cuda_malloc_camera(t_raytracing_tools *r)
{
	if (r->update.cameras >= 1)
	{
		if (r->update.cameras == 2)
			gpuErrchk(cudaMalloc(&(r->h_d_scene->cameras), sizeof(t_camera)));
		if (r->scene->is_3d) // l'enlever si on decoche l'opt 3d
			r->scene->cameras->filter = F_LEFT_RED;
		gpuErrchk((cudaMemcpy(r->h_d_scene->cameras, r->scene->cameras, sizeof(t_camera), cudaMemcpyHostToDevice)));
	}
}