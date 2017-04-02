/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/02 18:17:24 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"
#include "../../inc/cuda_call.h"

// static void	display_percentage(int num);

/*
** Updates a camera's pixel_map (color of image pixels).
*/


// __host__ void	cuda_push_camera(t_camera **cameras_head, t_camera *new_camera)
// {
// 	t_camera	*cam_ptr;

// 	if (new_camera)
// 	{
// 		if (!(*cameras_head))
// 			*cameras_head = new_camera;
// 		else
// 		{
// 			cam_ptr = *cameras_head;
// 			while (cam_ptr->next)
// 				cam_ptr = cam_ptr->next;
// 			cam_ptr->next = new_camera;
// 			new_camera->prev = cam_ptr;
// 		}
// 		new_camera->next = NULL;
// 	}
// }
/*
__host__ void	allocate_cameras(t_camera **d_cams, t_camera *h_cams, t_pt2 res)
{
	t_camera *p_cam;
	t_camera *new_cam;

	new_cam = NULL;
	*d_cams = NULL;
	p_cam = h_cams;

	cudaMallocManaged(&new_cam, sizeof(t_camera));
	memcpy(new_cam, p_cam, sizeof(t_camera));
	p_cam = p_cam->next;
}

__host__ void	cuda_push_light(t_light **lights_head, t_light *new_light)
{
	t_light	*light_ptr;

	if (new_light)
	{
		if (!(*lights_head))
			*lights_head = new_light;
		else
		{
			light_ptr = *lights_head;
			while (light_ptr->next)
				light_ptr = light_ptr->next;
			light_ptr->next = new_light;
		}
		new_light->next = NULL;
	}
}*/
/*
__host__ void 	allocate_lights(t_light **d_lights, t_light *h_lights)
{
	t_light *p_light;
	t_light *new_light;

	new_light = NULL;
	*d_lights = NULL;
	p_light = h_lights;
	while (p_light)
	{
		cudaMallocManaged(&new_light, sizeof(t_light));
		memcpy(new_light, p_light, sizeof(t_light));
		cuda_push_light(d_lights, new_light);
		p_light = p_light->next;
	}
}
*//*
__host__ void	cuda_push_object(t_object **objects_head, t_object *new_object)
{
	t_object	*obj_ptr;

	if (new_object)
	{
		if (!(*objects_head))
			*objects_head = new_object;
		else
		{
			obj_ptr = *objects_head;
			while (obj_ptr->next)
				obj_ptr = obj_ptr->next;
			obj_ptr->next = new_object;
		}
		new_object->next = NULL;
	}
}*/
/*
__host__ void	allocate_objects(t_object **d_objs, t_object *h_objs)
{
	t_object *p_obj;
	t_object *new_obj;

	new_obj = NULL;
	*d_objs = NULL;
	p_obj = h_objs;
	while (p_obj)
	{
		cudaMallocManaged(&new_obj, sizeof(t_object));
		memcpy(new_obj, p_obj, sizeof(t_object));
		cuda_push_object(d_objs, new_obj);
		p_obj = p_obj->next;
	}
}
*/
// __host__
// void	cuda_push_scene(t_scene **scenes_head, t_scene *new_scene)
// {
// 	t_scene	*scene_ptr;

