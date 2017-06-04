/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:05:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/04 14:42:53 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Initializes a camera ray.
*/

__device__
t_ray	init_camera_ray(t_raytracing_tools *r, t_dpt2 current_pos_pix)
{
	t_ray		cam_ray;
	t_camera	*cam;
	t_vec3		pix;

	cam = &r->scene->cameras[0];
	cam_ray.type = R_PRIMARY;
	cam_ray.origin = cam->pos;
	pix.x = (2 * (r->pix.x + current_pos_pix.x) / (float)r->scene->res.x - 1) *
			r->scene->image_aspect_ratio * cam->scale;
	pix.y = (1 - 2 * (r->pix.y + current_pos_pix.y) / (float)r->scene->res.y) *
			cam->scale;
	pix.z = CAM_IMG_PANE_DIST;
	cam_ray.dir = v_norm(pix);
	cam_ray.dir = v_norm(m_v_mult(cam_ray.dir, &cam->ctw));
	cam_ray.t = INFINITY;
	cam_ray.hit = v_new(NAN, NAN, NAN);
	cam_ray.hit_obj = 0;
	cam_ray.hit_type = T_COUNT;
	cam_ray.n_dir = 1;
	cam_ray.nhit = v_new(NAN, NAN, NAN);
	cam_ray.col = c_new(0, 0, 0);
	cam_ray.ior = r->scene->cameras->ior;
	cam_ray.depth = r->scene->ray_depth;
	r->ior_list[0] = r->scene->cameras->ior;
	return (cam_ray);
}
