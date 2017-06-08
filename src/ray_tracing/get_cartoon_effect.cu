/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cartoon_effect.cu                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:55:19 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 12:26:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../../inc/cuda_call.h"

/*
** cartoontools: 
** x: bin_size
** y: tolerance
** z: radius_filter
*/
__global__
void	cartoonize(t_scene *scene, t_color *pixel_map, t_vec3 c);
__device__
void	create_edges(t_scene *scene, t_color *pixel_map, t_vec3 c, t_pt2 pix);
__device__
void	reset_values(int *f, t_dpt2 comp[3]);
__device__
void	add_colors(t_dpt2 comp[3], t_color *pixel_map, int i1, int i2);
__device__
bool	high_contrast(t_dpt2 comp[3], float tolerance);
__device__
void	set_black(t_color *pix, int x);

void	get_cartoon_effect(t_raytracing_tools *r, t_vec3 cartoon_tools)
{
	dim3			block_size;
	dim3			grid_size;
	
	block_size = dim3(32, 32, 1);
	grid_size = dim3(r->scene->res.x / 32 + 1, r->scene->res.y / 32 + 1);
	cartoonize<<<grid_size, block_size>>>(r->d_scene, r->d_pixel_map, cartoon_tools);
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
	// pixel_map[idx] = c_new(255, 0, 0);
	// C(1)
	__syncthreads();
	// C(2)
	// create_edges(scene, pixel_map, c, pix);
}

__device__
bool	high_contrast2(t_dpt2 comp[3], float tolerance)
{
	if (fabs(comp[0].x - comp[0].y) > tolerance ||
		fabs(comp[1].x - comp[1].y) > tolerance ||
		fabs(comp[2].x - comp[2].y) > tolerance)
		{
			// printf("fabs 1 : %f vs %f\n", fabs(comp[0].x - comp[0].y), tolerance);
			// printf("fabs 2 : %f vs %f\n", fabs(comp[1].x - comp[1].y), tolerance);
			// printf("fabs 3 : %f vs %f\n", fabs(comp[2].x - comp[2].y), tolerance);
		return (true);
		}
	return (false);
}

__device__
void	create_edges(t_scene *scene, t_color *pixel_map, t_vec3 c, t_pt2 pix)
{
	int		idx;
	int 	f;
	t_dpt2	comp[3];
	bool	is_black;

	reset_values(&f, comp);
	idx = scene->res.x * pix.y + pix.x;
	is_black = 0;
	while (++f < c.z)
		if (pix.x - f > 0 && pix.x + f < scene->res.x)
			add_colors(comp, pixel_map, idx - f, idx + f);
	if (high_contrast(comp, c.y))
		is_black = 1;
	reset_values(&f, comp);
	f = 0;
	while (++f < c.z && !is_black)
		if (pix.y - f > 0 && pix.y + f < scene->res.y)
			add_colors(comp, pixel_map, idx - f * scene->res.x, idx + f * scene->res.x);
	if (high_contrast(comp, c.y))
	{
		// printf("set black: [%d, %d]\n", pix.x, pix.y);
		is_black = 1;
	}
	__syncthreads();
	return (set_black(&pixel_map[idx], is_black));
}

__device__
void	reset_values(int *f, t_dpt2 comp[3])
{
	*f = 0;
	comp[0].x = 0;
	comp[0].y = 0;
	comp[1].x = 0;
	comp[1].y = 0;
	comp[2].x = 0;
	comp[2].y = 0;
}

__device__
void	add_colors(t_dpt2 comp[3], t_color *pixel_map, int i1, int i2)
{
	comp[0].x += (float)pixel_map[i1].r;
	comp[0].y += (float)pixel_map[i2].r;
	comp[1].x += (float)pixel_map[i1].g;
	comp[1].y += (float)pixel_map[i2].g;
	comp[2].x += (float)pixel_map[i1].b;
	comp[2].y += (float)pixel_map[i2].b;
}

__device__
bool	high_contrast(t_dpt2 comp[3], float tolerance)
{
	if (comp[0].x - comp[0].y < -tolerance ||
		comp[1].x - comp[1].y < -tolerance ||
		comp[2].x - comp[2].y < -tolerance)
	{
			// printf("high contraSt\n");
		return (true);
	}
	if (comp[1].x - comp[1].y < -tolerance)
	{
		// return (true);
	}
	return (false);
}


__device__
void	set_black(t_color *pix, int x)
{
	if (x)
		*pix = c_new(0, 0, 0);
}