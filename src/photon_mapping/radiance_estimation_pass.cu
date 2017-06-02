/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radiance_estimation_pass.cu                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:16:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/02 12:14:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "photon_mapping.h"
#include "rt.cuh"
#include "../../inc/cuda_call.h"
#include <cuda.h>
#include <curand.h>
#include <curand_kernel.h>

#define N 32
#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}
__device__
static void		update_photon_count(int *photon_count, float photons_added);
__device__
static void		update_radius(t_raytracing_tools *r, float *radius, float photon_count, float photons_added);
__device__
static t_vec3	add_accumulated_power(t_region *region, t_photon photon, float rad);
__device__
static void		udpate_accumulated_power(t_vec3 *pow, t_vec3 new_pow, float rad2);

__global__
void	estimate_region_radiance(t_scene *scene, t_color *pixel_map, t_region *region_map, t_tile tile)
{
	t_raytracing_tools	r;
	int					i;
	int					i2;
	int					photons_added;
	float				dist;
	t_vec3				power_added;
	
	r.pix.x = (tile.id.x * tile.size) + (blockDim.x * blockIdx.x) + threadIdx.x;
	r.pix.y = (tile.id.y * tile.size) + (blockDim.y * blockIdx.y) + threadIdx.y;
	r.scene = scene; 
    r.idx = scene->res.x * r.pix.y + r.pix.x;
	i2 = (r.pix.x % tile.size) + (r.pix.y % tile.size) * tile.size;
	photons_added = 0;
	power_added = v_new(0, 0, 0);
	if (r.pix.x >= scene->res.x || r.pix.y >= scene->res.y || v_isnan(region_map[i2].hit_pt))
		return ;
	// printf("iteration: %d\n", scene->photon_iteration);
	if (r.idx == 0 && scene->photon_iteration == 1)
	{
		t_vec3 normalized_power = v_scale(region_map[0].power, 1.0 / (float)(scene->photon_iteration * scene->photon_count_per_pass * M_PI * region_map[0].radius * region_map[0].radius));

		printf("\nregion intialization: iteration: [%d]\
			\n\tphotons added: [%d]\
			\n\thit_pt: [%f, %f, %f]\
			\n\tray_dir: [%f, %f, %f]\
			\n\tnormal: [%f, %f, %f]\
			\n\tkd: [%f]\
			\n\tradius: [%f]\
			\n\tphoton count: [%d]\
			\n\taccumulated power: [%f, %f, %f]\n\n",
			scene->photon_iteration,
			photons_added,
			region_map[0].hit_pt.x, region_map[0].hit_pt.y, region_map[0].hit_pt.z,
			region_map[0].ray_dir.x, region_map[0].ray_dir.y, region_map[0].ray_dir.z,
			region_map[0].normal.x, region_map[0].normal.y, region_map[0].normal.z,
			region_map[0].kd,
			region_map[0].radius,
			region_map[0].n,
			region_map[0].power.x, region_map[0].power.y, region_map[0].power.z
		);
	}
		// printf("---rad entering kernel: %f\n", region_map[0].radius);
	// printf("idx: [%d] i2: [%d]\n", r.idx, i2);
	i = -1;
	// printf("pcpp: %d, rad: %f\n", r.scene->photon_count_per_pass, region_map[i2].radius);
	while (++i < PHOTON_BOUNCE_MAX * r.scene->photon_count_per_pass)
	{
		// printf("POSITION DU PHOTON: %f, %f, %f\n", scene->photon_list[i].pos.x, scene->photon_list[i].pos.y, scene->photon_list[i].pos.z);
		if (!v_isnan(scene->photon_list[i].pos))
		{
			dist = v_length(v_sub(region_map[i2].hit_pt, scene->photon_list[i].pos));
			// printf("%d: dist: %f rad: %f\n", r.idx, dist, region_map[i2].radius);
			if (region_map[i2].radius > dist)
			{
				// if (r.pix.x == 100 && r.pix.y == 100)
				// {
				// 	printf("r.idx: %d, hit pt: [%f, %f, %f], photon: [%f, %f, %f], rad: %f dist: %f\n", r.idx, region_map[i2].hit_pt.x, region_map[i2].hit_pt.y, region_map[i2].hit_pt.z, scene->photon_list[i].pos.x, scene->photon_list[i].pos.y, scene->photon_list[i].pos.z, region_map[i2].radius, dist);
				// }
				
				power_added = v_add(power_added, add_accumulated_power(&region_map[i2], scene->photon_list[i], dist * dist));
				// printf("power: [%f, %f, %f]\n", power_added.x, power_added.y, power_added.z);
				++photons_added;
			}
		}
		__syncthreads();
	}
	if (photons_added)
		udpate_accumulated_power(&region_map[i2].power, power_added, region_map[i2].radius * region_map[i2].radius);
	// if (r.idx == 0)
	// {
	// 	// float r = region_map[0].radius;
	// 	printf("before update radius: rad: %f, photon_count: %d, photons_added: %d, %p\n", region_map[0].radius, region_map[0].n, photons_added, &region_map[0].radius);
	// }
	if (photons_added)
		update_radius(&r, &region_map[i2].radius, region_map[i2].n, photons_added);
	// if (r.idx == 0)
	// {
	// 	// printf("--- photons_added: %d, rad in kernel: %f --> %f, %p\n", photons_added, r, region_map[0].radius, &region_map[0].radius);
	// 	printf("before update radius: rad: %f, photon_count: %d, photons_added: %d, %p\n", region_map[0].radius, region_map[0].n, photons_added, &region_map[0].radius);
	// }
	update_photon_count(&region_map[i2].n, photons_added);
	//put in r->rt_pixel_map[index]
	t_color tmp = pixel_map[r.idx];
	// pixel_map[r.idx] = c_new(0, 110, 110);
	// printf("photon_iter: %lu, count per pass: %lu\n", scene->photon_iteration, scene->photon_count_per_pass);
	pixel_map[r.idx] = c_add(pixel_map[r.idx], vec_to_col(v_scale(region_map[i2].power, 1.0 / (float)(scene->photon_iteration * scene->photon_count_per_pass * M_PI * region_map[i2].radius * region_map[i2].radius))));
	// if (r.idx % 500 == 0)
	// printf("power: [%f, %f, %f]\n", region_map[i2].power.x, region_map[i2].power.y, region_map[i2].power.z);
	// printf("idx: [%d]. old color: [%d, %d, %d], new color: [%d, %d, %d]\n", r.idx, tmp.r, tmp.g, tmp.b, pixel_map[r.idx].r, pixel_map[r.idx].g, pixel_map[r.idx].b);
	if (r.idx == 0)
	{
		t_vec3 normalized_power = v_scale(region_map[0].power, 1.0 / (float)(scene->photon_iteration * scene->photon_count_per_pass * M_PI * region_map[0].radius * region_map[0].radius));

		printf("\nupdated region: iteration: [%d]\
			\n\tphoton count per pass: [%d]\
			\n\tphotons added: [%d]\
			\n\thit_pt: [%f, %f, %f]\
			\n\tray_dir: [%f, %f, %f]\
			\n\tnormal: [%f, %f, %f]\
			\n\tkd: [%f]\
			\n\tradius: [%f]\
			\n\tphoton count: [%d]\
			\n\taccumulated power: [%f, %f, %f]\
			\n\tnormalized_power: [%f, %f, %f]\n\n",
			scene->photon_iteration,
			scene->photon_count_per_pass,
			photons_added,
			region_map[0].hit_pt.x, region_map[0].hit_pt.y, region_map[0].hit_pt.z,
			region_map[0].ray_dir.x, region_map[0].ray_dir.y, region_map[0].ray_dir.z,
			region_map[0].normal.x, region_map[0].normal.y, region_map[0].normal.z,
			region_map[0].kd,
			region_map[0].radius,
			region_map[0].n,
			region_map[0].power.x, region_map[0].power.y, region_map[0].power.z,
			normalized_power.x, normalized_power.y, normalized_power.z
		);
	}
	__syncthreads();
}

