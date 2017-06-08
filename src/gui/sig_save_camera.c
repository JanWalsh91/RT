/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_save_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 16:38:18 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 12:25:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

static void	save_camera2(int fd, t_camera *cam);

void		save_camera(int fd, t_camera *cam)
{
	write(fd, "\tcamera: ", 9);
	write(fd, cam->name, ft_strlen(cam->name));
	write(fd, "\n\t{\n", 4);
	write(fd, "\t\tposition: ", 12);
	write_vector(fd, cam->pos);
	write(fd, "\n", 1);
	write(fd, "\t\tdirection: ", 13);
	write_vector(fd, cam->dir);
	write(fd, "\n", 1);
	if (!v_isnan(cam->look_at) && (cam->look_at.x != 0 &&
		cam->look_at.y != 0 && cam->look_at.z != 0))
	{
		write(fd, "\t\tlook at: ", 11);
		write_vector(fd, cam->look_at);
		write(fd, "\n", 1);
	}
	save_camera2(fd, cam);
}

static void	save_camera2(int fd, t_camera *cam)
{
	if (cam->filter != F_NONE)
		write(fd, "\t\tfilter: ", 10);
	if (cam->filter == F_BW)
		write(fd, "black and white\n", 16);
	else if (cam->filter == F_SEPIA)
		write(fd, "sepia\n", 6);
	else if (cam->filter == F_DEUTAN)
		write(fd, "deutan\n", 7);
	write(fd, "\t\tfov: ", 7);
	write_int(fd, cam->fov);
	write(fd, "\n", 1);
	write(fd, "\t\tior: ", 7);
	write_float(fd, cam->ior);
	write(fd, "\n\t}\n", 4);
}
