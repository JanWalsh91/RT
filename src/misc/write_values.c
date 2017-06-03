/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 16:36:49 by tgros             #+#    #+#             */
/*   Updated: 2017/06/03 16:37:06 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"

void	write_vector(int fd, t_vec3 vec)
{
	write_float(fd, vec.x);
	write(fd, ", ", 2);
	write_float(fd, vec.y);
	write(fd, ", ", 2);
	write_float(fd, vec.z);
}

void	write_float(int fd, float d)
{
	char	*tmp;
	float	tmp2;
	int		i;

	if (d < 0.0)
	{
		write(fd, "-", 1);
		d = -d;
	}
	tmp = ft_itoa(d);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
	write(fd, ".", 1);
	i = -1;
	tmp2 = d - (float)(int)d;
	while (++i < SAVE_FLOAT_PRECISION)
	{
		tmp2 *= 10.0;
		tmp = ft_itoa((int)tmp2);
		write(fd, tmp, 1);
		free(tmp);
		tmp2 -= (float)(int)tmp2;
	}
}

void	write_int(int fd, int i)
{
	char *tmp;

	tmp = ft_itoa(i);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}
