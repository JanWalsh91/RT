/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:20:32 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Parses a float.
*/

float	parse_float(char *value)
{
	float	new_d;
	int		i;

	new_d = NAN;
	if (ft_charcount(value, ',') ||
		!((ft_charcount(value, '.') == 1) ||
		ft_charcount(value, '.') == 0))
		return (new_d);
	i = -1;
	while (value && value[++i])
		if (!((ft_isdigit(value[i]) || value[i] == '-' ||
			value[i] == '+') || value[i] == '.'))
			return (new_d);
	new_d = ft_atof(value);
	return (new_d);
}
