/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:18:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/08 13:26:12 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../../Libft/inc/libft.h"

/*
** Contains functions for parsing each value based on token.
*/

char	*read_texture_file(t_parse_tools *t)
{
	t_color			*texture;
	char			**res;
	int				i;
	t_vec3			resolution;

	res = ft_strsplit(t->input->value, ' ');
	ft_strtoupper(res[0]); // TODO: protect
	if (ft_strcmp(res[0], "PERLIN") == 0)
	{
		if (v_isnan(resolution = parse_vector(t->input->value + ft_strlen(res[0]))))
			return ("Position formatting error.");
		t->current_object->texture_name = ft_strdup("Perlin");
		t->current_object->texture = generate_perlin_noise(&resolution);
		t->current_object->texture_dim.x = (int)resolution.x;
		t->current_object->texture_dim.y = (int)resolution.y;
	}
	else
	{
		if (!(texture = read_bmp(t->input->value, &t->current_object->texture_dim)))
			return (strerror(errno));
		t->current_object->texture_name = ft_strdup(t->input->value); // free?
		t->current_object->texture = texture;
	}
	i = -1;
	while (res[++i])
		free(res[i]);
	free(res);
	return (NULL);
}

char	*read_material_file(t_parse_tools *t)
{
	rt_file_warning(t, "Read material file: feature not yet available.");
	return (NULL);
}

char	*hashtag(t_parse_tools *t)
{
	rt_file_warning(t, "Ingore line.");
	return (NULL);
}

char	*invalid_token(t_parse_tools *t)
{
	return ("Invalid token.");
}
