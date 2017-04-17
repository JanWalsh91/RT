/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_new_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:08:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/17 15:12:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void    *sig_new_object(GtkWidget *widget, t_gtk_tools *g)
{
    t_object	*obj; 
	
    printf("sig_new_object\n");

	if (!(obj = (t_object *)ft_memalloc(sizeof(t_object))))
		return (NULL);
	ft_bzero(obj, sizeof(t_object));
	
	obj->type = T_SPHERE;
	obj->rad = DEFAULT_RADIUS;
	obj->col = v_new(DEFAULT_COL_R, DEFAULT_COL_G, DEFAULT_COL_B);
	obj->kd = DEFAULT_KD;
	obj->ks = DEFAULT_KS;
	obj->ior = DEFAULT_IOR;
	obj->transparency = DEFAULT_TRANSPARENCY;
	obj->reflection = DEFAULT_REFLECTION;
	obj->specular_exp = DEFAULT_SPECULAR_EXP;
	obj->dir = v_new(DEFAULT_DIR_X, DEFAULT_DIR_Y, DEFAULT_DIR_Z);
	obj->height = DEFAULT_HEIGHT;
	obj->name = ft_strdup("New Object");
	obj->next = NULL;
	push_object(&(g->r->scene->objects), obj);
	update_grid_objects(g);
	return (NULL);
}