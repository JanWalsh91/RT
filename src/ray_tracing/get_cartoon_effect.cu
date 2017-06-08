/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cartoon_effect.cu                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:55:19 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 21:18:48 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../../inc/cuda_call.cuh"

/*
** cartoontools: 
** x: bin_size
** y: tolerance
** z: radius_filter
*/

__global__
void	cartoonize(t_scene *scene, t_color *pixel_map, t_vec3 c);

void	get_cartoon_effect(t_raytracing_tools *r)
{
	dim3			block_size;
	dim3			grid_size;
	t_vec3			cartoon_tools;

	cartoon_tools = v_new(45, 50, 2);
	block_size = dim3(32, 32, 1);
	grid_size = dim3(r->scene->res.x / 32 + 1, r->scene->res.y / 32 + 1);
	cartoonize<<<grid_size, block_size>>>(r->d_scene, r->d_pixel_map,
		cartoon_tools);
	cuda_check_kernel_errors();
}
__global__
void	cartoonize(t_scene *scene, t_color *pixel_map, t_vec3 c)
{
	t_pt2	pix;
	int		idx;

	pix.x = blockDim.x * blockIdx.x + threadIdx.x;
	pix.y = blockDim.y * blockIdx.y + threadIdx.y;
	idx = scene->res.x * pix.y + pix.x;
	if (pix.x >= scene->res.x || pix.y >= scene->res.y)
		return ;
	pixel_map[idx].r = pixel_map[idx].r - pixel_map[idx].r % (int)c.x;
	pixel_map[idx].g = pixel_map[idx].g - pixel_map[idx].g % (int)c.x;
	pixel_map[idx].b = pixel_map[idx].b - pixel_map[idx].b % (int)c.x;
	__syncthreads();
}
