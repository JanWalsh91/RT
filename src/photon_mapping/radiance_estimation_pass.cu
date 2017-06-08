/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radiance_estimation_pass.cu                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:16:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 16:36:22 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "../../inc/cuda_call.cuh"
#include <cuda.h>

__global__
static void		estimate_region_radiance(t_scene *scene, t_color *pixel_map,
				t_region *region_map, t_tile tile);
__device__
static int		photon_search(t_raytracing_tools *r, t_vec3 *power_added);
__device__
static void		update_region_values(t_raytracing_tools *r, int photons_added,
				t_vec3 power_added);
__device__
static t_vec3	add_accumulated_power(float k, t_region *region,
				t_photon photon, float rad);

void			radiance_estimation_pass(t_raytracing_tools *r, t_tile tile)
{
	dim3 		blockSize;
	dim3 		gridSize;
	int			size;

	size = (tile.size / BLOCK_DIM) + ((tile.size % BLOCK_DIM) ? 1 : 0);
	blockSize = dim3(BLOCK_DIM, BLOCK_DIM, 1);
	gridSize = dim3(size, size);
	estimate_region_radiance<<<gridSize, blockSize>>>(r->d_scene,
		r->d_pixel_map, r->d_region_map, tile);
	cuda_check_kernel_errors();
}

__global__
static void		estimate_region_radiance(t_scene *scene, t_color *pixel_map,
				t_region *region_map, t_tile tile)
{
	t_raytracing_tools	r;
	int					photons_added;
	t_vec3				power_added;

	r.pix.x = (tile.id.x * tile.size) + (blockDim.x * blockIdx.x) + threadIdx.x;
	r.pix.y = (tile.id.y * tile.size) + (blockDim.y * blockIdx.y) + threadIdx.y;
	r.scene = scene;
	r.idx = scene->res.x * r.pix.y + r.pix.x;
	r.d_region_map = &region_map[(r.pix.x % tile.size) + (r.pix.y % tile.size) *
		tile.size];
	photons_added = 0;
	power_added = v_new(0, 0, 0);
	if (r.pix.x >= scene->res.x || r.pix.y >= scene->res.y ||
		v_isnan(r.d_region_map->hit_pt))
		return ;
	photons_added = photon_search(&r, &power_added);
	update_region_values(&r, photons_added, power_added);
	pixel_map[r.idx] = c_add(pixel_map[r.idx],
		vec_to_col(v_scale(r.d_region_map->power, 1.0 /
	(float)(scene->photon_iteration * scene->photons_per_pass * M_PI *
		r.d_region_map->radius * r.d_region_map->radius))));
}

__device__
static int		photon_search(t_raytracing_tools *r, t_vec3 *power_added)
{
	int 		i;
	float		dist;
	int			photons_added;

	photons_added = 0;
	i = -1;
	while (++i < PHOTON_BOUNCE_MAX * r->scene->photons_per_pass)
	{
		if (!v_isnan(r->scene->photon_list[i].pos))
		{
			dist = v_length(v_sub(r->d_region_map->hit_pt,
				r->scene->photon_list[i].pos));
			if (r->d_region_map->radius > dist && v_dot(r->d_region_map->normal,
				r->scene->photon_list[i].n) > 0.5)
			{
				*power_added = v_add(*power_added,
					add_accumulated_power(r->scene->ppm_light_intensity,
					r->d_region_map, r->scene->photon_list[i], dist * dist));
				++photons_added;
			}
		}
	}
	return (photons_added);
}

__device__
static void		update_region_values(t_raytracing_tools *r, int photons_added,
				t_vec3 power_added)
{
	float	old_rad2;
	float	alpha;

	alpha = 2.0 / 3.0;
	if (photons_added)
	{
		old_rad2 = r->d_region_map->radius * r->d_region_map->radius;
		r->d_region_map->radius *= sqrtf((r->d_region_map->n + alpha *
			photons_added) / (r->d_region_map->n + photons_added));
		r->d_region_map->power = v_scale(v_add(r->d_region_map->power,
			power_added), r->d_region_map->radius * r->d_region_map->radius /
			old_rad2);
	}
	r->d_region_map->n += alpha * photons_added;
}

__device__
static t_vec3	add_accumulated_power(float k, t_region *region,
				t_photon photon, float dist2)
{
	t_vec3 result;

	result = v_scale(col_to_vec(photon.col), sqrtf(region->radius *
		region->radius - dist2) / (M_PI));
	result = v_scale(result, -v_dot(photon.dir, region->normal) * k *
		region->kd);
	return (result);
}
