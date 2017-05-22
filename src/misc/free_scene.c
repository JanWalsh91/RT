/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 14:20:07 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/21 15:54:41 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

static void	free_cameras(t_camera *cams, t_pt2 res);
static void	free_lights(t_light *lights);
static void	free_objects(t_object *objs);
// static void	free_matrix(t_matrix *m);

/*
** Frees the t_scene linked list and all substructures.
*/

void		free_scene(t_scene *scene)
{
	free(scene->name);
	free_cameras(scene->cameras, scene->res);
	scene->cameras = NULL;
	free_lights(scene->lights);
	scene->lights = NULL;
	free_objects(scene->objects);
	scene->objects = NULL;
	scene = NULL;
}

static void	free_cameras(t_camera *cams, t_pt2 res)
{
	t_camera	*tmp;

	while (cams->prev)
		cams = cams->prev;
	while (cams)
	{
		tmp = cams;
		if (cams->name)
			free(cams->name);
		cams = cams->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	free_lights(t_light *lights)
{
	t_light	*tmp;

	while (lights)
	{
		tmp = lights;
		if (lights->name)
			free(lights->name);
		lights = lights->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	free_objects(t_object *objs)
{
	t_object	*tmp;

	while (objs)
	{
		tmp = objs;
		if (objs->name)
			free(objs->name);
		objs = objs->next;
		free(tmp);
		tmp = NULL;
	}
}
