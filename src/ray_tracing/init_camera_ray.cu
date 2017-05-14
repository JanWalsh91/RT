/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_ray.cu                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:05:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/13 13:58:28 by tgros            ###   ########.fr       */
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
	pix.x = (2 * (r->pix.x + current_pos_pix.x) / (float)r->scene->res.x - 1) *
			r->scene->image_aspect_ratio * cam->scale;
	pix.y = (1 - 2 * (r->pix.y + current_pos_pix.y) / (float)r->scene->res.y) * cam->scale;
	pix.z = CAM_IMG_PANE_DIST;
	cam_ray.dir = v_norm(pix);
	cam_ray.origin = cam->pos;
	cam_ray.dir = m_v_mult(cam_ray.dir, &cam->ctw);
	cam_ray.dir = v_norm(cam_ray.dir);
	cam_ray.type = R_PRIMARY;
	cam_ray.n_dir = 1;
	cam_ray.depth = r->scene->ray_depth;
	//set first ior to camera's ior
	cam_ray.ior = r->scene->cameras->ior;
	r->ior_list[0] = r->scene->cameras->ior;
	return (cam_ray);
}
