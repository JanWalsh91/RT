/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/03 18:05:56 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"
#include "../../inc/cuda_call.h"

// static void	display_percentage(int num);

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

__global__ void render_pixel(t_scene *scene, t_color *d_pixel_map)
{
	t_ray	cam_ray;
	t_pt2 	pixel;
	int 	x;
	int 	y;
	int		idx;


	x = (blockDim.x * blockIdx.x) + threadIdx.x;
	y = (blockDim.y * blockIdx.y) + threadIdx.y;

	// printf("%d %d\n", blockIdx.x, blockIdx.y);
	// printf("%d %d\n", threadIdx.x, threadIdx.y);	

    idx = scene->res.x * y + x;

	// d_pixel_map[idx].x = 0;
	// d_pixel_map[idx].y = 0;
	// d_pixel_map[idx].z = 0;
	if (idx < scene->res.x * scene->res.y)
	{
		printf("%d\n", idx);
		pixel.x = x;
		pixel.y = y;
		scene->pix.x = x;
		scene->pix.y = y;
		// printf("%d, %d\n", blockIdx.x, blockIdx.y);
		cam_ray = init_camera_ray(pixel, scene);
		__syncthreads();
		
		// if (idx < 1)
		// {
		// 	printf("Pointer to camera fov, device: %p\n", &(scene->cameras[0].fov));
		// 	printf("Camera fov in the device: %f\n", scene->cameras[0].fov);
		// 	printf("Scene res : [%d, %d]\n", scene->res.x, scene->res.y);
		// 	printf("Scene ray depth: %d\n", scene->ray_depth);
		// 	printf("Scene background color: %f, %f, %f\n", scene->background_color.x, scene->background_color.y, scene->background_color.z);
		// 	printf("Scene ka: %f\n", scene->ka);
		// 	printf("Scene ka: %f\n", scene->image_aspect_ratio);
		// 	printf("Scene camera pos: %f, %f, %f\n", scene->cameras[0].pos.x, scene->cameras[0].pos.y, scene->cameras[0].pos.z);
		// 	printf("Scene first obj pos: %f, %f, %f\n", scene->objects[0].pos.x, scene->objects[0].pos.y, scene->objects[0].pos.z);
		// 	printf("Scene first light pos: %f, %f, %f\n", scene->lights[0].pos.x, scene->lights[0].pos.y, scene->lights[0].pos.z);

		// 	// pointer access to variable
		// 	// t_camera	*cam;

		// 	// init_camera_ray(pixel, scene);
		// 	// cam = &scene->cameras[0];

		// 	// printte_matrix(cam->ctw);

		// 	// printf("Cameras by pointer value : \n");
			
		// 	// printf("Scene camera pos: %f, %f, %f\n", cam->pos.x, cam->pos.y, cam->pos.z);

		// }
			// printf("%d\n", scene->lights[0].intensity);


		// if (x == 600 && y == 600)
		t_color col = cast_primary_ray(scene, &cam_ray);
		
		// t_color col = v_new(0, 0, 0);
		// if (200 < x && x < 300)
		// {	
		// 	col.x = idx % 255;
		// 	col.y = 255;
		// 	col.z = 255;
		// }
		__syncthreads();
		d_pixel_map[idx] = col;
		__syncthreads();
			// d_pixel_map[idx].y = 0;//cast_primary_ray(scene, &cam_ray);
		// d_pixel_map[idx].x = 255;
		// d_pixel_map[idx].y = 255;
		// d_pixel_map[idx].z = 255;
			// d_pixel_map[idx].z = 0;//cast_primary_ray(scene, &cam_ray);
			// if (d_pixel_map[idx].x > 0.0001)
				// printf("%f\n", d_pixel_map[idx].x);
	}
	// printf("%d %d\n", x, y);
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
	array = (t_object *)malloc(sizeof(t_object) * size + 1); // malloc error
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
	array = (t_light *)malloc(sizeof(t_light) * size + 1); // malloc error
	array[size].col.x = -1;
	light = head;
	size = -1;
	// printf("COLOR: %f\n", array[size].col.x);
	while (light)
	{
		memcpy(&array[++size], light, sizeof(t_light));
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
	// while (lights[size].col.x != -1)
		// ++size;

	return ((size + 1) * sizeof(t_light));
}

__host__
void		render(t_scene *scene)
{
	t_color	*d_pixel_map;
	t_color *h_pixel_map;

	t_scene		*h_scene_to_array;
	t_scene		*h_d_scene;
	t_scene		*d_scene;

	t_object	*d_objects;
	t_light		*d_lights;
	t_camera	*d_camera;

	// Preparation des deux structures temporarires
	h_scene_to_array = (t_scene *)malloc(sizeof(t_scene)); // malloc error
	h_d_scene = (t_scene *)malloc(sizeof(t_scene)); // malloc error
	memcpy(h_scene_to_array, scene, sizeof(t_scene));
	memcpy(h_d_scene, scene, sizeof(t_scene));

	// Creation des tableaux 1D pour les objets et lumieres
	h_scene_to_array->objects = list_to_array_objects(scene->objects);
	h_scene_to_array->lights = list_to_array_lights(scene->lights);
	h_scene_to_array->cameras = (t_camera *)malloc(sizeof(t_camera));
	memcpy(h_scene_to_array->cameras, scene->cameras, sizeof(t_camera));

	// Allocation de la memoire GPU
	cudaMalloc(&(h_d_scene->objects), get_object_array_length(h_scene_to_array->objects));
	cudaMalloc(&(h_d_scene->lights), get_lights_array_length(h_scene_to_array->lights));
	cudaMalloc(&(h_d_scene->cameras), sizeof(t_camera));
	cudaMalloc(&d_scene, sizeof(t_scene));

	printf("Pointer to camera fov, host: %p\n", &(h_d_scene->cameras[0].fov));

	// Copie des tableaux du CPU vers le GPU, en passant par la structure contenant des pointeurs sur GPU
	cudaMemcpy(h_d_scene->cameras, h_scene_to_array->cameras, sizeof(t_camera), cudaMemcpyHostToDevice);
	cudaMemcpy(h_d_scene->objects, h_scene_to_array->objects, get_object_array_length(h_scene_to_array->objects), cudaMemcpyHostToDevice);
	cudaMemcpy(h_d_scene->lights, h_scene_to_array->lights, get_lights_array_length(h_scene_to_array->lights), cudaMemcpyHostToDevice);

	// Copie de la structure finale sur le GPU, contenant les pointeurs GPU
	cudaMemcpy(d_scene, h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice);

	// Pixel map
	h_pixel_map = (t_color *)malloc(sizeof(t_color) * scene->res.y * scene->res.x);
	cudaMalloc(&d_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x);

	dim3 block_size;
	dim3 grid_size;

	int div = 16;

	dim3 gridSize= dim3(scene->res.x / div, scene->res.y);
	dim3 blockSize= dim3(div, 1, 1);
	render_pixel<<<gridSize, blockSize>>>(d_scene, d_pixel_map);
	//gpuErrchk( cudaPeekAtLastError() ); // Debug
	// gpuErrchk( cudaDeviceSynchronize() ); // Debug
	cudaDeviceSynchronize();
	C(666)
	cudaMemcpy(h_pixel_map, d_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x, cudaMemcpyDeviceToHost);
	
	printf("h_pix_map: %f\n", h_pixel_map[0].z);
	memcpy(scene->cameras->pixel_map, h_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x);
	printf("scene->cameras->pixel_map: %f\n", scene->cameras->pixel_map[0].z);

	t_pt2 loop;
	loop.y = -1;
	// while (++loop.y < scene->res.y)
	// {
		// loop.x = -1;
		while (++loop.y < scene->res.y)
		{
			fflush(stdout);
			printf("%f - ", scene->cameras->pixel_map[loop.y * scene->res.x + 200].z);
		}
		printf("\n");
	// }

	// t_pt2 coord;
	// coord.y = -1;
	// while (++coord.y < scene->res.y)
	// {
	// 	coord.x = -1;
	// 	while (++coord.x < scene->res.x)
	// 	{
	// 		scene->cameras->pixel_map[coord.y][coord.x] = h_pixel_map[scene->res.x * coord.y + coord.x];
	// 	}
	// }

/*	free(h_scene->objects);
	free(h_scene->lights);
	free(h_scene->cameras);
	free(h_scene);
	free(h_pixel_map);
	cudaFree(d_objects);
	cudaFree(d_lights);
	cudaFree(d_camera);
	cudaFree(d_scene);
	cudaFree(d_pixel_map);
*/
	// Malloc une scene sur le CPU
	// Malloc tableau d'objets sur le CPU
	// Malloc tableau de lights sur le CPU
	// Malloc camera CPU
	// Malloc tableau d'objets sur le GPU
	// Malloc tableau de lights sur le GPU
	// Malloc camera GPU
	// Copier tout du CPU au GPU
	// Malloc une scene sur le GPU
	// Copie la scene CPU sur le GPU
	// Lance le kernel
	// Free les listes GPU a partir de scene CPU
	// Free la scene GPU
	// Free la scene CPU et ses objets
}
