/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc_camera.cu                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:13:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 10:58:57 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.h"

/*
** Allocated memory on the device for the first camera.
*/

void		cuda_malloc_camera(t_raytracing_tools *r)
{
	if (r->update.cameras >= 1)
	{
		if (r->update.cameras == 2)
			gpu_errchk(cudaMalloc(&(r->h_d_scene->cameras), sizeof(t_camera)));
		if (r->scene->is_3d)
			r->scene->cameras->filter = F_LEFT_RED;
		gpu_errchk((cudaMemcpy(r->h_d_scene->cameras, r->scene->cameras,
			sizeof(t_camera), cudaMemcpyHostToDevice)));
	}
}
