/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_print_scene.c                                 :+:      :+:    :+:   */
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

void *sig_print_scene(GtkWidget *button, t_gtk_tools *g)
{
	if (g->r->scene)
		print_scene(g->r->scene);
	else
		ft_printf("No scene\n");
	return (NULL);
}
