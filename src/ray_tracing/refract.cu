/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 15:37:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/04 15:25:27 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Given a ray direction and normal at hit point, returns the direction of the
** refracted ray.
*/

__device__
t_vec3	refract(t_vec3 ray_dir, t_vec3 nhit, float ray_ior, float new_ior)
{
	float	cosi;
	t_vec3	eta;
	float	k;
	t_vec3	n;

	cosi = ft_clampf(v_dot(ray_dir, nhit), -1, 1);
	eta.x = ray_ior;
	eta.y = new_ior;
	n = nhit;
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		ft_swapf(&eta.x, &eta.y);
		n = v_scale(nhit, -1);
	}
	eta.z = eta.x / eta.y;
	k = 1 - eta.z * eta.z * (1 - cosi * cosi);
	return (k < 0 ? v_new(NAN, NAN, NAN) : v_add(v_scale(ray_dir, eta.z),
		v_scale(n, (eta.z * cosi - sqrtf(k)))));
}
