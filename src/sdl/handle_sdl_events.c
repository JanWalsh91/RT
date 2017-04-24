/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sdl_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 14:15:05 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/24 16:41:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
// # include <gtk/gtk.h>
#include "../inc/cuda_call.h"
#include "gui.h"
#include "pthread.h"
// #include <pthread_np.h>

/*
** Handles SDL user events.
*/

static int	init_window(t_scene *scene, t_env *env);
static int	init_rederer(t_scene *scene, t_env *env);

int	handle_sdl_events(t_gtk_tools *g)
{
	t_color	col;
	t_pt2	i; 

	g->quit = 0;
	while (!g->quit)
	{
		while (g->sdl)
		{
			if (!g->env.win)
			{
				// open window
				init_window(g->r->scene, &g->env);
				init_rederer(g->r->scene, &g->env);
			}
			if (g->r->update.render)
			{
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
				SDL_RaiseWindow(g->env.win);
				g->r->update.render = 0;
				// g->r->update.objects = 0;
			}
			// SDL_WaitEvent(&g->env.e);
			// while (SDL_PollEvent(&g->env.e))
			// {
			// 	if (g->env.e.window.event == SDL_WINDOWEVENT_CLOSE ||
			// 		(g->env.e.key.type == SDL_KEYDOWN &&
			// 		g->env.e.key.keysym.sym == SDLK_ESCAPE))
			// 	{
			// 		g->sdl = 0;
			// 		SDL_DestroyWindow(g->env.win);
			// 		SDL_Quit();
			// 	}
			// }
		}
	}
	return (1);
}

static int	init_window(t_scene *scene, t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("BIG ERROR\n\n\t");
		return (0);
	}
	printf("scene name: [%s]\n", scene->name);
	env->win = SDL_CreateWindow(scene->name, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, scene->res.x, scene->res.y, SDL_WINDOW_SHOWN);
	if (!env->win)
	{
		printf("SDL window creation error");
		SDL_Quit();
		return (0);
	}
	return (1);
}

static int	init_rederer(t_scene *scene, t_env *env)
{
	(void)scene;
	env->ren = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_ACCELERATED);
	if (!env->ren)
	{
		printf("SDL render creation error");
		SDL_DestroyWindow(env->win);
		SDL_Quit();
		return (1);
	}
	return (1);
}