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
	handle_sdl_events(g);
	return (NULL);
}
