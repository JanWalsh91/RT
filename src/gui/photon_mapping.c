/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:56:52 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 17:13:28 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.cuh"
#include "cuda_call.cuh"

void	render_ppm(struct s_gtk_tools *g, t_tile tile)
{
	int	photons_shot;

	photons_shot = 0;
	perpare_memory(g->r);
	while (photons_shot < (int)g->r->scene->photon_count && g->win)
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
		photons_shot += g->r->scene->photons_per_pass;
		copy_1(g->r);
		ft_memcpy(gdk_pixbuf_get_pixels(g->pixbuf), g->r->d_pixel_map,
			g->r->scene->res.x * 3 * g->r->scene->res.y);
		g->win ? gtk_widget_queue_draw(g->win) : 0;
		copy_2(g->r);
	}
	free_map_and_list(g->r);
}
