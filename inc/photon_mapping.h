/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_mapping.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:38:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/18 14:29:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHOTON_MAPPING_H
# define PHOTON_MAPPING_H

# include "rt.cuh"

/*
** KD tree
*/

typedef struct	s_kd_tree
{
	t_vec3		pos;
	t_vec3		dir;
	t_color		col;
	t_vec3		n;
	char		dim; //current dimension, necessary?
	struct s_kd_tree	*left;
	struct s_kd_tree	*right;
}				t_kd_tree;

void			create_kd_tree(struct s_photon **photon_list, t_kd_tree **root, int photon_count);
void			sort_kd_tree(t_kd_tree **root, int dim, t_kd_tree **sorted);
void			free_kd_tree(t_kd_tree *root);
typedef struct	s_photon
{
	t_vec3		pos;
	t_vec3		dir;
	t_color		col;
	t_vec3		n;
}				t_photon;

typedef struct	s_selected_photon
{
	t_kd_tree	*photon;
	float		dist2;
}				t_selected_photon;

#endif