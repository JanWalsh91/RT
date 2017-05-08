/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_mapping.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:38:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/08 13:03:55 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHOTON_MAPPING_H
# define PHOTON_MAPPING_H

# include "rt.h"

/*
** KD tree
*/

typedef struct	s_kd_tree
{
	void		*content;
	char		dim; //current dimension, necessary?
	s_kd_tree	*left;
	s_kd_tree	*right;
}				t_kd_tree;

t_kd_tree	*kd_create_tree(int dim);
t_kd_tree	*kd_create_node(void *data);
void		kd_free_tree(t_kd_tree *tree);
void		kd_free_node(t_kd_tree *node);
t_kd_tree	*kd_sort_tree(t_kd_tree *tree);
t_kd_tree	*kd_find_nearest(t_kd_tree *tree, t_vec3 pos);

typedef struct	s_photon
{
	t_vec3		pos;
	t_vec3		dir;
	t_color		col;
}				t_photon;

void	shoot_photon(t_photon *photon);
void	shoot_photon_group(t_photon *photons);
void	init_photon_group(t_photon *photons, t_obj *obj);
void	init_photon(t_photon *photon, t_obj *obj);

#endif