/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_malloc_camera.cu                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:13:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/06 11:00:48 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.h"

/*
** Allocated memory on the device for the first camera.
*/

bool		cuda_malloc_camera(t_raytracing_tools *r)
{
	if (r->update.cameras >= 1)
	{
		if (r->update.cameras == 2)
		{
			if(test_cuda_malloc((void **)(&r->h_d_scene->cameras), sizeof(t_camera)) == false)
				return(false);
		}
		if (r->scene->is_3d)
			r->scene->cameras->filter = F_LEFT_RED;
		gpu_errchk((cudaMemcpy(r->h_d_scene->cameras, r->scene->cameras,
			sizeof(t_camera), cudaMemcpyHostToDevice)));
	}
	return(true);
}
