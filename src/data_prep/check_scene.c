/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 10:39:37 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/22 10:27:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

static void	check_cameras(t_scene *scene, t_camera *cameras);
static void	check_lights(t_scene *scene, t_light *lights);
static void	get_cam_direction(t_scene *scene, t_camera *cam);
static void	get_light_direction(t_scene *scene, t_light *light);

/*
** Checks the validity of the scene, objects, lights, camera and their attributes.
** Sets default values if necessary.
*/

char		*check_scene(t_scene *scene)
{
	if (!scene)
		return ("No scene provided");
	(scene->res.x == -1) ? set_default_resolution(scene) : 0;
	isnan(scene->ka) ? set_default_ka(scene) : 0;
	v_isnan(scene->ambient_light_color) ?
		set_default_ambient_light_color(scene) : 0;
	scene->image_aspect_ratio = (float)scene->res.x / (float)scene->res.y;
	(scene->ray_depth == -1) ? set_default_ray_depth(scene) : 0;
	if (scene->cameras)
		check_cameras(scene, scene->cameras);
	if (scene->lights)
		check_lights(scene, scene->lights);
	if (scene->objects)
		check_objects(scene, scene->objects);
	return (NULL);
}

static void	check_cameras(t_scene *scene, t_camera *cameras)
{
	t_camera	*c_ptr;

	c_ptr = cameras;
	while (c_ptr)
	{
		v_isnan(c_ptr->pos) ? set_default_pos(scene,
			T_CAMERA, c_ptr, &c_ptr->pos) : 0;
		isnan(c_ptr->fov) ? set_default_fov(scene,
			T_CAMERA, c_ptr, &c_ptr->fov) : 0;
		isnan(c_ptr->ior) ? set_default_ior(scene, T_CAMERA, c_ptr, &c_ptr->ior) : 0;
		get_cam_direction(scene, c_ptr);
		init_camera(scene, c_ptr);
		c_ptr = c_ptr->next;
	}
}

static void	check_lights(t_scene *scene, t_light *lights)
{
	t_light		*l_ptr;

	l_ptr = lights;
	while (l_ptr)
	{
		(v_isnan(l_ptr->pos)) ? get_light_direction(scene, l_ptr) : 0;
		if (!v_isnan(l_ptr->dir) && !v_isnan(l_ptr->pos))
		{
			data_warning(scene, T_LIGHT, l_ptr,
				"Lights can either have position or direction. \
Setting to spherical/positional lighting.");
			l_ptr->dir = v_new(NAN, NAN, NAN);
		}
		v_isnan(l_ptr->dir) && v_isnan(l_ptr->pos) ?
			set_default_pos(scene, T_LIGHT, l_ptr, &l_ptr->pos) : 0;
		v_isnan(l_ptr->col) ? set_default_col(scene,
			T_LIGHT, l_ptr, &l_ptr->col) : 0;
		isnan(l_ptr->intensity) ? set_default_intensity(scene,
			T_LIGHT, l_ptr, &l_ptr->intensity) : 0;
		l_ptr = l_ptr->next;
	}
}

static void	get_cam_direction(t_scene *scene, t_camera *cam)
{
	t_matrix	m;

	if (!v_isnan(cam->look_at) && !v_isnan(cam->pos))
		cam->dir = v_sub(cam->look_at, cam->pos);
	if (v_isnan(cam->dir) || (!cam->dir.x && !cam->dir.y && !cam->dir.z))
		set_default_cam_dir(scene, T_CAMERA, cam, &cam->dir);
	cam->dir = v_norm(cam->dir);
}

static void	get_light_direction(t_scene *scene, t_light *light)
{
	t_matrix	m;

	if (!v_isnan(light->look_at) && !v_isnan(light->pos))
		light->dir = v_sub(light->look_at, light->pos);
	if (v_isnan(light->dir) ||
		(!light->dir.x && !light->dir.y && !light->dir.z))
		set_default_light_dir(scene, T_LIGHT, light, &light->dir);
	light->dir = v_norm(light->dir);
}
