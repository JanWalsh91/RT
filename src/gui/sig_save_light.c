/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_save_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 16:38:20 by tgros             #+#    #+#             */
/*   Updated: 2017/06/03 16:38:36 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	save_light(int fd, t_light *light)
{
	write(fd, "\tlight: ", 8);
	write(fd, light->name, ft_strlen(light->name));
	write(fd, "\n\t{\n", 4);
	if (v_isnan(light->dir))
	{
		write(fd, "\t\tposition: ", 12);
		write_vector(fd, light->pos);
		write(fd, "\n", 1);
	}
	else
	{
		write(fd, "\t\tdirection: ", 13);
		write_vector(fd, light->dir);
		write(fd, "\n", 1);
	}
	write(fd, "\t\tcolor: ", 8);
	write_vector(fd, (t_vec3)light->col);
	write(fd, "\n", 1);
	write(fd, "\t\tintensity: ", 13);
	write_int(fd, light->intensity);
	write(fd, "\n", 1);
	write(fd, "\t\tkflare: ", 10);
	write_float(fd, light->kflare);
	write(fd, "\n\t}\n", 4);
}
