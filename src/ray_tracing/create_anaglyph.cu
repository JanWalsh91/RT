/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_anaglyph.cu                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 09:52:05 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 10:20:12 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "../../inc/cuda_call.h"
#include "photon_mapping.h"

__global__
static void			get_look_at_position(t_scene *scene, t_vec3 *pos);
static t_vec3		get_look_at(t_scene *scene);
static void			update_camera(t_camera *camera);
__global__
static void			create_anaglyph(t_color *left, t_color *right,
					t_scene *scene, t_tile tile);
__global__
void render_pixel	(t_scene *scene, t_color *d_pixel_map,
					t_region *region_map, t_tile tile);

void				create_anaglyph_wrapper(t_raytracing_tools *r,
					dim3 blockSize, dim3 gridSize, t_tile tile)
{
	t_vec3	original;
	
	original = r->scene->cameras->dir;
	r->scene->cameras->dir = v_norm(v_sub(get_look_at(r->d_scene),
		r->scene->cameras->pos));
	r->scene->cameras->pos.x += 0.05;
	update_camera(r->scene->cameras);
	r->scene->cameras->filter = F_RIGHT_CYAN;
	gpu_assert(cudaMemcpy(r->h_d_scene->cameras, r->scene->cameras,
		sizeof(t_camera), cudaMemcpyHostToDevice));
	gpu_assert((cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene),
		cudaMemcpyHostToDevice)));
	render_pixel<<<gridSize, blockSize>>>(r->d_scene, r->d_pixel_map_3d,
		r->d_region_map, tile);
	gpu_assert((cudaDeviceSynchronize()));
	r->scene->cameras->pos.x -= 0.05;
	r->scene->cameras->dir = original;
	update_camera(r->scene->cameras);
	r->scene->cameras->filter = F_LEFT_RED;
	gpu_assert(cudaMemcpy(r->h_d_scene->cameras, r->scene->cameras,
		sizeof(t_camera), cudaMemcpyHostToDevice));
	gpu_assert((cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene),
		cudaMemcpyHostToDevice)));
	create_anaglyph<<<gridSize, blockSize>>>(r->d_pixel_map,
		r->d_pixel_map_3d, r->d_scene, tile);
	gpu_assert((cudaDeviceSynchronize()));
}

static t_vec3		get_look_at(t_scene *scene)
{
	t_vec3	h_look_at;
	t_vec3	*d_look_at;

	if (cudaMalloc(&d_look_at, sizeof(t_vec3)))
		exit(0);
	get_look_at_position<<<1, 1>>>(scene, d_look_at);
	gpu_assert(cudaMemcpy(&h_look_at, d_look_at, sizeof(t_vec3),
		cudaMemcpyDeviceToHost));
	return (h_look_at);
}

__global__
static void			get_look_at_position(t_scene *scene, t_vec3 *pos)
{
	t_ray				cam_ray;
	t_raytracing_tools	r;
	t_dpt2				aa_i;
	int					i;

	r.pix.x = scene->res.x / 2.0;
	r.pix.y = scene->res.y / 2.0;
	r.scene = scene; 
    r.idx = scene->res.x * r.pix.y + r.pix.x;
	aa_i.x = 0.5;
	aa_i.y = 0.5;
	memset(&r.ior_list, 0, sizeof(float) * (MAX_RAY_DEPTH + 1));
	cam_ray = init_camera_ray(&r, aa_i);
	r.t = INFINITY; 
	i = -1;
	while (scene->objects[++i].type != T_INVALID_TOKEN)
	{
		if (intersects(&r, &cam_ray, i) && r.t > cam_ray.t)
			r.t = cam_ray.t;
	}
	if (r.t == INFINITY)
		*pos = v_new(NAN, NAN, NAN);
	else
		*pos = v_add(cam_ray.origin, v_scale(cam_ray.dir, r.t)); 
}

static void			update_camera(t_camera *camera)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = v_norm(camera->dir);
	if (v_dot(forward, v_new(0, 1, 0)) > 0.9999 ||
		v_dot(forward, v_new(0, 1, 0)) < -0.9999)
		right = v_new(1, 0, 0);
	else
		right = v_norm(v_cross(v_new(0, 1, 0), forward));
	up = v_norm(v_cross(forward, right));
	m_new_identity(&camera->ctw);
	camera->ctw[0][0] = right.x;
	camera->ctw[0][1] = right.y;
	camera->ctw[0][2] = right.z;
	camera->ctw[1][0] = up.x;
	camera->ctw[1][1] = up.y;
	camera->ctw[1][2] = up.z;
	camera->ctw[2][0] = forward.x;
	camera->ctw[2][1] = forward.y;
	camera->ctw[2][2] = forward.z;
	camera->ctw[3][0] = camera->pos.x;
	camera->ctw[3][1] = camera->pos.y;
	camera->ctw[3][2] = camera->pos.z;
}

__global__
static void			create_anaglyph(t_color *left, t_color *right, t_scene *scene,
					t_tile tile)
{
	int		idx;
	t_pt2	pixel;

	pixel.x = (tile.id.x * tile.size) + (blockDim.x * blockIdx.x) + threadIdx.x;
	pixel.y = (tile.id.y * tile.size) + (blockDim.y * blockIdx.y) + threadIdx.y;
  	idx = scene->res.x * pixel.y + pixel.x;

	if (pixel.x < scene->res.x && pixel.y < scene->res.y)
	{
		left[idx].g = right[idx].g;
		left[idx].b = right[idx].b;
	}
}
