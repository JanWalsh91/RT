/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_free.cu                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:56:48 by tgros             #+#    #+#             */
/*   Updated: 2017/05/17 12:38:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.h"

int	cuda_free(t_raytracing_tools *r, int all)
{
	int i;

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
	if (r->update.photon_map == 2 || all)
	{
		i = -1;
		while (++i < r->scene->res.x * r->scene->res.y)
			cudaFree(r->scene->selected_photons[i]);
		cudaFree(r->scene->selected_photons);
	}
	return (0);
}
