/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 15:41:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 16:50:45 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

/*
** Resets the attributes.
*/

int	reset_attributes(t_attributes *att)
{
	att->res.x = -1;
	att->res.y = -1;
	att->ray_depth = -1;
	att->ka = NAN;
	att->ambient_light_color = v_new(NAN, NAN, NAN);
	att->intensity = NAN;
	att->fov = NAN;
	att->pos = v_new(NAN, NAN, NAN);
	att->dir = v_new(NAN, NAN, NAN);
	att->rot = v_new(NAN, NAN, NAN);
	att->look_at = v_new(NAN, NAN, NAN);
	att->col = v_new(NAN, NAN, NAN);
	att->rad = NAN;
	att->height = NAN;
	att->refraction = NAN;
	att->reflection = NAN;
	att->specular_exp = NAN;
	att->kd = NAN;
	att->ks = NAN;
	att->transparency = NAN;
	return (1);
}
