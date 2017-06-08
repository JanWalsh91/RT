/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_photon.cu                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 14:38:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 16:58:36 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "../../inc/cuda_call.cuh"
#include <cuda.h>
#include <curand.h>
#include <curand_kernel.h>

/*
** Kernel wrapper and kernel for shooting photon
*/

static void		init_random_numbers(int nb, float *random_numbers);
__global__
static void		shoot_photon(t_scene *scene, t_photon *init_photon_list,
				int photon_count, float *rand_numbers);
__device__
static t_ray	init_kernel_photon(t_raytracing_tools *r, t_photon photon,
				float *rand_numbers);
__device__
static void		set_default_photon_values(t_photon *p_list, int idx, int depth);

void			shoot_photon_wrapper(t_raytracing_tools *r, size_t photon_count,
				t_photon *init_photon_list)
{
	dim3		block_size;
	dim3		grid_size;
	float		*h_rand_numbers;
	float		*d_rand_numbers;
	int			rand_size;

	rand_size = r->scene->photons_per_pass * 3;
	block_size = dim3(BLOCK_DIM, 1, 1);
	grid_size = dim3(photon_count / BLOCK_DIM + 1, 1);
	h_rand_numbers = (float *)malloc(sizeof(float) * rand_size);
	test_cuda_malloc(&d_rand_numbers, sizeof(float) * rand_size);
	init_random_numbers(rand_size, h_rand_numbers);
	cudaMemcpy(d_rand_numbers, h_rand_numbers, sizeof(float) * rand_size,
		cudaMemcpyHostToDevice);
	shoot_photon<<<grid_size, block_size>>>(r->d_scene, init_photon_list,
		photon_count, d_rand_numbers);
	cuda_check_kernel_errors();
	cudaFree(d_rand_numbers);
	free(h_rand_numbers);
}

/*
** Kernel for shooting a single photon
*/

__global__
static void		shoot_photon(t_scene *scene, t_photon *init_photon_list,
				int photon_count, float *rand_numbers)
{
	t_raytracing_tools	r;
	t_ray				photon;
	curandState			state;

	r.pix.x = 0;
	r.pix.y = 0;
	r.scene = scene;
	r.idx = (blockDim.x * blockIdx.x) + threadIdx.x;
	r.rand_list = rand_numbers;
	if (r.idx >= photon_count)
		return ;
	r.devStates = &state;
	curand_init(rand_numbers[0], r.idx % (int)rand_numbers[0], r.idx *
		rand_numbers[0], r.devStates);
	memset(&r.ior_list, 0, sizeof(float) * (PHOTON_BOUNCE_MAX + 1));
	photon = init_kernel_photon(&r, init_photon_list[r.idx], rand_numbers);
	if (photon.col.r + photon.col.g + photon.col.b > 20)
		cast_primary_ray(&r, &photon);
}

__device__
static t_ray	init_kernel_photon(t_raytracing_tools *r, t_photon photon,
				float *rand_numbers)
{
	t_ray		new_ray;

	new_ray.dir.x = rand_numbers[r->idx];
	new_ray.dir.y = rand_numbers[r->idx + 1];
	new_ray.dir.z = rand_numbers[r->idx + 2];
	new_ray.dir = v_norm(new_ray.dir);
	new_ray.type = R_DIRECT_PHOTON;
	new_ray.origin = photon.pos;
	new_ray.col = photon.col;
	new_ray.nhit = photon.n;
	new_ray.n_dir = 1;
	new_ray.depth = r->scene->ray_depth;
	new_ray.ior = r->scene->cameras->ior;
	r->ior_list[0] = r->scene->cameras->ior;
	set_default_photon_values(r->scene->photon_list, r->idx,
		r->scene->ray_depth);
	return (new_ray);
}

__device__
static void		set_default_photon_values(t_photon *p_list, int idx, int depth)
{
	int i;

	i = 0;
	while (i < depth && i < PHOTON_BOUNCE_MAX)
	{
		p_list[idx * PHOTON_BOUNCE_MAX + i].pos = v_new(NAN, NAN, NAN);
		p_list[idx * PHOTON_BOUNCE_MAX + i].dir = v_new(NAN, NAN, NAN);
		p_list[idx * PHOTON_BOUNCE_MAX + i].n = v_new(NAN, NAN, NAN);
		p_list[idx * PHOTON_BOUNCE_MAX + i].col = c_new(0, 0, 0);
		++i;
	}
}

static void		init_random_numbers(int nb, float *random_numbers)
{
	int i;

	i = -1;
	while (++i < nb)
		random_numbers[i] = (((float)rand()) / (float)INT_MAX) - 0.5;
}
