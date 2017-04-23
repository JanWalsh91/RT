/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:39:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/04 16:43:50 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.cuh"
#include "../inc/cuda_call.h"
#include "gui.h"

/*
** Manages SDL functions and sets pixel colors found from render() to
** the renderer.
*/

#include <time.h>


void	*rt(t_gtk_tools *g)
{
	t_color	col;
	t_pt2	i;

	// render(g->r);
	// init_sdl(g->r->scene, &g->env);
	// SDL_RenderClear(g->env.ren);
	// i.y = -1;
	// while (++i.y < g->r->scene->res.y)
	// {
	// 	i.x = -1;
	// 	while (++i.x < g->r->scene->res.x)
	// 	{
	// 		// col = (g->r->scene)->cameras->pixel_map[i.y * g->r->scene->res.x + i.x];
	// 		// col = g->r->d_pixel_map[i.y * g->r->scene->res.x + i.x];
	// 		if (i.x == 200 && i.y == 200)
	// 		{
	// 			printf("checking for BLACK SCREEN BUG: col at 200, 200:");
	// 			// print_vec(col);
	// 		}
	// 		// SDL_SetRenderDrawColor(g->env.ren, col.r, col.g, col.b,
	// 			// SDL_ALPHA_OPAQUE);
	// 		// SDL_RenderDrawPoint(g->env.ren, i.x, i.y);
	// 	}
	// }
	// SDL_RenderPresent(g->env.ren);
	handle_sdl_events(g->r->scene, g);
	SDL_DestroyWindow(g->env.win);
	SDL_Quit();
	return (NULL);
}
