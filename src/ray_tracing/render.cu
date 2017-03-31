/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:59:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 16:50:45 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

static void	display_percentage(int num);

/*
** Updates a camera's pixel_map (color of image pixels).
*/

__device__
void		render(t_raytracing_tools *r)
{
	t_ray	cam_ray;

	r->pix.y = -1;
	while (++r->pix.y < r->scenes->res.y)
	{
		r->pix.x = -1;
		display_percentage((int)((double)r->pix.y /
			r->scenes->res.y * (100)) + 1);
		while (++r->pix.x < r->scenes->res.x)
		{
			cam_ray = init_camera_ray(r->pix, r->scenes);
			r->scenes->cameras->pixel_map[r->pix.y][r->pix.x] =
				cast_primary_ray(r, &cam_ray);
		}
	}
}

__device__
static void	display_percentage(int num)
{
	ft_printf("Loading...%i%%\r", num);
}
