/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_new_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:08:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/17 15:12:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void    *sig_new_light(GtkWidget *widget, t_gtk_tools *g)
{
    t_light     *light;

    printf("sig_new_light\n");
    if (!(light = (t_light *)ft_memalloc(sizeof(t_light))))
		return (NULL);
	ft_bzero(light, sizeof(t_light));
	
	// light->type = T_SPHERICAL;
    light->intensity = DEFAULT_INTENSITY;
	light->col = v_new(DEFAULT_COL_R, DEFAULT_COL_G, DEFAULT_COL_B);
	light->name = ft_strdup("New light");
	light->next = NULL;
	push_light(&(g->r->scene->lights), light);
	update_grid_lights(g);
	return (NULL);
}