/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.cu                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 15:37:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/03 15:10:11 by jwalsh           ###   ########.fr       */
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
	float	etai;
	float	etat;
	float	eta;
	float	k;
	t_vec3	n;

	cosi = ft_clampf(v_dot(ray_dir, nhit), -1, 1);
	etai = ray_ior;
	etat = new_ior;
	n = nhit;
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		ft_swapf(&etai, &etat);
		n = v_scale(nhit, -1);
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	//if k < 0, there is no refracted ray;
	return (k < 0 ? v_new(NAN, NAN, NAN) : v_add(v_scale(ray_dir, eta), v_scale(n, (eta * cosi - sqrtf(k))))); 
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