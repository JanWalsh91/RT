/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_ray.cu                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:05:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/03 16:34:43 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

/*
** Initializes a camera ray.
*/

__device__
t_ray	init_camera_ray(t_pt2 i, t_scene *scene)
{
	t_ray		cam_ray;
	t_camera	*cam;
	t_vec3		pix;

	cam = &scene->cameras[0];
	pix.x = (2 * (i.x + 0.5) / (double)scene->res.x - 1) *
			scene->image_aspect_ratio * cam->scale;
	pix.y = (1 - 2 * (i.y + 0.5) / (double)scene->res.y) * cam->scale;
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