// 	if (new_scene)
// 	{
// 		if (!*scenes_head)
// 			*scenes_head = new_scene;
// 		else
// 		{
// 			scene_ptr = *scenes_head;
// 			while (scene_ptr->next)
// 				scene_ptr = scene_ptr->next;
// 			scene_ptr->next = new_scene;
// 			new_scene->prev = scene_ptr;
// 		}
// 	}
// }
/*
__host__ void	allocate_scenes(t_raytracing_tools *d_r, t_raytracing_tools *h_r)
{
	t_scene	*p_scene;
	t_scene	*new_scene;

	new_scene = NULL;
	d_r->scenes = NULL;
	p_scene = h_r->scenes;
	while (p_scene)
	{
		//allocate mem
		cudaMallocManaged(&new_scene, sizeof(t_scene));
		memcpy(new_scene, p_scene, sizeof(t_scene));
		if (!d_r->scenes)
			d_r->scenes = new_scene;
		//allocate cameras
		allocate_cameras(&new_scene->cameras, p_scene->cameras, p_scene->res);
		//allocate lights
		allocate_lights(&new_scene->lights, p_scene->lights);
		//allocate objects
		allocate_objects(&new_scene->objects, p_scene->objects);
		cuda_push_scene(&d_r->scenes, new_scene);
		p_scene = p_scene->next;
	}
}*/
/*
__host__ void allocate_camera(t_scene *h_scene)
{
	t_camera	*h_camera;
	t_camera	*d_camera;
	t_color		**d_pixel_map;
	int			i;

	h_camera = (t_camera *)malloc(sizeof(t_camera));
	memcpy(h_camera, h_scene->cameras, sizeof(t_camera));

	cudaMalloc(&d_pixel_map, sizeof(t_color *) * h_scene->res.y);
	i = -1;
	while (++i < h_scene->res.x)
		cudaMalloc(&(d_pixel_map[i]), sizeof(t_color) * h_scene->res.x);
	h_camera->pixel_map = d_pixel_map;

	cudaMalloc(&d_camera, sizeof(t_camera));
	cudaMemcpy(d_camera, h_camera, sizeof(t_camera), cudaMemcpyHostToDevice);
}

__host__ void	allocate_lights(t_scene *h_scene)
{
	t_light *p_light;
	t_light *h_light;
	t_light *d_light;

	p_light = h_scene->lights;
	while (p_light)
	{
		//cudaMallocManaged(&new_light, sizeof(t_light));
		//memcpy(new_light, p_light, sizeof(t_light));
		//cuda_push_light(d_lights, new_light);
		
		h_light = (t_light *)malloc(sizeof(t_light));
		memcpy(h_light, p_light, sizeof(t_light));

		cudaMalloc(&d_light, sizeof(t_light));
		h_light->next = NULL;
		cudaMemcpy(d_light, h_light, sizeof(t_light), cudaMemcpyHostToDevice);
		
		p_light = p_light->next;
	}
}

__host__ t_object	*allocate_objects(t_object *h_scene)
{
	t_object *p_object;
	t_object *h_object;
	t_object *d_object;

	p_object = h_scene->objects;
	if (p_object)
	{
		h_object = (t_object *)malloc(sizeof(t_object));
		memcpy(h_object, p_object, sizeof(t_object));
		allocate_objects(h_scene);
		cudaMalloc(&d_object, sizeof(t_object));
		h_object->next = NULL;
		cudaMemcpy(d_object, h_object, sizeof(t_object), cudaMemcpyHostToDevice);
		
		p_object = p_object->next;
	}
}

__host__ void allocate_scene(t_raytracing_tools *h_r_tmp)
{
	t_scene	*h_scene;
	t_scene	*d_scene;

	h_scene = (t_scene *)malloc(sizeof(t_scene));
	memcpy(h_scene, h_r_tmp->scenes, sizeof(t_scene));

	allocate_camera(h_scene);
	allocate_lights(h_scene);
	h_r_tmp->objects = allocate_objects(h_r_tmp->objects);

	cudaMalloc(&d_scene, sizeof(t_scene));
	h_r_tmp->scenes = d_scene;
	cudaMemcpy(d_scene, h_scene, sizeof(t_scene), cudaMemcpyHostToDevice);
}

__host__ __device__ t_raytracing_tools  *allocate_memory(t_raytracing_tools *h_r)
{
	C(11)
	t_raytracing_tools	*d_r;
	t_raytracing_tools	*h_r_tmp;

	h_r_tmp = (t_raytracing_tools *)malloc(sizeof(t_raytracing_tools));
	memcpy(h_r_tmp, h_r, sizeof(t_raytracing_tools));

	allocate_scenes(d_r, h_r);

	cudaMalloc(&d_r, sizeof(t_raytracing_tools));
	cudaMemcpy(d_r, h_r_tmp, sizeof(t_raytracing_tools), cudaMemcpyHostToDevice);
	// printf("%d\n", d_r->pix.x);
	C(12)
	// memcpy(d_r, h_r, sizeof(t_raytracing_tools));
	C(13)
	return (d_r);
}*/

