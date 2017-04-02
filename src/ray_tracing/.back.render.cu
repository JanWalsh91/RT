/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/01 17:40:27 by tgros            ###   ########.fr       */
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
}

__host__ t_raytracing_tools  *allocate_memory(t_raytracing_tools *h_r)
{
	C(11)
	t_raytracing_tools *d_r = NULL;

	cudaMallocManaged(&d_r, sizeof(t_raytracing_tools));
	// printf("%d\n", d_r->pix.x);
	C(12)
	memcpy(d_r, h_r, sizeof(t_raytracing_tools));
	C(13)
	allocate_scenes(d_r, h_r);
	return (d_r);
}

__global__ void render_pixel(t_raytracing_tools *r)
{
	t_pt2	pixel;
	t_ray	cam_ray;

	pixel.x = blockIdx.x * blockDim.x + threadIdx.x;
	pixel.y = blockIdx.y * blockDim.y + threadIdx.y;

	r->pix.x = pixel.x;
	r->pix.y = pixel.y;
	cam_ray = init_camera_ray(pixel, r->scenes);
	r->scenes->cameras->pixel_map[pixel.y][pixel.x] = cast_primary_ray(r, &cam_ray);
}

__host__
void		render(t_raytracing_tools *r)
{
/*	t_ray	cam_ray;

	r->pix.y = -1;
	while (++r->pix.y < r->scenes->res.y)
	{
		r->pix.x = -1;
		display_percentage((int)((double)r->pix.y /
			r->scenes->res.y * (100)) + 1);
		while (++r->pix.x < r->scenes->res.x)
		{
			cam_ray = init_camera_ray(r->pix, r->scenes);
			r->scenes->cameras->pixel_map[r->pix.y][r->pix.x] =
				cast_primary_ray(r, &cam_ray);
		}
	}*/

	t_raytracing_tools *d_r;
	C(1)
	d_r = allocate_memory(r);
	C(2)
	dim3 block_size;
	dim3 grid_size;


	block_size = dim3(16, 16);
	grid_size = dim3(r->scenes->res.x / block_size.x + 1, r->scenes->res.y / block_size.y + 1);
	C(3)
	// print_scenes(d_r->scenes);
	render_pixel<<<grid_size, block_size>>>(d_r);
	cudaDeviceSynchronize();
	// printf("%f\n", d_r->scenes->cameras->pos.y);
	int i;
	i = -1;


	C(4)
	cudaMemcpy(r->scenes->cameras->pixel_map, d_r->scenes->cameras->pixel_map, sizeof(t_color *) * r->scenes->res.y, cudaMemcpyDeviceToHost);
	// r->scenes->cameras->pixel_map = d_r->scenes->cameras->pixel_map;
	C(5)
	while (++i < r->scenes->res.y) ;
		//printf("%f\n", d_r->scenes->cameras->pixel_map[i][0].x);
		//memcpy(r->scenes->cameras->pixel_map[i], d_r->scenes->cameras->pixel_map[i], sizeof(t_color) * r->scenes->res.x);
		// r->scenes->cameras->pixel_map[i] = d_r->scenes->cameras->pixel_map[i];
	C(6)
}

// __device__
// static void	display_percentage(int num)
// {
// 	ft_printf("Loading...%i%%\r", num);
// }
