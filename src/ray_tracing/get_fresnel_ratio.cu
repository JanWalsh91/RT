/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fresnel_ratio.cu                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:25:09 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 11:23:53 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the fresnel ratio.
*/

__device__
float	get_fresnel_ratio2(float cosi, float etai,
				float etat, float sint);

__device__
float			get_fresnel_ratio(t_vec3 ray_dir, t_vec3 normal,
				float n1, float n2)
{
	float	cosi;
	float	etai;
	float	etat;
	float	sint;

	cosi = ft_clampf(v_dot(ray_dir, normal), -1, 1);
	etai = n1;
	etat = n2;
	if (cosi > 0)
		ft_swapf(&etai, &etat);
	sint = (etai / etat) * (1 - cosi * cosi > 0.0 ?
		sqrtf(1 - cosi * cosi) : 0.0);
	if (sint >= 1)
		return (1);
	else
		return (get_fresnel_ratio2(cosi, etai, etat, sint));
}

__device__
float	get_fresnel_ratio2(float cosi, float etai,
				float etat, float sint)
{
	float	cost;
	float	rs;
	float	rp;

	cost = sqrtf((1 - sint * sint > 0 ? 1 - sint * sint : 0.0));
    cosi = cosi < 0 ? -cosi : cosi;
    rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
    rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
	return ((rs * rs + rp * rp) / 2);
}
