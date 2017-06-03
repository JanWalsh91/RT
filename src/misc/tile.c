/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 15:53:49 by tgros             #+#    #+#             */
/*   Updated: 2017/06/03 15:54:15 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	init_tile(t_tile *tile, t_gtk_tools *g)
{
	tile->size = g->r->settings.tile_size;
	tile->id.x = 0;
	tile->id.y = 0;
	tile->row = (g->r->scene->res.x / tile->size) +
					((g->r->scene->res.x % tile->size) ? 1 : 0);
	tile->col = (g->r->scene->res.y / tile->size) +
					((g->r->scene->res.y % tile->size) ? 1 : 0);
	tile->max = tile->row * tile->col;
}

void	increment_tile(t_pt2 *tile_id, int tile_row)
{
	if (++tile_id->x >= tile_row)
	{
		tile_id->x = 0;
		++tile_id->y;
	}
}
