/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_photon_map.cu                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:48:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 10:28:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "photon_mapping.h"
#include "rt.cuh"
#include "../../inc/cuda_call.h"
#include <cuda.h>
#include <curand.h>
#include <curand_kernel.h>

void			print_photons(t_kd_tree *tree);
static int		shoot_photon_group(t_raytracing_tools *r, size_t photon_count);
static void		init_photon_group(t_raytracing_tools *r, size_t photon_count, t_photon *init_photon_list);
static float	get_total_intensity(t_light *lights);
static void		init_photon(t_photon *photon, t_light *light);
static void		shoot_photon_wrapper(t_raytracing_tools *r, size_t photon_count, t_photon *init_photon_list);
__global__
static void		shoot_photon(t_scene *scene, t_photon *init_photon_list, int photon_count, float rand_numbers[]);
__device__
static t_ray	init_kernel_photon(t_raytracing_tools *r, t_photon photon, float rand_numbers[]);

/*
** Frees previous photon map, shoots photons, creates and sorts the tree.
*/

void			update_photon_map(t_raytracing_tools *r)
{
	printf("update_photon_map\n");
	int			ret;
	t_kd_tree 	*sorted;
	
	// srand(time(NULL));
	ret = shoot_photon_group(r, r->scene->photon_count);
	
	if (r->scene->photon_kd_tree)
		free_kd_tree(r->scene->photon_kd_tree);
	r->scene->photon_kd_tree = NULL;
	create_kd_tree(r->h_d_scene->photon_list, &r->scene->photon_kd_tree, r->scene->photon_count);
	// exit(0);
	// // printf("-----%p and %p\n", r->scene->photon_kd_tree, r->d_scene->photon_kd_tree);
	// // exit(0);
	sorted = NULL;
	sort_kd_tree(&r->scene->photon_kd_tree, 0, &sorted); // CAUSES SEGFAULT
	// exit(0);
	// r->scene->photon_kd_tree = sorted;
	// printf("done creating photon map\n");
	t_kd_tree *p = sorted;
	// printf("first photon: pos: [%f, %f, %f], dir: [%f, %f, %f], col: [%d, %d, %d], n: [%f, %f, %f]\n",
	// p->pos.x, p->pos.y, p->pos.z, p->dir.x, p->dir.y, p->dir.z, p->col.r, p->col.g, p->col.b, p->n.x, p->n.y, p->n.z);

	// print_photons(r->scene->photon_kd_tree); 
}

static int	shoot_photon_group(t_raytracing_tools *r, size_t photon_count)
{
	// printf("shoot_photon_group\n");
	t_photon	*init_photon_list;
	cudaError_t		code;

	if ((code = cudaMallocHost(&init_photon_list, sizeof(t_photon) * photon_count)))
	{
		printf("shoot_photon group malloc fail: %s, %d\n", cudaGetErrorString(code), code);
		exit(1);
		 
		//if cudaMalloc fails...
		// return (shoot_photon_group(r, photon_count / 2) +
		// shoot_photon_group(r, photon_count / 2));
	}
	init_photon_group(r, photon_count, init_photon_list);
	shoot_photon_wrapper(r, photon_count, init_photon_list);
	// cudaFree(init_photon_list); // CAUSES INVALID DEVICE POINTER
	return (photon_count);
}

static void		init_photon_group(t_raytracing_tools *r, size_t photon_count, t_photon *init_photon_list)
{
	// printf("init_photon_group\n");
	t_light		*l_ptr;
	float		total_intensity;
	float 		ratio;
	int			i;
	
	total_intensity = get_total_intensity(r->scene->lights);
	l_ptr = r->scene->lights;
	ratio = 0;
	i = -1;
	while (l_ptr)
	{
		if (v_isnan(l_ptr->pos))
			continue ;
		//get ratio of photons to shoot for one light
		ratio += photon_count * l_ptr->intensity / total_intensity;
		//while photon count within ratio
		while (++i < ratio)
			//init the photon
			init_photon((init_photon_list + i), l_ptr);
		l_ptr = l_ptr->next;
	}
}		

static float	get_total_intensity(t_light *lights)
{
	// printf("get_total_intensity\n");
	t_light		*l_ptr;
	float		total_intensity;
	
	l_ptr = lights;
	total_intensity = 0;
	while (l_ptr)
	{
		if (v_isnan(l_ptr->pos))
			continue ;
		total_intensity += l_ptr->intensity;
		l_ptr = l_ptr->next;
	}
	return (total_intensity);
}

