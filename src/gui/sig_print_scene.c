/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_print_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 12:27:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 12:27:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "../inc/cuda_call.h"

void *sig_print_scene(GtkWidget *button, t_gtk_tools *g)
{
	(void)button;
	if (g->r->scene)
		print_scene(g->r->scene);
	else
		ft_printf("No scene\n");
	return (NULL);
}
