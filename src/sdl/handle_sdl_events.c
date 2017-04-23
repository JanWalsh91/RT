/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sdl_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 14:15:05 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/23 18:37:21 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
// # include <gtk/gtk.h>
#include "../inc/cuda_call.h"
#include "gui.h"

/*
** Handles SDL user events.
*/

int	handle_sdl_events(t_scene *scenes, t_gtk_tools *g)
{
	int quit;
	t_color	col;
	t_pt2	i;

	quit = 0;
	(void)scenes;
	while (!quit)
	{
		// printf("%d\n", g->r->update.render);
		// sleep(1);
		if (g->r->update.render)
		{
			g->r->update.render = 0;
			printf("---UPDATE----\n");
			clock_t start = clock();
			render(g->r);
			clock_t stop = clock();
			printf("\nAppel du render : %f\n",
  			(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
			printf("End render\n");
			SDL_RenderClear(g->env.ren);

			i.y = -1;
			while (++i.y < g->r->scene->res.y)
			{
				i.x = -1;
				while (++i.x < g->r->scene->res.x)
				{
					col = g->r->d_pixel_map[i.y * g->r->scene->res.x + i.x];
					if (i.x == 200 && i.y == 200)
					{
						printf("checking for BLACK SCREEN BUG: col at 200, 200:");
						// print_vec(col);
					}
					SDL_SetRenderDrawColor(g->env.ren, col.r, col.g, col.b,
						SDL_ALPHA_OPAQUE);
					SDL_RenderDrawPoint(g->env.ren, i.x, i.y);
				}
			}
			SDL_RenderPresent(g->env.ren);
			// g->r->update.objects = 0;
		}
		// SDL_WaitEvent(&g->env.e);
		if (g->env.e.window.event == SDL_WINDOWEVENT_CLOSE ||
			(g->env.e.key.type == SDL_KEYDOWN &&
			g->env.e.key.keysym.sym == SDLK_ESCAPE))
			quit = 1;
	}
	return (1);
}
