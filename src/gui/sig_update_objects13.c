/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_update_objects13.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 11:42:19 by tgros             #+#    #+#             */
/*   Updated: 2017/06/06 11:48:50 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	*sig_update_obj_beer_lambert(GtkWidget *spin_button, t_gtk_tools *g)
{
	t_object	*obj;

	printf("sig_update_obj_beer_lambert\n");
	obj = get_selected_object(g);
	obj->beer_lambert = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button));
	(g->updating_gui) ? 0 : obj_render_sig(g);
	return (NULL);
}
