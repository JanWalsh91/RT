/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:18:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 16:50:45 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

/*
** Contains functions for parsing each value based on token.
*/

void	read_texture_file(t_parse_tools *t)
{
	rt_file_warning(t, "Read texture file: feature not yet available.");
}

void	read_material_file(t_parse_tools *t)
{
	rt_file_warning(t, "Read material file: feature not yet available.");
}

void	hashtag(t_parse_tools *t)
{
	rt_file_warning(t, "Ingore line.");
}

void	invalid_token(t_parse_tools *t)
{
	rt_file_error_exit(t, "Invalid token.");
}
