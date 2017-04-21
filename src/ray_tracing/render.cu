/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/21 12:20:33 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cuda_call.h"

#include <pthread.h>

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
	// printf("%d %d\n", blockIdx.x, blockIdx.y);
	// printf("%d %d\n", threadIdx.x, threadIdx.y);	

    idx = scene->res.x * r.pix.y + r.pix.x;

	if (idx < 1)
	{
		// printf("Coucou\n");
		printf("%f\n", scene->lights[1].col.x);
		// *loading = 20;
	}


	if (r.pix.x < scene->res.x && r.pix.y < scene->res.y)
	{
		cam_ray = init_camera_ray(&r);	
		d_pixel_map[idx] = filter(cast_primary_ray(&r, &cam_ray), scene->cameras->filter);
		// d_pixel_map[idx] = cast_primary_ray(&r, &cam_ray);
	}
	//loading->x = atomicAdd(&(loading->x), 1);
	//__syncthreads();
}



t_object	*list_to_array_objects(t_object *object)
{
	int			size;
	t_object	*head;
	t_object	*array;

	size = 0;
	head = object;
	while (object)
	{
		++size;
		object = object->next;
	}
	array = (t_object *)malloc(sizeof(t_object) * (size + 1)); // malloc error
	array[size].type = T_INVALID_TOKEN;
	object = head;
	size = -1;
	while (object)
	{
		memcpy(&array[++size], object, sizeof(t_object)); // stack memcpy ?
		object = object->next;
	}
	return (array);
}

size_t			get_object_array_length(t_object *objects)
{
	size_t	size;

	size = 0;
	while (objects[size].type != T_INVALID_TOKEN)
		++size;
	return ((size + 1) * sizeof(t_object));
}

t_light		*list_to_array_lights(t_light *light)
{
	int			size;
	t_light	*head;
	t_light	*array;

	size = 0;
	head = light;
	while (light)
	{
		++size;
		light = light->next;
	}
	array = (t_light *)malloc(sizeof(t_light) * (size + 1)); // malloc error
	// bzero(array, sizeof(t_light) * (size + 1));
	array[size].col = v_new(NAN, NAN, NAN);
	light = head;
	size = -1;
	// printf("COLOR: %f\n", array[size].col.x);
	while (light)
	{
		array[++size].col = v_new(NAN, NAN, NAN);
		memcpy(&array[size], light, sizeof(t_light));
		light = light->next;
		// printf("%p\n", light);
	}
	// printf("COLOR: %f\n", array[size].col.x);
	return (array);
}

size_t			get_lights_array_length(t_light *lights)
{
	size_t	size;

	size = 0;
	// printf("%f\n", lights[size].col.x);
	while (!v_isnan(lights[size].col))
		++size;
	// C(3)
	return ((size + 1) * sizeof(t_light));
}

		#include <time.h>

// void		*loading_bar(void	*pt)
// {
// 	t_pt2 *max = (t_pt2*) pt;
// 	// usleep(1000000);

// 	while (max->x < max->y / 2) ;
// 		printf("loading : %d\n", max->x);
// 	return NULL;
// }

