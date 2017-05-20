/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_texture_loaded.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 17:14:56 by tgros             #+#    #+#             */
/*   Updated: 2017/05/20 09:54:55 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

// A deplacer dans sig_generate_texture ? 

t_object		*is_texture_loaded(t_object *head, t_object	*to_cmp, char *texture_name, t_vec3 dim)
{
	t_object	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("Object: [%s]\n", tmp->name);
		printf("[%s] vs [%s]\n", tmp->texture_name, texture_name);
		if (tmp != to_cmp)
		{
			if (tmp->texture_name && ft_strcmp(tmp->texture_name, texture_name) == 0)
			{
				if (ft_strcmp(tmp->texture_name, "Perlin") == 0 ||
					ft_strcmp(tmp->texture_name, "Checkerboard") == 0 ||
					ft_strcmp(tmp->texture_name, "Noise") == 0)
				{
					if (tmp->texture_dim.x == dim.x && tmp->texture_dim.y == dim.y && tmp->texture_dim.z == dim.z)
						return (tmp);
				}
				else
					return (tmp);
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}