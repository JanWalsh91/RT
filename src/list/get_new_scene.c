/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/02 15:31:55 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Creates a new scene for parsing.
*/

static void		set_scene_non_values(t_scene *new_scene);

t_scene			*get_new_scene(t_parse_tools *t)
{
	t_scene		*new_scene;
	static int	i = 0;

	new_scene = NULL;
	if (!(new_scene = (t_scene *)ft_memalloc(sizeof(t_scene))))
		ft_errno_exit();
	set_scene_non_values(new_scene);
	new_scene->name = (!t->input->value || !*t->input->value) ?
		ft_strjoinfree("Scene ", ft_itoa(++i), 'r') :
		ft_strdup(t->input->value);
	return (new_scene);
}

/*
** Set default values for parsing a file (see sig_open_scene for default
** values for a new scene)
*/

static void		set_scene_non_values(t_scene *new_scene)
{
	new_scene->res.x = -1;
	new_scene->res.y = -1;
	new_scene->ray_depth = -1;
	new_scene->objects = NULL;
	new_scene->cameras = NULL;
	new_scene->lights = NULL;
	new_scene->background_color = v_new(NAN, NAN, NAN);
	new_scene->ambient_light_color = v_new(NAN, NAN, NAN);
	new_scene->ka = NAN;
	new_scene->image_aspect_ratio = NAN;
	new_scene->name = NULL;
	new_scene->is_diffuse = true;
	new_scene->is_shadow = true;
	new_scene->is_specular = true;
	new_scene->is_fresnel = true;
	new_scene->is_photon_mapping = false; 
	new_scene->photon_kd_tree = NULL;
	// new_scene->selected_photons = NULL;
	new_scene->photon_count_per_pass = 500;
	new_scene->photon_count = 50000;
	new_scene->is_aa = 1;
}