void		render(t_scene *scene)
{
	t_color		*d_pixel_map;
	t_color 	*h_pixel_map;
	t_scene		*h_scene_to_array;
	t_scene		*h_d_scene;
	t_scene		*d_scene;
	dim3		block_size;
	dim3		grid_size;
	clock_t		start;
	clock_t		stop;

	size_t       available;
  	size_t       total;

	cudaDeviceSetLimit(cudaLimitStackSize, 1024 * scene->ray_depth);
	// Preparation des deux structures temporarires
	start = clock();
	if (!(h_scene_to_array = (t_scene *)malloc(sizeof(t_scene))))
		exit(0); // malloc error
	stop = clock();
	printf("1. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	

	start = clock();
	if (!(h_d_scene = (t_scene *)malloc(sizeof(t_scene))))
		exit(0); // malloc error
	stop = clock();
	printf("2. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	
	start = clock();
	if (!(memcpy(h_scene_to_array, scene, sizeof(t_scene))))
		exit(0);
	stop = clock();
	printf("3. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	
	start = clock();
	memcpy(h_d_scene, scene, sizeof(t_scene));
	stop = clock();
	printf("4. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);

	// Creation des tableaux 1D pour les objets et lumieres
	start = clock();
	h_scene_to_array->objects = list_to_array_objects(scene->objects);
	stop = clock();
	printf("5. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	start = clock();
	h_scene_to_array->lights = list_to_array_lights(scene->lights);
	stop = clock();
	printf("6. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	
	start = clock();
	h_scene_to_array->cameras = (t_camera *)malloc(sizeof(t_camera));
	stop = clock();
	printf("7. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	
	// t_vec3	*truc;

	start = clock();
	// cudaMalloc(&truc, sizeof(t_vec3));
	gpuErrchk(cudaSetDevice(0));
	// cudaFree(0);
	stop = clock();
	printf("80. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);


	start = clock();
	memcpy(h_scene_to_array->cameras, scene->cameras, sizeof(t_camera));
	stop = clock();
	printf("8. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	
	// Allocation de la memoire GPU
	start = clock();
	gpuErrchk(cudaMalloc(&(h_d_scene->lights), get_lights_array_length(h_scene_to_array->lights)));
	
	stop = clock();
	printf("10. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	start = clock();
	gpuErrchk(cudaMalloc(&(h_d_scene->objects), get_object_array_length(h_scene_to_array->objects)));
	stop = clock();
	printf("9. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	start = clock();
	gpuErrchk(cudaMalloc(&(h_d_scene->cameras), sizeof(t_camera)));
	stop = clock();
	printf("11. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	start = clock();
	gpuErrchk(cudaMalloc(&d_scene, sizeof(t_scene)));
	stop = clock();
	printf("12. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);

	//printf("Pointer to camera fov, host: %p\n", &(h_d_scene->cameras[0].fov));

	// Copie des tableaux du CPU vers le GPU, en passant par la structure contenant des pointeurs sur GPU
	start = clock();
	gpuErrchk(cudaMemcpy(h_d_scene->cameras, h_scene_to_array->cameras, sizeof(t_camera), cudaMemcpyHostToDevice));
	stop = clock();
	printf("13. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	start = clock();
	gpuErrchk((cudaMemcpy(h_d_scene->objects, h_scene_to_array->objects, get_object_array_length(h_scene_to_array->objects), cudaMemcpyHostToDevice)));
	stop = clock();
	printf("14. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	start = clock();
	gpuErrchk(cudaMemcpy(h_d_scene->lights, h_scene_to_array->lights, get_lights_array_length(h_scene_to_array->lights), cudaMemcpyHostToDevice));
	stop = clock();
	printf("15. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);

	// Copie de la structure finale sur le GPU, contenant les pointeurs GPU
	start = clock();
	gpuErrchk(cudaMemcpy(d_scene, h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice));
	stop = clock();
	printf("16. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	// Pixel map
	start = clock();
	h_pixel_map = (t_color *)malloc(sizeof(t_color) * scene->res.y * scene->res.x);
	stop = clock();
	printf("17. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
  	cudaMemGetInfo(&available, &total);
 	printf("available memory: [%'lu]\ntotal memory:   [%'lu]\n", available, total);
	start = clock();
	printf("Pixelmap size : %lu\n", sizeof(t_color) * scene->res.y * scene->res.x);
	printf("t_color size : %d\n", scene->res.y);
	gpuErrchk((cudaMalloc(&d_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x)));
	// cudaMallocHost(&h_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x);
	stop = clock();
	cudaMemGetInfo(&available, &total);
 	printf("available memory: [%'lu]\ntotal memory:   [%'lu]\n", available, total);
	printf("18. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);

	dim3 blockSize 	= dim3(BLOCK_DIM, BLOCK_DIM, 1);
	dim3 gridSize	= dim3(scene->res.x / BLOCK_DIM + 1, scene->res.y / BLOCK_DIM + 1);


	printf("gridsize: [%d][%d][%d] blocksize: [%d][%d][%d]\n", gridSize.x, gridSize.y, gridSize.z, blockSize.x, blockSize.y, blockSize.z);
	



	start = clock();
	render_pixel<<<gridSize, blockSize>>>(d_scene, d_pixel_map/*, progress*/);
	gpuErrchk( cudaPeekAtLastError() );
	// gpuErrchk( cudaDeviceSynchronize() ); // Debug
	gpuErrchk((cudaDeviceSynchronize()));
	stop = clock();
	printf("19. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);

	//   printf("!!!%d \n", progress->x);
	//   pthread_join(p0, NULL);
 
	start = clock();
	gpuErrchk(cudaMemcpy(h_pixel_map, d_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x, cudaMemcpyDeviceToHost));
	stop = clock();
	printf("20. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);


	//printf("h_pix_map: %f\n", h_pixel_map[0].z);
	start = clock();
	memcpy(scene->cameras->pixel_map, h_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x);
	
	// in a different thread:
	// export_image(h_pixel_map, scene->res.y, scene->res.x, "image.bmp");

	stop = clock();
	printf("21. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	  //printf("scene->cameras->pixel_map: %f\n", scene->cameras->pixel_map[0].z);


	start = clock();
	cudaFree(h_d_scene->cameras);
	cudaFree(h_d_scene->lights);
	cudaFree(h_d_scene->objects);
	cudaFree(d_scene);
	cudaFree(d_pixel_map);
	stop = clock();
	printf("22. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);

	start = clock();
	free(h_scene_to_array->objects);
	free(h_scene_to_array->lights);
	free(h_scene_to_array->cameras);
	free(h_scene_to_array);
	free(h_d_scene);
	free(h_pixel_map);
	stop = clock();
	printf("23. Time taken %f milliseconds\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);


	  int nb;

	  cudaGetDeviceCount(&nb);
	  printf("Nb device : %d\n", nb);
}
