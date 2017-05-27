/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_free.cu                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:56:48 by tgros             #+#    #+#             */
/*   Updated: 2017/05/26 21:42:07 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.h"

/*
**
*/

int	cuda_free(t_raytracing_tools *r, int all)
{
	int i;

	printf("cudafree\n");
	if (r->update.resolution == 2 || all)
		cudaFree(r->d_pixel_map);
	C(1)
	if (r->update.objects == 2 || all)
		cudaFree(r->h_d_scene->objects);
	C(2)
	if (r->update.lights == 2 || all)
		cudaFree(r->h_d_scene->lights);
	C(3)
	if (r->update.cameras == 2 || all)
		cudaFree(r->h_d_scene->cameras);
	C(4)
	if (r->update.scene == 2 || all)
		cudaFree(r->d_scene);
	C(5)
	printf("selected photon address: %p\n", r->scene->selected_photons);
	if ((r->update.photon_map == 2 || all) && r->scene->selected_photons)
	{
		C(6)
		i = -1;
		// while (++i < r->scene->res.x * r->scene->res.y)
			// cudaFree(r->scene->selected_photons[i]);
		cudaFree(r->scene->selected_photons);
	}
	C(7)
	return (0);
}
