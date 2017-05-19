/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_checkerboard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 17:49:17 by tgros             #+#    #+#             */
/*   Updated: 2017/05/16 16:05:30 by tgros            ###   ########.fr       */
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
		return (NULL);
	i.y = -1;
	while (++i.y < res->y)
	{
		i.x = -1;
		while (++i.x < res->x)
		{
			// Number of tile on the pixmap : res->x / res.z
			// 
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
