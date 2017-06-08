/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_one_flare.cu                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 10:18:02 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 14:14:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cuda_call.cuh"
#include "rt.cuh"
#include "cuda_runtime.h"

__global__
void		draw_one_flare(t_light_flare_tools *tools, t_scene *scene,
				t_color *pixel_map);

void	draw_one_flare_wrapper(t_raytracing_tools *r, t_light_flare_tools *tools, int light_count)
{
	int i;
	size_t shift;
	dim3 grid_size;
	dim3 block_size;

	i = -1;
	shift = 0;
	while (++i < light_count)
	{
		block_size = dim3(BLOCK_DIM, BLOCK_DIM, 1);
		grid_size = dim3(r->scene->res.x / BLOCK_DIM + 1,
			r->scene->res.y / BLOCK_DIM + 1);
		draw_one_flare<<<grid_size, block_size>>>(tools + shift,
			r->d_scene, r->d_pixel_map);
		cuda_check_kernel_errors();
		shift++;
	}
}

__global__
void		draw_one_flare(t_light_flare_tools *tools, t_scene *scene,
				t_color *pixel_map)
{
	t_pt2	pix;
	float	rad;
	t_color	col;

	pix.x = (blockDim.x * blockIdx.x) + threadIdx.x;
	pix.y = (blockDim.y * blockIdx.y) + threadIdx.y;
	if (pix.x < tools->pos.x - tools->max_rad ||
		pix.x > tools->pos.x + tools->max_rad ||
		pix.y < tools->pos.y - tools->max_rad ||
		pix.y > tools->pos.y + tools->max_rad ||
		pix.x < 0 || pix.x >= scene->res.x || pix.y < 0 ||
		pix.y >= scene->res.y || !tools->is_valid)
		return ;
	rad = sqrt(powf((tools->pos.x - pix.x), 2) +
		powf((tools->pos.y - pix.y), 2));
	col = pixel_map[pix.y * scene->res.x + pix.x];
	col = c_add(col, c_scale(vec_to_col(tools->light->col),
		((tools->max_rad - rad) /
		(tools->max_rad * rad)) * tools->light->kflare));
	pixel_map[pix.y * scene->res.x + pix.x] = col;
}