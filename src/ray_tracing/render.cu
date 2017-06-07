/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/07 20:58:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "../../inc/cuda_call.h"

/*
** Calls on the render_pixel kernel to update the d_pixel_map.
*/

__device__
void	render_without_aa(t_raytracing_tools *r);
__device__
void	render_with_aa(t_raytracing_tools *r);
__global__
void	render_pixel(t_scene *scene, t_color *d_pixel_map, t_region *region_map,
		t_tile tile);
void	create_anaglyph_wrapper(t_raytracing_tools *r, dim3 block_size,
		dim3 grid_size, t_tile tile);

void	render(t_raytracing_tools *r, t_tile tile)
{
	dim3			block_size;
	dim3			grid_size;
	int			size;

	size = (tile.size / BLOCK_DIM) + ((tile.size % BLOCK_DIM) ? 1 : 0);
	block_size = dim3(BLOCK_DIM, BLOCK_DIM, 1);
	grid_size = dim3(size, size);
	printf("launch kernel:\n");
	render_pixel<<<grid_size, block_size>>>(r->d_scene, r->d_pixel_map,
		r->d_region_map, tile);
	cuda_check_kernel_errors();
	printf("end kernel\n");
	if (r->scene->is_3d)
		create_anaglyph_wrapper(r, block_size, grid_size, tile);
}

/*
** Kernel to render a single pixel.
*/

__global__
void	render_pixel(t_scene *scene, t_color *d_pixel_map, t_region *region_map,
		t_tile tile)
{
	t_raytracing_tools	r;

	r.pix.x = (tile.id.x * tile.size) + (blockDim.x * blockIdx.x) + threadIdx.x;
	r.pix.y = (tile.id.y * tile.size) + (blockDim.y * blockIdx.y) + threadIdx.y;
	r.scene = scene;
	r.idx = scene->res.x * r.pix.y + r.pix.x;
	r.d_pixel_map = d_pixel_map;
	if (r.pix.x < scene->res.x && r.pix.y < scene->res.y)
	{
		if (r.scene->is_photon_mapping)
		{
			r.d_region_map = &region_map[(r.pix.x % tile.size) +
				(r.pix.y % tile.size) * tile.size];
		}
		(scene->is_aa == 1 || r.scene->is_photon_mapping) ?
			render_without_aa(&r) :
			render_with_aa(&r);
	}
}

__device__
void	render_without_aa(t_raytracing_tools *r)
{
	t_dpt2	i;
	t_ray	cam_ray;

	i.x = 0.5;
	i.y = 0.5;
	memset(&r->ior_list, 0, sizeof(float) * (MAX_RAY_DEPTH + 1));
	cam_ray = init_camera_ray(r, i);
	r->d_pixel_map[r->idx] = filter(cast_primary_ray(r, &cam_ray),
		r->scene->cameras->filter);
	__syncthreads();
	update_region_map(r, &cam_ray);
}

__device__
void	render_with_aa(t_raytracing_tools *r)
{
	t_dpt2	aa_i;
	t_ray	cam_ray;
	int		i;
	t_vec3	average;
	float	sample_size;

	sample_size = 1 / (float)r->scene->is_aa;
	aa_i.x = 0.0;
	aa_i.y = 0.0;
	i = -1;
	average = v_new(0, 0, 0);
	while (++i < r->scene->is_aa * r->scene->is_aa)
	{
		aa_i.x += sample_size;
		if (i % (r->scene->is_aa - 1) == 0)
			aa_i.x = 0.0;
		if (i % (r->scene->is_aa - 1) == 0)
			aa_i.y += sample_size;
		memset(&r->ior_list, 0, sizeof(float) * (MAX_RAY_DEPTH + 1));
		cam_ray = init_camera_ray(r, aa_i);
		average = v_add(average, col_to_vec(cast_primary_ray(r, &cam_ray)));
	}
	average = v_scale(average, 1 / (float)(r->scene->is_aa * r->scene->is_aa));
	r->d_pixel_map[r->idx] = filter(vec_to_col(average),
		r->scene->cameras->filter);
}

