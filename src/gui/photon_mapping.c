/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:56:52 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 12:32:43 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cuda_call.h"
#include <cuda_runtime.h>
#include "gui.h"

void	perpare_memory(struct s_gtk_tools *g);

void	render_ppm(struct s_gtk_tools *g, t_tile tile)
{
	int	photons_shot;
	photons_shot = 0;

	g->r->h_d_scene->photon_iteration = 1;
	perpare_memory(g);
	while (photons_shot < (int)g->r->scene->photon_count)
	{
		photon_mapping_pass(g->r);
		tile.id.y = 0;
		tile.id.x = 0;
		while (tile.id.x != tile.col && tile.id.y != tile.row)
		{ 
			get_region_map_tile(g->r, tile);
			radiance_estimation_pass(g->r, tile);
			copy_region_map_tile(g->r, tile);
			increment_tile(&tile.id, tile.col);
		}
		++g->r->h_d_scene->photon_iteration;
		photons_shot += g->r->scene->photon_count_per_pass;
		cudaMemcpy(g->r->d_scene, g->r->h_d_scene, sizeof(t_scene),
			cudaMemcpyHostToDevice);
		ft_memcpy(gdk_pixbuf_get_pixels(g->pixbuf), g->r->d_pixel_map,
			g->r->scene->res.x * 3 * g->r->scene->res.y);
		gtk_widget_queue_draw(g->win);
		cudaMemcpy(g->r->d_pixel_map, g->r->rt_pixel_map, sizeof(t_color) *
			g->r->scene->res.x * g->r->scene->res.y, cudaMemcpyHostToHost);
	}
	cudaFreeHost(g->r->rt_pixel_map);
	cudaFree(g->r->h_d_scene->photon_list);
}

void	perpare_memory(struct s_gtk_tools *g)
{
	(cudaMallocHost((void **)&g->r->rt_pixel_map, sizeof(t_color) *
		g->r->scene->res.y * g->r->scene->res.x));
	cudaMemcpy(g->r->rt_pixel_map, g->r->d_pixel_map, sizeof(t_color) *
		g->r->scene->res.y * g->r->scene->res.x, cudaMemcpyHostToHost);
	cudaMalloc((void **)&(g->r->h_d_scene->photon_list), sizeof(t_photon) *
		PHOTON_BOUNCE_MAX * g->r->scene->photon_count_per_pass);
	cudaMemcpy(g->r->d_scene, g->r->h_d_scene, sizeof(t_scene),
		cudaMemcpyHostToDevice);
}
