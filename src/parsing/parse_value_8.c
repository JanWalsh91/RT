/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:18:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/20 14:59:23 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Contains functions for parsing each value based on token.
*/

char	*read_texture_file(t_parse_tools *t)
{
	rt_file_warning(t, "Read texture file: feature not yet available.");
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