__device__
static t_vec3	add_accumulated_power(t_region *region, t_photon photon, float rad2)
{
	// printf("update_accumulated_power\n");
	t_vec3 result;
	float k = 1; ///

	result = v_scale(col_to_vec(photon.col), 1 / (M_PI * rad2));
	result = v_scale(result, -v_dot(region->ray_dir, photon.n) * k * region->kd);
	// printf("add accumulated power: [%f, %f, %f]\n", result.x, result.y, result.z);
	return (result);
}

__device__
static void		udpate_accumulated_power(t_vec3 *pow, t_vec3 new_pow, float rad2)
{
	// printf("update_accumulated_power\n");
	// new_pow = v_scale(*pow, 1 / (M_PI * rad2));
	*pow = v_scale(v_add(*pow, new_pow), ((rad2 + 1) / (rad2)));
}

__device__
static void		update_radius(t_raytracing_tools *r, float *radius, float photon_count, float photons_added)
{
	// printf("update_radius\n");
	*radius *= sqrtf((photon_count + (2.0 / 3.0) * photons_added) / (photon_count + photons_added));
	// if (r->idx == 0)
	// 	printf("after : %f\n", *rad);
}

__device__
static void		update_photon_count(int *photon_count, float photons_added)
{
	// printf("update_photon_count\n");
	*photon_count += (2.0 / 3.0) * photons_added;
}

void			radiance_estimation_pass(t_raytracing_tools *r, t_tile tile)
{
	// printf("radiance_estimation_pass\n");
	dim3 		blockSize;
	dim3 		gridSize;
	int			size;

	// printf("a-----photon_iter: %d, count per pass: %d\n", r->scene->photon_iteration, r->scene->photon_count_per_pass);
	size = (tile.size / BLOCK_DIM) + ((tile.size % BLOCK_DIM) ? 1 : 0);
	blockSize = dim3(BLOCK_DIM, BLOCK_DIM, 1);
	gridSize = dim3(size, size);
	estimate_region_radiance<<<gridSize, blockSize>>>(r->d_scene, r->d_pixel_map, r->d_region_map, tile);
			cudaError_t errSync  = cudaGetLastError();
cudaError_t errAsync = cudaDeviceSynchronize();
if (errSync != cudaSuccess) 
  printf("Sync kernel error: %s\n", cudaGetErrorString(errSync));
if (errAsync != cudaSuccess)
  printf("Async kernel error: %s\n", cudaGetErrorString(errAsync));
	//add cuda debug
}
