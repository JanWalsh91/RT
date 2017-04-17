/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 15:37:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/17 12:24:08 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Given a ray direction and normal at hit point, returns the direction of the
** refracted ray.
*/

__device__
t_vec3	refract(t_vec3 ray_dir, t_vec3 nhit, double ior)
{
	double	cosi;
	double	etai;
	double	etat;
	double	eta;
	float	k;
	t_vec3	n;

	cosi = ft_clampd(v_dot(ray_dir, nhit), -1, 1);
	etai = 1;
	etat = ior;
	n = nhit;
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		ft_swapd(&etai, &etat);
		n = v_scale(nhit, -1);
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	//if k < 0, there is no refracted ray;
	return (k < 0 ? v_new(0, 0, 0) : v_add(v_scale(ray_dir, eta), v_scale(n, (eta * cosi - __dsqrt_rn(k))))); 
}
// Vec3f refract(const Vec3f &I, const Vec3f &N, const float &ior) 
// { 
//     float cosi = clamp(-1, 1, I.dotProduct(N)); 
//     float etai = 1, etat = ior; 
//     Vec3f n = N; 
//     if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -N; } 
//     float eta = etai / etat; 
//     float k = 1 - eta * eta * (1 - cosi * cosi); 
//     return k < 0 ? 0 : eta * I + (eta * cosi - sqrtf(k)) * n; 
// } 