/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:19:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 11:40:59 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

static void	free_split_value(char **split_value);

/*
** Parses a vector.
*/

t_vec3		parse_vector(char *value)
{
	t_vec3	new_vec;
	char	**split_value;

	new_vec = v_new(NAN, NAN, NAN);
	if (ft_charcount(value, ',') != 2)
		return (new_vec);
	split_value = split_trim(value, ',');
	new_vec.x = parse_float(split_value[0]);
	new_vec.y = parse_float(split_value[1]);
	new_vec.z = parse_float(split_value[2]);
	free_split_value(split_value);
	if (isnan(new_vec.x) || isnan(new_vec.y) || isnan(new_vec.z))
		return (v_new(NAN, NAN, NAN));
	return (new_vec);
}

static void	free_split_value(char **split_value)
{
	if (split_value && split_value[0])
		free(split_value[0]);
	if (split_value && split_value[1])
		free(split_value[1]);
	if (split_value && split_value[2])
		free(split_value[2]);
	if (split_value)
		free(split_value);
}
