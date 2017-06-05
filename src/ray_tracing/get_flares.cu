/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flares.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 10:18:02 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 16:28:26 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "../../inc/cuda_call.h"

static int		get_light_count(t_light *light);
__global__
static void		draw_one_flare(t_light_flare_tools *tools, t_scene *scene,
				t_color *pixel_map);

void			get_flares(t_raytracing_tools *r)
{
	int					i;
	t_light_flare_tools *tools;
	size_t				shift;
	int					light_count;

	r->t = INFINITY;
	light_count = get_light_count(r->scene->lights);
	if (!light_count)
		return ;
	cudaMalloc(&tools, sizeof(t_light_flare_tools) * light_count);
	init_light_flares_wrapper(light_count, r, tools);
	i = -1;
	shift = 0;
	while (++i < light_count)
	{
		dim3 blockSize = dim3(BLOCK_DIM, BLOCK_DIM, 1);
		dim3 gridSize = dim3(r->scene->res.x / BLOCK_DIM + 1,
			r->scene->res.y / BLOCK_DIM + 1);
		draw_one_flare<<<gridSize, blockSize>>>(tools + shift,
			r->d_scene, r->d_pixel_map);
		cuda_check_kernel_errors();
		shift++;
	}
}

static int		get_light_count(t_light *light)
{
	int				i;
	t_light			*l_ptr;

	i = 0;
	l_ptr = light;
	while (l_ptr)
	{
		++i;
		l_ptr = l_ptr->next;
	}
	return (i);
}

__global__
static void		draw_one_flare(t_light_flare_tools *tools, t_scene *scene,
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
