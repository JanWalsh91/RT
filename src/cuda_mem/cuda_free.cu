/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_free.cu                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:56:48 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 14:14:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.cuh"

/*
** Frees lists malloc'ed with cudaMalloc.
*/

int	cuda_free(t_raytracing_tools *r, int all)
{
	if (r->update.resolution == 2 || all)
		cudaFree(r->d_pixel_map);
	if (r->update.objects == 2 || all)
		cudaFree(r->h_d_scene->objects);
	if (r->update.lights == 2 || all)
		cudaFree(r->h_d_scene->lights);
	if (r->update.cameras == 2 || all)
		cudaFree(r->h_d_scene->cameras);
	if (r->update.scene == 2 || all)
		cudaFree(r->d_scene);
	return (0);
}
