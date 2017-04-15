/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fresnel_ratio.cu                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:25:09 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/15 15:28:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Calculates and returns the fresnel ratio.
*/

__device__
static double	get_fresnel_ratio2(double cosi, double etai, double etat, double sint);

__device__
double			get_fresnel_ratio(t_vec3 ray_dir, t_vec3 normal, double ior)
{
	double	cosi;
	double	etai;
	double	etat;
	double	sint;

	cosi = ft_clampd(v_dot(ray_dir, normal), -1, 1);
	etai = 1;
	etat = ior;
	if (cosi  > 0)
		ft_swapd(&etai, &etat);
	sint = etai / etat * __dsqrt_rn(1 - cosi * cosi > 0.0 ? 1 - cosi * cosi > 0.0 : 0.0));
	if (sint >= 1) 
		return (1);
	else
		return (get_fresnel_ratio2(cosi, etai, etat, sint));
	
}

__device__
static double	get_fresnel_ratio2(double cosi, double etai, double etat, double sint)
{
	double	cost;
	double 	Rs;
	double	Rp;

	cost = __dsqrt_rn((1 - sint * sint > 0 ? 1 - sint * sint : 0.0)); 
    cosi = cosi < 0 ? -cosi : cosi; 
    Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
    Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
	return ((Rs * Rs + Rp * Rp) / 2); 
}