static void		init_photon(t_photon *photon, t_light *light)
{
	// printf("init_photon\n");
	photon->pos = light->pos;
	photon->col = vec_to_col(light->col);
	photon->n = v_new(NAN, NAN, NAN);
}

/*
** Kernel wrapper and kernel for shooting photon
*/

static void		shoot_photon_wrapper(t_raytracing_tools *r, size_t photon_count, t_photon *init_photon_list)
{
	printf("shoot_photon_wrapper\n");
	dim3 		blockSize;
	dim3 		gridSize;
	
	blockSize = dim3(BLOCK_DIM, 1, 1);
	gridSize = dim3(photon_count / BLOCK_DIM + ((photon_count % BLOCK_DIM) ? 1 : 0, 1));
	shoot_photon<<<gridSize, blockSize>>>(r->d_scene, init_photon_list, photon_count, rand());
	C(1)
		cudaError_t errSync  = cudaGetLastError();
cudaError_t errAsync = cudaDeviceSynchronize();
if (errSync != cudaSuccess) 
  printf("Sync kernel error: %s\n", cudaGetErrorString(errSync));
if (errAsync != cudaSuccess)
  printf("Async kernel error: %s\n", cudaGetErrorString(errAsync));
	// gpu_errchk((cudaDeviceSynchronize()));
}

__global__
static void			shoot_photon(t_scene *scene, t_photon *init_photon_list, int photon_count, float rand_numbers[])
{
	t_raytracing_tools	r;
	t_ray				photon;
	curandState			state;
	
	// printf("shoot_photon: time: %d\n", rand_i);
	r.pix.x = 0;
	r.pix.y = 0;
	r.scene = scene;
    r.idx = (blockDim.x * blockIdx.x) + threadIdx.x;
	if (r.idx >= photon_count)  
		return ; 
	r.devStates = &state;
	// curand_init (r.idx + (rand_i % 50), 0, 0, r.devStates);
	memset(&r.ior_list, 0, sizeof(float) * (PHOTON_BOUNCE_MAX + 1));
	photon = init_kernel_photon(&r, init_photon_list[r.idx], rand_numbers);
	// printf("photon [%i]: [%f, %f, %f]\n", r.idx, photon.dir.x, photon.dir.y, photon.dir.z);
	if (r.idx == 0)
		printf("photon cast primary ray\n");
	cast_primary_ray(&r, &photon);
	
	__syncthreads();
	
	//also need to update final photon position and normal at hitpoint
}
 
__device__ 
static t_ray		init_kernel_photon(t_raytracing_tools *r, t_photon photon, float rand_numbers[])
{
	t_ray		new_ray; 
	curandState localState;
	int 		i;
	
	//simplify rand nums here
	// printf("init_kernel_photon\n");
	localState = *r->devStates;
	new_ray.dir.x = curand(&localState);
	// r->devStates = &localState;
	new_ray.dir.y = curand(&localState);
	// r->devStates = &localState;
	new_ray.dir.z = curand(&localState);
	r->devStates = &localState;
	new_ray.dir = v_norm(new_ray.dir);
	// printf("init kernel photon: dir: [%f, %f, %f]\n", new_ray.dir.x, new_ray.dir.y, new_ray.dir.z);
	new_ray.type = R_DIRECT_PHOTON;
	new_ray.origin = photon.pos;
	new_ray.col = photon.col;
	new_ray.nhit = photon.n;
	new_ray.n_dir = 1;
	new_ray.depth = r->scene->ray_depth;
	new_ray.ior = r->scene->cameras->ior; ////////////
	r->ior_list[0] = r->scene->cameras->ior; ////////change for light ior!
	i = 0;
	while (i < r->scene->ray_depth && i < PHOTON_BOUNCE_MAX)
	{
		r->scene->photon_list[r->idx + i].pos = v_new(NAN, NAN, NAN);
		r->scene->photon_list[r->idx + i].dir = v_new(NAN, NAN, NAN);
		r->scene->photon_list[r->idx + i].n = v_new(NAN, NAN, NAN);
		r->scene->photon_list[r->idx + i].col = c_new(0, 0, 0);
		++i;
	}
	if (r->idx == 0)
		printf("done preping photon\n");
	return (new_ray);
}

void	print_photons(t_kd_tree *tree)
{
	// printf("PRINTF_PHOTONS\n");
	if (!tree)
	{
		printf("found nothing going up\n");
		return ;
	}
	printf("going left\n");
	print_photons(tree->left);
	printf("photon: [%p] [%f, %f, %f]\n", tree, tree->pos.x, tree->pos.y, tree->pos.z);
	printf("going right\n");
	print_photons(tree->right);
	printf("going up\n");
}