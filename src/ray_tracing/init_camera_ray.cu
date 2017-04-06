/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_ray.cu                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:05:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Initializes a camera ray.
*/

__device__
t_ray	init_camera_ray(t_raytracing_tools *r)
{
	t_ray		cam_ray;
	t_camera	*cam;
	t_vec3		pix;

	cam = &r->scenes->cameras[0];
	pix.x = (2 * (r->pix.x + 0.5) / (double)r->scenes->res.x - 1) *
			r->scenes->image_aspect_ratio * cam->scale;
	pix.y = (1 - 2 * (r->pix.y + 0.5) / (double)r->scenes->res.y) * cam->scale;
	pix.z = CAM_IMG_PANE_DIST;
	cam_ray.dir = v_norm(pix);
	cam_ray.origin = cam->pos;
	cam_ray.dir = m_v_mult(cam_ray.dir, &cam->ctw);
	cam_ray.dir = v_norm(cam_ray.dir);
	cam_ray.type = R_PRIMARY;
	cam_ray.n_dir = 1;
	// printf("[%d]: cam ray dir: [%f, %f %f]\n", i.x + i.y * scene->res.x, cam_ray.dir.x, cam_ray.dir.y, cam_ray.dir.z);
	return (cam_ray);
}
