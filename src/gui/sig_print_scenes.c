/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_print_scenes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:07:07 by tgros             #+#    #+#             */
/*   Updated: 2017/04/28 17:07:21 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"

void *sig_print_scenes(GtkWidget *button, t_gtk_tools *g)
{
	print_scenes(g->r->scene);
	return (NULL);
}
