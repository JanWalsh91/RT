/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_flares.cu                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 10:18:02 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 16:29:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "../../inc/cuda_call.h"

__device__
static t_pt2	get_pane_coords(t_ray *ray, t_camera *cam, t_scene *scene);
__global__
void			init_light_flares(t_scene *scene, t_light_flare_tools *tools);
__device__
static void		init_ray_and_rt_tools(t_raytracing_tools *t, t_ray *ray,
				t_scene *scene, t_light_flare_tools *tools);
__device__
static bool		is_light_blocked(t_raytracing_tools *r, t_ray *ray,
				t_scene *scene, t_light_flare_tools *tools);

void			init_light_flares_wrapper(int light_count,
				t_raytracing_tools *r, t_light_flare_tools *tools)
{
	init_light_flares<<<light_count, 1>>>(r->d_scene, tools);
	cuda_check_kernel_errors();
}

__global__
void			init_light_flares(t_scene *scene, t_light_flare_tools *tools)
{
	t_raytracing_tools	r;
	t_ray				ray;

	r.idx = blockIdx.x;
	init_ray_and_rt_tools(&r, &ray, scene, tools);
	tools[r.idx].is_valid = 1;
	if (!get_view_pane_intersection(&ray, scene->cameras))
	{
		tools[r.idx].is_valid = 0;
		return ;
	}
	tools[r.idx].pos = get_pane_coords(&ray, scene->cameras, scene);
	if (tools[r.idx].pos.x < 0 || tools[r.idx].pos.x >= scene->res.x ||
		tools[r.idx].pos.y < 0 || tools[r.idx].pos.y >= scene->res.y)
	{
		tools[r.idx].is_valid = 0;
		return ;
	}
	tools[r.idx].dist = v_length(v_sub(scene->lights[r.idx].pos, ray.origin));
	tools[r.idx].max_rad = powf(scene->lights[r.idx].intensity, 3) /
		tools[r.idx].dist;
	tools[r.idx].light = &scene->lights[r.idx];
	if (is_light_blocked(&r, &ray, scene, tools))
		tools[r.idx].is_valid = 0;
}

__device__
static void		init_ray_and_rt_tools(t_raytracing_tools *r, t_ray *ray,
				t_scene *scene, t_light_flare_tools *tools)
{
	r->scene = scene;
	ray->t = INFINITY;
	ray->type = R_PRIMARY;
	r->t = INFINITY;
	ray->origin = scene->cameras->pos;
	ray->dir = v_norm(v_sub(scene->lights[r->idx].pos, scene->cameras->pos));
}

__device__
static bool		is_light_blocked(t_raytracing_tools *r, t_ray *ray,
				t_scene *scene, t_light_flare_tools *tools)
{
	int y;

	if (tools[r->idx].pos.x >= 0 && tools[r->idx].pos.y >= 0 &&
	tools[r->idx].pos.x < scene->res.x && tools[r->idx].pos.y < scene->res.y)
	{
		y = -1;
		while (scene->objects && scene->objects[++y].type != T_INVALID_TOKEN)
		{
			if (intersects(r, ray, y) &&
				ray->t < tools[r->idx].dist && ray->t > 0.0)
				return (true);
		}
	}
	else
		return (true);
	return (false);
}

__device__
static t_pt2	get_pane_coords(t_ray *ray, t_camera *cam, t_scene *scene)
{
	t_pt2	coord;
	t_vec3	ortho_x;
	t_vec3	ortho_y;
	t_vec3	proj_dir;

	proj_dir = v_sub(ray->dir, v_scale(cam->dir, -1));
	ortho_x = v_cross(v_new(0, 1, 0), v_scale(cam->dir, -1));
	ortho_y = v_cross(v_scale(cam->dir, -1), ortho_x);
	ortho_x = v_norm(ortho_x);
	ortho_y = v_norm(ortho_y);
	ray->hit = v_add(ray->origin, v_scale(ray->dir, ray->t));
	coord.x = (int)(v_dot(v_scale(ortho_x, -1), proj_dir) * scene->res.x * 0.5 /
		scene->image_aspect_ratio / cam->scale + scene->res.x * 0.5);
	coord.y = (int)(v_dot(v_scale(ortho_y, -1), proj_dir) * scene->res.y * 0.5 /
		cam->scale + scene->res.y / 2);
	return (coord);
}
