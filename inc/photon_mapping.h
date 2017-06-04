/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_mapping.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:38:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/04 16:23:46 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHOTON_MAPPING_H
# define PHOTON_MAPPING_H

# include "rt.cuh"

# define PHOTON_BOUNCE_MAX 5
# define PHOTON_SEARCH_RADIUS 100

typedef struct s_region
{
	t_vec3	hit_pt; //hit point
	t_vec3	ray_dir; //incoming ray dir at hit point
	t_vec3	normal; //normal at hit point
	float	kd; //pointer to hit object
	float	radius; //search radius
	int		n; //photon count
	t_vec3	power; //accumulated normalized power
}				t_region;

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

// void			create_kd_tree(struct s_photon *photon_list, t_kd_tree **root, int photon_count);
// void			sort_kd_tree(t_kd_tree **root, int dim, t_kd_tree **sorted);
// void			free_kd_tree(t_kd_tree *root);
// void			photon_mapping_pass(t_raytracing_tools *r);
// void			radiance_estimation_pass(t_raytracing_tools *r, struct s_tile tile);
void			render_ppm(struct s_gtk_tools *g, t_tile tile);


typedef struct	s_photon
{
	t_vec3		pos;
	t_vec3		dir;
	t_color		col;
	t_vec3		n;
	int			type; //0: direct 1: indirect 2: caustic
}				t_photon;

typedef struct	s_selected_photon
{
	t_kd_tree	*photon;
	float		dist2;
}				t_selected_photon;

#endif