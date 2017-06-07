/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:56:52 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/07 14:07:25 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cuda_call.h"
#include <cuda_runtime.h>
#include "gui.h"


// TO DO add interaction with user to be able to stop

void	render_ppm(struct s_gtk_tools *g, t_tile tile)
{
	printf("render_ppm\n");
	int	photons_shot;
	
	photons_shot = 0;

	//rt pixel map is the original map.
	printf("Resolution : %d, %d\n", g->r->scene->res.x, g->r->scene->res.y);
	(cudaMallocHost((void **)&g->r->rt_pixel_map, sizeof(t_color) * g->r->scene->res.y * g->r->scene->res.x));
	cudaMemcpy(g->r->rt_pixel_map, g->r->d_pixel_map, sizeof(t_color) * g->r->scene->res.y * g->r->scene->res.x, cudaMemcpyHostToHost);
	//malloc space for photons on GPU
	cudaMalloc((void **)&(g->r->h_d_scene->photon_list), sizeof(t_photon) * PHOTON_BOUNCE_MAX * g->r->scene->photon_count_per_pass);
	// printf("AAAAAA-----photon_iter: %d, count per pass: %d\n", g->r->h_d_scene->photon_iteration, g->r->h_d_scene->photon_count_per_pass);	
	g->r->h_d_scene->photon_iteration = 1;
	cudaMemcpy(g->r->d_scene, g->r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice);
	while (photons_shot < (int)g->r->scene->photon_count)
	{
		//photon_mapping_pass
		// printf("pre photon pass: %f\n", g->r->h_region_map[0]->radius);
		photon_mapping_pass(g->r);
		// printf("post photon pass: %f\n", g->r->h_region_map[0]->radius);
		//radiance estimation pass
		// exit(0);
		tile.id.y = 0;
		tile.id.x = 0;
		while ((tile.id.y + 1) <= tile.row)
		{ 
			get_region_map_tile(g->r, tile);
			// printf("pre radiance pass: %f\n", g->r->h_region_map[0]->radius);
			radiance_estimation_pass(g->r, tile);
			// printf("post radiance pass: %f\n", g->r->h_region_map[0]->radius);
			copy_region_map_tile(g->r, tile);
			// printf("post copy after radiance pass: %f\n", g->r->h_region_map[0]->radius);
			increment_tile(&tile.id, tile.col);
		}
		++g->r->h_d_scene->photon_iteration;
		photons_shot += g->r->scene->photon_count_per_pass;
		cudaMemcpy(g->r->d_scene, g->r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice);
		ft_memcpy(gdk_pixbuf_get_pixels(g->pixbuf), g->r->d_pixel_map, g->r->scene->res.x * 3 * g->r->scene->res.y);
		gtk_widget_queue_draw(g->win);
		cudaMemcpy(g->r->d_pixel_map, g->r->rt_pixel_map, sizeof(t_color) * g->r->scene->res.x * g->r->scene->res.y, cudaMemcpyHostToHost);
		sleep(1);
	}
	cudaFreeHost(g->r->rt_pixel_map);
	cudaFree(g->r->h_d_scene->photon_list);
	// free();
}

// static void	reset_photon_map(t_raytracing_tools *r)
// {
// 	cudaFree(r->h_d_scene->photon_list);
// 	gpu_errchk(cudaMalloc(&(r->h_d_scene->photon_list), sizeof(t_photon) * PHOTON_BOUNCE_MAX * r->scene->photon_count_per_pass));
// 	gpu_errchk(cudaMemcpy(r->d_scene, r->h_d_scene, sizeof(t_scene), cudaMemcpyHostToDevice));	
// }