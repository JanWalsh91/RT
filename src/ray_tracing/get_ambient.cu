/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient.cu                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:04:10 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/02 17:19:14 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

/*
** Calculates and returns the ambient value of the color.
*/

__device__
t_color	get_ambient(t_scene *scene)
{
	return (v_clamp(v_scale(scene->ambient_light_color, scene->ka), 0, 255));
}
