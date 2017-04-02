/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/02 13:58:07 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"
#include "../../inc/cuda_call.h"

// static void	display_percentage(int num);

/*
** Updates a camera's pixel_map (color of image pixels).
*/


__host__ void	cuda_push_camera(t_camera **cameras_head, t_camera *new_camera)
{
	t_camera	*cam_ptr;

	if (new_camera)
	{
		if (!(*cameras_head))
			*cameras_head = new_camera;
		else
		{
			cam_ptr = *cameras_head;
			while (cam_ptr->next)
				cam_ptr = cam_ptr->next;
			cam_ptr->next = new_camera;
			new_camera->prev = cam_ptr;
		}
		new_camera->next = NULL;
	}
}

__host__ void	allocate_cameras(t_camera **d_cams, t_camera *h_cams, t_pt2 res)
{
	t_camera *p_cam;
	t_camera *new_cam;
	int		i;

	new_cam = NULL;
	*d_cams = NULL;
	p_cam = h_cams;
	while (p_cam)
	{
		cudaMallocManaged(&new_cam, sizeof(t_camera));
		memcpy(new_cam, p_cam, sizeof(t_camera));
		i = -1;
		cudaMallocManaged(&new_cam->pixel_map, sizeof(t_color *) * res.y);
		while (++i < res.y)
			cudaMallocManaged(&new_cam->pixel_map[i], sizeof(t_color) * res.x);
		cuda_push_camera(d_cams, new_cam);
		p_cam = p_cam->next;
	}
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
}
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
*/
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
}
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
__host__
void	cuda_push_scene(t_scene **scenes_head, t_scene *new_scene)
{
	t_scene	*scene_ptr;

	if (new_scene)
	{
		if (!*scenes_head)
			*scenes_head = new_scene;
		else
		{
			scene_ptr = *scenes_head;
			while (scene_ptr->next)
				scene_ptr = scene_ptr->next;
			scene_ptr->next = new_scene;
			new_scene->prev = scene_ptr;
		}
	}
}
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

