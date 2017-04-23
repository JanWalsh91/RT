/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/23 18:49:54 by tgros            ###   ########.fr       */
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

__global__ void render_pixel(t_scene *scene, t_color *d_pixel_map/*, t_pt2 *loading*/)
{
	t_ray				cam_ray;
	t_raytracing_tools	r;
	int					idx;

	r.pix.x = (blockDim.x * blockIdx.x) + threadIdx.x;
	r.pix.y = (blockDim.y * blockIdx.y) + threadIdx.y;
	r.scene = scene;
    idx = scene->res.x * r.pix.y + r.pix.x;


	if (r.pix.x < scene->res.x && r.pix.y < scene->res.y)
	{
		cam_ray = init_camera_ray(&r);	
		// d_pixel_map[idx] = filter(cast_primary_ray(&r, &cam_ray), scene->cameras->filter);
		d_pixel_map[idx] = filter(cast_primary_ray(&r, &cam_ray), scene->cameras->filter);
		// d_pixel_map[idx] = cast_primary_ray(&r, &cam_ray);
	}
	//loading->x = atomicAdd(&(loading->x), 1);
	//__syncthreads();
}

void		render(t_raytracing_tools *r)
{
	// t_clock start = clock();
	// t_color		*d_pixel_map;
	// t_color 	*h_pixel_map;
	// t_scene		*h_scene_to_array;
	// t_scene		*h_d_scene;
	// t_scene		*d_scene;
	dim3		block_size;
	dim3		grid_size;


	// size_t       available;
  	// size_t       total;

	

	// Preparation des deux structures temporarires
	// if (!(h_scene_to_array = (t_scene *)malloc(sizeof(t_scene))))
		// exit(0); // malloc error
	// if (!(h_d_scene = (t_scene *)malloc(sizeof(t_scene))))
	// 	exit(0); // malloc error
	// if (!(memcpy(h_scene_to_array, scene, sizeof(t_scene))))
	// 	exit(0);
	// memcpy(h_d_scene, scene, sizeof(t_scene));

	// Creation des tableaux 1D pour les objets et lumieres
	// h_scene_to_array->objects = list_to_array_objects(scene->objects);
	// h_scene_to_array->lights = list_to_array_lights(scene->lights);
	// h_scene_to_array->cameras = (t_camera *)malloc(sizeof(t_camera));
	

	// memcpy(h_scene_to_array->cameras, scene->cameras, sizeof(t_camera));
	
	// Allocation de la memoire GPU
	// gpuErrchk(cudaMalloc(&(h_d_scene->lights), get_lights_array_length(h_scene_to_array->lights)));
	// gpuErrchk(cudaMalloc(&(h_d_scene->objects), get_object_array_length(h_scene_to_array->objects)));
	// gpuErrchk(cudaMalloc(&(h_d_scene->cameras), sizeof(t_camera)));
	// gpuErrchk(cudaMalloc(&d_scene, sizeof(t_scene)));

	// Copie des tableaux du CPU vers le GPU, en passant par la structure contenant des pointeurs sur GPU
	// gpuErrchk(cudaMemcpy(h_d_scene->cameras, h_scene_to_array->cameras, sizeof(t_camera), cudaMemcpyHostToDevice));
	// gpuErrchk((cudaMemcpy(h_d_scene->objects, h_scene_to_array->objects, get_object_array_length(h_scene_to_array->objects), cudaMemcpyHostToDevice)));
	// gpuErrchk(cudaMemcpy(h_d_scene->lights, h_scene_to_array->lights, get_lights_array_length(h_scene_to_array->lights), cudaMemcpyHostToDevice));

	// Copie de la structure finale sur le GPU, contenant les pointeurs GPU
	// gpuErrchk(cudaMemcpy(d_scene, h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice));
	
	// Pixel map
	// h_pixel_map = (t_color *)malloc(sizeof(t_color) * r->scene->res.y * r->scene->res.x);
	
  	// cudaMemGetInfo(&available, &total);
 	// printf("available memory: [%'lu]\ntotal memory:   [%'lu]\n", available, total);
	// gpuErrchk((cudaMalloc(&d_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x)));
	// cudaMemGetInfo(&available, &total);
 	// printf("available memory: [%'lu]\ntotal memory:   [%'lu]\n", available, total);

	 //prep kernel
	dim3 blockSize 	= dim3(BLOCK_DIM, BLOCK_DIM, 1);
	dim3 gridSize	= dim3(r->scene->res.x / BLOCK_DIM + 1, r->scene->res.y / BLOCK_DIM + 1);


	// printf("gridsize: [%d][%d][%d] blocksize: [%d][%d][%d]\n", gridSize.x, gridSize.y, gridSize.z, blockSize.x, blockSize.y, blockSize.z);
	
	// printf("Nouvelle position: %f\n", r->scene->objects->pos.x);
	// printf("d_scene : [%f]\n", r->d_scene->ka);;
	// clock_t start = clock();

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaEventRecord(start);
	render_pixel<<<gridSize, blockSize>>>(r->d_scene, r->d_pixel_map/*, progress*/);
	cudaEventRecord(stop);

	cudaEventSynchronize(stop);
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

	printf("=============== EXECUTION ================== \n");
	printf("Kernel duration: %f milliseconds\n", milliseconds);
	printf("============================================ \n");

	// clock_t stop = clock();
	// printf("\nAppel du kernel : %f\n",
  	// (float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	
	// printf("%d %d %d\n", r->d_pixel_map[25].r, r->d_pixel_map[25].g, r->d_pixel_map[25].b );

	// gpuErrchk( cudaPeekAtLastError() );
	gpuErrchk((cudaDeviceSynchronize()));
	// start = clock();
	// memcpy(r->scene->cameras->pixel_map, r->d_pixel_map, sizeof(t_color) * r->scene->res.y * r->scene->res.x);
	// r->scene->cameras->pixel_map = r->d_pixel_map;
	// gpuErrchk(cudaMemcpy(r->scene->cameras->pixel_map, r->d_pixel_map, sizeof(t_color) * r->scene->res.y * r->scene->res.x, cudaMemcpyDeviceToHost));
	//  stop = clock();
	// printf("\nmemcpy pixelmap : %f\n",
  	// (float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	// gpuErrchk((cudaMemcpy(r->scene->cameras->pixel_map, h_pixel_map, sizeof(t_color) * r->scene->res.y * r->scene->res.x, cudaMemcpyDeviceToHost)));
	// memcpy(r->scene->cameras->pixel_map, h_pixel_map, sizeof(t_color) * r->scene->res.y * r->scene->res.x);
	//free dat shit
	// cudaFree(h_d_scene->cameras);
	// cudaFree(h_d_scene->lights);
	// cudaFree(h_d_scene->objects);
	// cudaFree(d_scene);
	// cudaFree(d_pixel_map);

	//free dis shit
	// free(h_scene_to_array->objects);
	// free(h_scene_to_array->lights);
	// free(h_scene_to_array->cameras);
	// free(h_scene_to_array);
	// free(h_d_scene);
	// free(h_pixel_map);
}
