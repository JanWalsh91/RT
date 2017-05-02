/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fresnel_ratio.cu                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:25:09 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/01 12:37:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the fresnel ratio.
*/

__device__
static float	get_fresnel_ratio2(float cosi, float etai, float etat, float sint);

__device__
float			get_fresnel_ratio(t_vec3 ray_dir, t_vec3 normal, float ior)
{
	float	cosi;
	float	etai;
	float	etat;
	float	sint;

	cosi = ft_clampf(v_dot(ray_dir, normal), -1, 1);
	etai = 1;
	etat = ior;
	if (cosi  > 0)
		ft_swapf(&etai, &etat);
	sint = etai / etat * sqrtf(1 - cosi * cosi > 0.0 ? 1 - cosi * cosi : 0.0);
	if (sint >= 1) 
		return (1);
	else
		return (get_fresnel_ratio2(cosi, etai, etat, sint));
	
}

__device__
static float	get_fresnel_ratio2(float cosi, float etai, float etat, float sint)
{
	float	cost;
	float 	Rs;
	float	Rp;

	cost = sqrtf((1 - sint * sint > 0 ? 1 - sint * sint : 0.0)); 
    cosi = cosi < 0 ? -cosi : cosi; 
    Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
    Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
	return ((Rs * Rs + Rp * Rp) / 2); 
}