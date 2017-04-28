/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_free.cu                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:56:48 by tgros             #+#    #+#             */
/*   Updated: 2017/04/28 16:51:52 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.h"

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
