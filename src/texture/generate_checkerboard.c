/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_checkerboard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 17:49:17 by tgros             #+#    #+#             */
/*   Updated: 2017/06/09 10:22:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include <cuda_runtime.h>

t_color		*generate_checkerboard(t_vec3 *res)
{
	t_color		*map;
	t_pt2		i;
	t_pt2		tile;
	char		color;

	if (cudaMallocHost((void **)&map, (3 * res->x * res->y)) != 0)
		ft_error_exit("cudaMallocHost error");
	i.y = -1;
	while (++i.y < res->y)
	{
		i.x = -1;
		while (++i.x < res->x)
		{
			tile.x = i.x / res->z;
			tile.y = i.y / res->z;
			if ((tile.x + tile.y) % 2 == 0)
				color = 0;
			else
				color = 255;
			map[i.y * (int)res->x + i.x].r = color;
			map[i.y * (int)res->x + i.x].g = color;
			map[i.y * (int)res->x + i.x].b = color;
		}
	}
	return (map);
}
