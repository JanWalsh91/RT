/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flares.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 10:18:02 by tgros             #+#    #+#             */
/*   Updated: 2017/05/25 10:24:48 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "../../inc/cuda_call.h"


int		get_light_count(t_light *light)
{
	int 	i;
	t_light	*l_ptr;

	i = 0;
	l_ptr = light;
	while (l_ptr)
	{
		++i;
		l_ptr = l_ptr->next;
	}
	return (i);
}

__device__
bool	get_view_pane_intersection(t_ray *ray, t_camera *cam)
{
	float d1;
	t_vec3	v1;
	float r1;

	d1 = v_dot(v_scale(cam->dir, -1), ray->dir);
	if (d1 > -1e-20)
		return (false);
	v1 = v_sub(v_add(cam->pos, cam->dir), cam->pos);
	r1 = v_dot(v1, v_scale(cam->dir, -1)) / d1;
	if (r1 < 0)
		return (false);
	ray->t = r1;
	printf("T: %f\n", ray->t);
	return (true);
}

__device__
t_pt2	get_pane_coords(t_ray *ray, t_camera *cam, t_scene *scene)
{
	t_pt2	coord;
	t_vec3	ortho_x;
	t_vec3	ortho_y;
	t_vec3	proj_dir;

	proj_dir = v_sub(ray->dir, v_scale(cam->dir, -1));
	ortho_x = v_cross(v_new(0, 1, 0), v_scale(cam->dir, -1));
	ortho_y = v_cross(v_scale(cam->dir, -1), ortho_x);
	ortho_x = v_norm(ortho_x);
	ortho_y = v_norm(ortho_y);
	ray->hit = v_add(ray->origin, v_scale(ray->dir, ray->t));
	coord.x = (int)(v_dot(v_scale(ortho_x, -1), proj_dir) * scene->res.x * 0.5 / scene->image_aspect_ratio / cam->scale + scene->res.x * 0.5);
	coord.y = (int)(v_dot(v_scale(ortho_y, -1), proj_dir) * scene->res.y * 0.5 / cam->scale + scene->res.y / 2);
	// printf("coords: [%d, %d]\n", coord.x, coord.y);
	return (coord);
}

__global__
void	init_light_flares(t_scene *scene, t_light_flare_tools *tools)
{
	t_raytracing_tools	r;
	t_ray				ray;
	int					id;
	int					y;

	id = blockIdx.x;
	r.scene = scene;
	ray.t = INFINITY;
	ray.type = R_PRIMARY;
	r.t = INFINITY;
	tools[id].is_valid = 1;
	ray.origin = scene->cameras->pos;
	ray.dir = v_norm(v_sub(scene->lights[id].pos, scene->cameras->pos));
	if (!get_view_pane_intersection(&ray, scene->cameras))
	{
		tools[id].is_valid = 0;
		return ;
	}
	tools[id].pos = get_pane_coords(&ray, scene->cameras, scene);
	if (tools[id].pos.x < 0 || tools[id].pos.x >= scene->res.x || tools[id].pos.y < 0 || tools[id].pos.y >= scene->res.y)
	{
		tools[id].is_valid = 0;
		return ;
	}
	tools[id].dist = v_length(v_sub(scene->lights[id].pos, ray.origin));
	tools[id].max_rad = powf(scene->lights[id].intensity, 3) / tools[id].dist;
	tools[id].light = &scene->lights[id];
	if (tools[id].pos.x >= 0 && tools[id].pos.y >= 0 && tools[id].pos.x < scene->res.x && tools[id].pos.y < scene->res.y)
	{
		y = -1;
		while (scene->objects[++y].type != T_INVALID_TOKEN)
		{
			if (intersects(&r, &ray, y) &&
				ray.t < tools[id].dist && ray.t > 0.0)
			{
				tools[id].is_valid = 0;
				return ;
			}
		}
	}
	else
		tools[id].is_valid = 0;
}

__global__
void	draw_one_flare(t_light_flare_tools *tools, t_scene *scene, t_color *pixel_map)
{
	t_pt2	pix;
	float	rad;
	t_color	col;

	pix.x = (blockDim.x * blockIdx.x) + threadIdx.x;
	pix.y = (blockDim.y * blockIdx.y) + threadIdx.y;
	if (pix.x < tools->pos.x - tools->max_rad || pix.x > tools->pos.x + tools->max_rad ||
		pix.y < tools->pos.y - tools->max_rad || pix.y > tools->pos.y + tools->max_rad ||
		pix.x < 0 || pix.x >= scene->res.x || pix.y < 0 || pix.y >= scene->res.y || !tools->is_valid)
			return ;
	rad = sqrt(powf((tools->pos.x - pix.x), 2) + powf((tools->pos.y - pix.y), 2));
	col = pixel_map[pix.y * scene->res.x + pix.x];
	col = c_add(col, c_scale(vec_to_col(tools->light->col), ((tools->max_rad - rad) / (tools->max_rad * rad)) * tools->light->kflare));
	pixel_map[pix.y * scene->res.x + pix.x] = col;
}

void	add_lens_flare(t_raytracing_tools *r, t_color *pixel_map)
{
	int					i;
	t_light_flare_tools *tools;
	size_t				shift;

	r->t = INFINITY;
	int light_count = get_light_count(r->scene->lights);
	cudaMalloc(&tools, sizeof(t_light_flare_tools) * light_count);
	init_light_flares<<<light_count, 1>>>(r->d_scene, tools);
	cudaError_t errSync  = cudaGetLastError();
	cudaError_t errAsync = cudaDeviceSynchronize();
	if (errSync != cudaSuccess)
		printf("1 Sync kernel error: %s\n", cudaGetErrorString(errSync));
	if (errAsync != cudaSuccess)
		printf("1 Async kernel error: %s\n", cudaGetErrorString(errAsync));
	if (errSync != cudaSuccess || errAsync != cudaSuccess)
		exit(-1);
	i = -1;
	shift = 0;
	while (++i < light_count)
	{
		dim3 blockSize 	= dim3(BLOCK_DIM, BLOCK_DIM, 1);
		dim3 gridSize	= dim3(r->scene->res.x / BLOCK_DIM + 1, r->scene->res.y / BLOCK_DIM + 1);
		draw_one_flare<<<gridSize, blockSize>>>(tools + shift, r->d_scene, r->d_pixel_map);
		errSync  = cudaGetLastError();
		errAsync = cudaDeviceSynchronize();
		if (errSync != cudaSuccess)
			printf("2 Sync kernel error: %s\n", cudaGetErrorString(errSync));
		if (errAsync != cudaSuccess)
			printf("2 Async kernel error: %s\n", cudaGetErrorString(errAsync));
		if (errSync != cudaSuccess || errAsync != cudaSuccess)
			exit(-1);
		shift++;
	}
}

void 	lens_flare_wrapper(t_raytracing_tools *r)
{
	printf("lens_flare_wrapper\n");
	add_lens_flare(r, r->d_pixel_map);
	printf("end lens_flare_wrapper\n");
	cudaError_t errAsync = cudaDeviceSynchronize();
	if (errAsync != cudaSuccess)
		printf("Sync kernel error: %s\n", cudaGetErrorString(errAsync));
	printf("end lens_flare_wrapper");
}