__host__ void	allocate_objects(t_scene *h_scene)
{
	t_light *p_object;
	t_light *h_object;
	t_light *d_object;

	p_object = h_scene->lights;
	while (p_object)
	{
		//cudaMallocManaged(&new_light, sizeof(t_light));
		//memcpy(new_light, p_object, sizeof(t_light));
		//cuda_push_object(d_objects, new_light);
		
		h_object = (t_light *)malloc(sizeof(t_light));
		memcpy(h_object, p_object, sizeof(t_light));

		cudaMalloc(&d_object, sizeof(t_light));
		h_object->next = NULL;
		cudaMemcpy(d_object, h_object, sizeof(t_light), cudaMemcpyHostToDevice);
		
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
	allocate_objects(h_scene);

	cudaMalloc(&d_scene, sizeof(t_scene));
	h_r_tmp->scenes = d_scene;
	cudaMemcpy(d_scene, h_scene, sizeof(t_scene), cudaMemcpyHostToDevice);
}

__host__ t_raytracing_tools  *allocate_memory(t_raytracing_tools *h_r)
{
	C(11)
	t_raytracing_tools	*d_r;
	t_raytracing_tools	*h_r_tmp;

	h_r_tmp = (t_raytracing_tools *)malloc(sizeof(t_raytracing_tools));
	memcpy(h_r_tmp, h_r, sizeof(t_raytracing_tools));

	// allocate_scenes(d_r, h_r);


	// cudaMallocManaged(&d_r, sizeof(t_raytracing_tools));
	cudaMalloc(&d_r, sizeof(t_raytracing_tools));
	cudaMemcpy(d_r, h_r_tmp, sizeof(t_raytracing_tools), cudaMemcpyHostToDevice);
	// printf("%d\n", d_r->pix.x);
	C(12)
	// memcpy(d_r, h_r, sizeof(t_raytracing_tools));
	C(13)
	return (d_r);
}

__global__ void render_pixel(t_raytracing_tools *r, t_color *d_pixel_map)
{
	// t_ray	cam_ray;

	(void)r;


	// int blockId = blockIdx.x + blockIdx.y * gridDim.x; 
	// int idx = blockId * (blockDim.x * blockDim.y) + (threadIdx.y * blockDim.x) + threadIdx.x;
    int x = (blockDim.x * blockIdx.x) + threadIdx.x;
    int y = (blockDim.y * blockIdx.y) + threadIdx.y;
    int idx = r->scenes->res.x * y + x;
	// r->pix.x = pixel.x;
	// r->pix.y = pixel.y;
	// cam_ray = init_camera_ray(pixel, r->scenes);*/
	if (idx < r->scenes->res.x * r->scenes->res.y)
	{
		d_pixel_map[idx].x = 255;//cast_primary_ray(r, &cam_ray);
		d_pixel_map[idx].y = 255;//cast_primary_ray(r, &cam_ray);
		d_pixel_map[idx].z = 255;//cast_primary_ray(r, &cam_ray);
	}
}

__host__
void		render(t_raytracing_tools *r)
{
	t_raytracing_tools *d_r;
	t_color	*d_pixel_map;
	t_color *h_pixel_map;

	d_r = allocate_memory(r);
	cudaMalloc((void**) &d_pixel_map, sizeof(t_color) * r->scenes->res.y * r->scenes->res.x);
	h_pixel_map = (t_color *)malloc(sizeof(t_color) * r->scenes->res.y * r->scenes->res.x);

	dim3 block_size;
	dim3 grid_size;

	h_pixel_map[0].x = -1;

	dim3 blockSize = dim3(32, 32, 1);
	dim3 gridSize = dim3((blockSize.x + r->scenes->res.x - 1) / blockSize.x, (blockSize.y + r->scenes->res.y - 1) / blockSize.y, 1);

	printf("grid size: %i, %i\n", gridSize.x, gridSize.y); 
	// dim3	blockSize(100);
	// dim3	gridSize(10, 10, 10);


	render_pixel<<<gridSize, blockSize>>>(d_r, d_pixel_map);

	// render_pixel<<<grid_size, block_size>>>(d_r, d_pixel_map);
	cudaDeviceSynchronize();

	C(4)
	// cudaMemcpy(r->scenes->cameras->pixel_map, d_r->scenes->cameras->pixel_map, sizeof(t_color *) * r->scenes->res.y, cudaMemcpyDeviceToHost);
	// r->scenes->cameras->pixel_map = d_r->scenes->cameras->pixel_map;
	cudaMemcpy(h_pixel_map, d_pixel_map, sizeof(t_color) * r->scenes->res.y * r->scenes->res.x, cudaMemcpyDeviceToHost);
	// h_pixel_map[0].x = 255;
	C(5)
	// while (++i < r->scenes->res.y)
		// cudaMemcpy(h_pixel_map[i], d_pixel_map[i], sizeof(t_color) * r->scenes->res.x, cudaMemcpyDeviceToHost);
		//printf("%f\n", d_r->scenes->cameras->pixel_map[i][0].x);
		//memcpy(r->scenes->cameras->pixel_map[i], d_r->scenes->cameras->pixel_map[i], sizeof(t_color) * r->scenes->res.x);
		// r->scenes->cameras->pixel_map[i] = d_r->scenes->cameras->pixel_map[i];
	C(6)
	int i = -1;
	while (++i < 30) //r->scenes->res.y * r->scenes->res.x)
		printf("%f\n", h_pixel_map[i].x);

	t_pt2 coord;

	coord.y = -1;
	while (++coord.y < r->scenes->res.y)
	{
		coord.x = -1;
		while (++coord.x < r->scenes->res.x)
		{
			r->scenes->cameras->pixel_map[coord.y][coord.x] = h_pixel_map[r->scenes->res.y * coord.x + coord.y];
		}
	}
}

// __device__
// static void	display_percentage(int num)
// {
// 	ft_printf("Loading...%i%%\r", num);
// }