__global__ void render_pixel(t_scene *scene, t_color *d_pixel_map)
{
	t_ray	cam_ray;
	t_pt2 	pixel;
	int x;
	int y;


	x = (blockDim.x * blockIdx.x) + threadIdx.x;
	y = (blockDim.y * blockIdx.y) + threadIdx.y;
	pixel.x = x;
	pixel.y = y;

	// printf("Coucou : %d\n", r->scenes->res.x * y + x);
    int idx = 1000 * y + x;
	cam_ray = init_camera_ray(pixel, scene);
	if (idx < 1000 * 1000)
		d_pixel_map[idx] = cast_primary_ray(scene, &cam_ray);
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
	while (light)
	{
		memcpy(&array[++size], light, sizeof(t_light));
		light = light->next;
	}
	return (array);
}

size_t			get_lights_array_length(t_light *lights)
{
	size_t	size;

	size = 0;
	while (lights[size].col.x != -1)
		++size;
	return ((size + 1) * sizeof(t_light));
}

__host__
void		render(t_scene *scene)
{
	t_color	*d_pixel_map;
	t_color *h_pixel_map;

	t_scene		*h_scene;
	t_scene		*d_scene;

	t_object	*d_objects;
	t_light		*d_lights;
	t_camera	*d_camera;

	h_scene = (t_scene *)malloc(sizeof(t_scene)); // malloc error
	h_scene->objects = list_to_array_objects(scene->objects);
	h_scene->lights = list_to_array_lights(scene->lights);
	h_scene->cameras = (t_camera *)malloc(sizeof(t_camera));
	memcpy(h_scene->cameras, scene->cameras, sizeof(t_camera));

	cudaMalloc(&d_scene, sizeof(t_scene *));
	cudaMalloc(&d_objects, get_object_array_length(h_scene->objects));
	cudaMalloc(&d_lights, get_lights_array_length(h_scene->lights));
	cudaMalloc(&d_camera, sizeof(t_camera));

	cudaMemcpy(d_objects, h_scene->objects, get_object_array_length(h_scene->objects), cudaMemcpyHostToDevice);
	cudaMemcpy(d_lights, h_scene->lights, get_lights_array_length(h_scene->lights), cudaMemcpyHostToDevice);
	cudaMemcpy(d_camera, h_scene->cameras, sizeof(t_camera), cudaMemcpyHostToDevice);

	h_pixel_map = (t_color *)malloc(sizeof(t_color) * scene->res.y * scene->res.x);
	cudaMalloc((void**) &d_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x);

	dim3 block_size;
	dim3 grid_size;

	dim3 blockSize = dim3(32, 32, 1);
	dim3 gridSize = dim3(scene->res.x / 32 + 1, scene->res.y / 32 + 1);
	render_pixel<<<gridSize, blockSize>>>(d_scene, d_pixel_map);
	cudaDeviceSynchronize();

	cudaMemcpy(h_pixel_map, d_pixel_map, sizeof(t_color) * scene->res.y * scene->res.x, cudaMemcpyDeviceToHost);

	// Copie la pixel map cree a partir du device dans la scene courante. A modifier, buerk, caca!
	t_pt2 coord;
	coord.y = -1;
	while (++coord.y < scene->res.y)
	{
		coord.x = -1;
		while (++coord.x < scene->res.x)
		{
			scene->cameras->pixel_map[coord.y][coord.x] = h_pixel_map[scene->res.y * coord.x + coord.y];
		}
	}

	free(h_scene->objects);
	free(h_scene->lights);
	free(h_scene->cameras);
	free(h_scene);
	free(h_pixel_map);
	cudaFree(d_objects);
	cudaFree(d_lights);
	cudaFree(d_camera);
	cudaFree(d_scene);
	cudaFree(d_pixel_map);

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
