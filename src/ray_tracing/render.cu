/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/31 16:02:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "photon_mapping.h"
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

// __device__
// void	printte_matrix(t_matrix m)
// {
// 	int i;
// 	int	y;

// 	y = -1;
// 	while (++y < 4)
// 	{
// 		i = -1;
// 		while (++i < 4)
// 			printf("[%f]", m[y][i]);
// 		printf("\n");
// 	}
// }

__global__ void render_pixel(t_scene *scene, t_color *d_pixel_map, t_region *region_map, t_tile tile)
{
	t_ray				cam_ray;
	t_raytracing_tools	r;
	t_dpt2				aa_i;
	float				sample_size;
	int					i;
	t_vec3				moyenne;
	int					i2;

	r.pix.x = (tile.id.x * tile.size) + (blockDim.x * blockIdx.x) + threadIdx.x;
	r.pix.y = (tile.id.y * tile.size) + (blockDim.y * blockIdx.y) + threadIdx.y;
	r.scene = scene; 
    r.idx = scene->res.x * r.pix.y + r.pix.x;
	if (r.pix.x < scene->res.x && r.pix.y < scene->res.y)
	{
		if (region_map)
		{
			i2 = (r.pix.x % tile.size) + (r.pix.y % tile.size) * tile.size;
			// printf("idx: [%d]i2: %d\n", r.idx, i2);
			r.d_region_map = &region_map[i2];
		}
		// initialize ior list
		// r.ior_list = (float *)malloc(sizeof(float) * (scene->ray_depth + 1));
		// printf("AA de la scene : %d\n", scene->is_aa);
		if (scene->is_aa == 1)
		{
			aa_i.x = 0.5;
			aa_i.y = 0.5;
			memset(&r.ior_list, 0, sizeof(float) * (MAX_RAY_DEPTH + 1));
			cam_ray = init_camera_ray(&r, aa_i);
			d_pixel_map[r.idx] = filter(cast_primary_ray(&r, &cam_ray), scene->cameras->filter);
			if (region_map)
			{
				r.d_region_map->hit_pt = cam_ray.hit;
				r.d_region_map->ray_dir = cam_ray.dir;
				r.d_region_map->normal = v_scale(cam_ray.nhit, cam_ray.n_dir);
				r.d_region_map->kd = scene->objects[cam_ray.hit_obj].kd;
			
			
				if (r.idx == 1)
					printf("hit_pt: [%f, %f, %f], ray_dir: [%f, %f, %f], normal: [%f, %f, %f], kd: %f\n", r.d_region_map->hit_pt.x, r.d_region_map->hit_pt.y, r.d_region_map->hit_pt.z, 
					r.d_region_map->ray_dir.x, r.d_region_map->ray_dir.y, r.d_region_map->ray_dir.z, r.d_region_map->normal.x, r.d_region_map->normal.y, r.d_region_map->normal.z,
					r.d_region_map->kd);
			}
			
		}
		else
		{
			sample_size =  1 / (float)scene->is_aa;
			aa_i.x = 0.0;
			aa_i.y = 0.0;
			i = -1;
			moyenne.x = 0;
			moyenne.y = 0;
			moyenne.z = 0;
			while (++i < scene->is_aa * scene->is_aa)
			{
				aa_i.x += sample_size;
				if (i % (scene->is_aa - 1) == 0)
				{
					aa_i.x = 0.0;
					aa_i.y += sample_size;
				}
				memset(&r.ior_list, 0, sizeof(float) * (MAX_RAY_DEPTH + 1));
				cam_ray = init_camera_ray(&r, aa_i);
				moyenne = v_add(moyenne, col_to_vec(cast_primary_ray(&r, &cam_ray)));
			}
			moyenne.x /= (scene->is_aa * scene->is_aa);
			moyenne.y /= (scene->is_aa * scene->is_aa);
			moyenne.z /= (scene->is_aa * scene->is_aa);
			d_pixel_map[r.idx] = filter(vec_to_col(moyenne), scene->cameras->filter);
		}
	}
}

//'dis is wonderful
__global__ void create_anaglyph(t_color *left, t_color *right, t_scene *scene, t_tile tile)
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
	// __syncthreads();
}

// Trouver un moyen pour appeler cette fonction ><
void	update_camera(t_camera *camera)
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

void		render(t_raytracing_tools *r, t_tile tile)
{
	dim3 		blockSize;
	dim3 		gridSize;
	int			size;

	size = (tile.size / BLOCK_DIM) + ((tile.size % BLOCK_DIM) ? 1 : 0);
	blockSize = dim3(BLOCK_DIM, BLOCK_DIM, 1);
	gridSize = dim3(size, size);

	// cudaEvent_t start, stop;
	// cudaEventCreate(&start); 
	// cudaEventCreate(&stop);
	// cudaEventRecord(start);
	printf("launch kernel:\n");
	render_pixel<<<gridSize, blockSize>>>(r->d_scene, r->d_pixel_map, r->d_region_map, tile);
	// printf("Iteration i = %d	\n", i++);
	// cudaEventRecord(stop);
	// cudaEventSynchronize(stop);
	// float milliseconds = 0;
	// cudaEventElapsedTime(&milliseconds, start, stop);


	cudaError_t errSync  = cudaGetLastError();
	cudaError_t errAsync = cudaDeviceSynchronize();
	if (errSync != cudaSuccess)
		printf("Sync kernel error: %s\n", cudaGetErrorString(errSync));
	if (errAsync != cudaSuccess)
		printf("Async kernel error: %s\n", cudaGetErrorString(errAsync));
	if (errSync != cudaSuccess || errAsync != cudaSuccess)
		exit(-1);
	//beautiful....
	// printf("=============== EXECUTION ================== \n");
	// printf("Kernel duration: %f milliseconds\n", milliseconds);
	// printf("============================================ \n");

	// gpuErrchk((cudaDeviceSynchronize()));

	if (r->scene->is_3d)
	{
		printf("3d\n");
		//IS HARDCODING THESE VALUES CORRECT?
		r->scene->cameras->pos.x += 0.05;
		r->scene->cameras->dir.x -= 0.01;
		r->scene->cameras->dir = v_norm(r->scene->cameras->dir);
		update_camera(r->scene->cameras);
		r->scene->cameras->filter = F_RIGHT_CYAN;
		gpuErrchk(cudaMemcpy(r->h_d_scene->cameras, r->scene->cameras, sizeof(t_camera), cudaMemcpyHostToDevice));
		gpuErrchk((cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice)));
		render_pixel<<<gridSize, blockSize>>>(r->d_scene, r->d_pixel_map_3d, r->d_region_map, tile);
		gpuErrchk((cudaDeviceSynchronize()));
		r->scene->cameras->pos.x -= 0.05;
		r->scene->cameras->dir.x += 0.01;
		r->scene->cameras->dir = v_norm(r->scene->cameras->dir);
		update_camera(r->scene->cameras);
		r->scene->cameras->filter = F_LEFT_RED;
		gpuErrchk(cudaMemcpy(r->h_d_scene->cameras, r->scene->cameras, sizeof(t_camera), cudaMemcpyHostToDevice));
		gpuErrchk((cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice)));
		create_anaglyph<<<gridSize, blockSize>>>(r->d_pixel_map, r->d_pixel_map_3d, r->d_scene, tile);
		gpuErrchk((cudaDeviceSynchronize()));
	}

}
