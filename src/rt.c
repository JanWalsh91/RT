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

/*
** Manages SDL functions and sets pixel colors found from render() to
** the renderer.
*/

#include <time.h>

int	rt(t_raytracing_tools *r)
{
	t_env	env;
	t_color	col;
	t_pt2	i;

	clock_t start = clock();
	render(r->scenes);
	clock_t stop = clock();
	printf("\nTotal de la fonction render : %f\n",
  	(float)(stop - start) / (float)CLOCKS_PER_SEC * 1000.0f);
	
	init_sdl(r->scenes, &env);
	SDL_RenderClear(env.ren);
	i.y = -1;
	while (++i.y < r->scenes->res.y)
	{
		i.x = -1;
		while (++i.x < r->scenes->res.x)
		{
			col = (r->scenes)->cameras->pixel_map[i.y * r->scenes->res.x + i.x];
			SDL_SetRenderDrawColor(env.ren, col.x, col.y, col.z,
				SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(env.ren, i.x, i.y);
		}
	}
	SDL_RenderPresent(env.ren);
	handle_sdl_events(r->scenes, &env);
	SDL_DestroyWindow(env.win);
	SDL_Quit();
	return (1);
}
