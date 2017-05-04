/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/04 14:25:24 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "../../inc/cuda_call.h"

/*
** Updates a camera's pixel_map (color of image pixels).
*/
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
void	printte_matrix(t_matrix m)
{
	int i;
	int	y;

	y = -1;
	while (++y < 4)
	{
		i = -1;
		while (++i < 4)
			printf("[%f]", m[y][i]);
		printf("\n");
	}
}

__global__ void render_pixel(t_scene *scene, t_color *d_pixel_map, t_pt2 tileId, int tile_size)
{
	t_ray				cam_ray;
	t_raytracing_tools	r;
	int					idx;
	
	r.pix.x = (tileId.x * tile_size) + (blockDim.x * blockIdx.x) + threadIdx.x;
	r.pix.y = (tileId.y * tile_size) + (blockDim.y * blockIdx.y) + threadIdx.y;
	r.scene = scene;
	
    idx = scene->res.x * r.pix.y + r.pix.x;
	if (r.pix.x < scene->res.x && r.pix.y < scene->res.y)
	{
		//initialize ior list
		r.ior_list = (float *)malloc(sizeof(float) * (scene->ray_depth + 1));
		memset(r.ior_list, 0, sizeof(float) * (scene->ray_depth + 1));
		cam_ray = init_camera_ray(&r);
		d_pixel_map[idx] = filter(cast_primary_ray(&r, &cam_ray), scene->cameras->filter);
		free(r.ior_list);
	}
}

//'dis is wonderful
__global__ void create_anaglyph(t_color *left, t_color *right, t_scene *scene, int tile_size, t_pt2 tileId)
{
	// int	idx;

	// // printf("Debut du deuxieme kernel\n");

	// idx = scene->res.x * ((blockDim.y * blockIdx.y) + threadIdx.y) + ((blockDim.x * blockIdx.x) + threadIdx.x);

	// if (idx == 10)
	// {
	// 	printf("Other kernel\n");
	// 	printf("%d, %d, %d\n", right[10].r, right[10].g, right[10].b);
	// }


	int		idx;
	t_pt2	pixel;

	pixel.x = (tileId.x * tile_size) + (blockDim.x * blockIdx.x) + threadIdx.x;
	pixel.y = (tileId.y * tile_size) + (blockDim.y * blockIdx.y) + threadIdx.y;
    idx = scene->res.x * pixel.y + pixel.x;

	if (pixel.x < scene->res.x && pixel.y < scene->res.y)
	{
		left[idx].g = right[idx].g;
		left[idx].b = right[idx].b;
	}
	// __syncthreads();
}

void		render(t_raytracing_tools *r, t_pt2 tileId)
{
	dim3 		blockSize;
	dim3 		gridSize;
	int			size;

	size = (r->settings.tile_size / BLOCK_DIM) + ((r->settings.tile_size % BLOCK_DIM) ? 1 : 0);
	blockSize = dim3(BLOCK_DIM, BLOCK_DIM, 1);
	gridSize = dim3(size, size);

	cudaEvent_t start, stop;
	cudaEventCreate(&start); 
	cudaEventCreate(&stop);
	cudaEventRecord(start);
	render_pixel<<<gridSize, blockSize>>>(r->d_scene, r->d_pixel_map, tileId, r->settings.tile_size);
	// printf("Iteration i = %d	\n", i++);
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

	//beautiful....
	// printf("=============== EXECUTION ================== \n");
	// printf("Kernel duration: %f milliseconds\n", milliseconds);
	// printf("============================================ \n");

	gpuErrchk((cudaDeviceSynchronize()));
	// if (r->scene->is_3d)
	// {
	// 	printf("3d\n");
	// 	r->scene->cameras->pos.x += 0.2;
	// 	r->scene->cameras->filter = F_RIGHT_CYAN;
	// 	gpuErrchk((cudaMemcpy(r->h_d_scene->cameras, r->scene->cameras, sizeof(t_camera), cudaMemcpyHostToDevice)));
	// 	gpuErrchk(cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice));
	// 	// render_pixel<<<gridSize, blockSize>>>(r->d_scene, r->d_pixel_map_3d, tileId, r->settings.tile_size);
	// 	gpuErrchk((cudaDeviceSynchronize()));
	// 	r->scene->cameras->pos.x -= 0.2;

	// 	// create_anaglyph<<<gridSize, blockSize>>>(r->d_pixel_map, r->d_pixel_map_3d, r->d_scene, r->settings.tile_size, tileId);

	// 	gpuErrchk((cudaDeviceSynchronize()));
	// }
}