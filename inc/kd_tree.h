/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kd_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 15:06:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/06 17:29:14 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/inc/libft.h"
#include "../Libmathft/inc/libmathft.h"


struct typedef	s_kd_tree
{
	int	dim;
	
}				t_kd_tree;

struct typedef	s_photon
{
	t_vec3		pos;
	t_vec3		dir; //final direction important for weighting influence of photon on hitpoint.
	t_vec3		color;
	float		intensity; // may not be necessary. Instead use one value:
	// intensity of one photon: total intensity / photon count
}				t_photon;