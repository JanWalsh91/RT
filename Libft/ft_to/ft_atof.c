/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 11:17:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 11:55:17 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Converts an array into a float. To be improvd.
*/

float	ft_atof(const char *str)
{
	float	result;
	int		i;
	float	divider;
	float	sign;

	if (!str)
		return (0);
	sign = (str[0] == '-') ? -1 : 1;
	result = ft_atol(str);
	i = 0;
	while (str[i] == 9 || str[i] == 10 || str[i] == 11 ||
		str[i] == 12 || str[i] == 13 || str[i] == 32)
		++i;
	(str[i] == '+' || str[i] == '-') ? ++i : 0;
	while (ft_isdigit(str[i]))
		++i;
	if (str[i] != '.')
		return (result);
	divider = 10;
	while (ft_isdigit(str[++i]))
	{
		result += sign * (str[i] - '0') / divider;
		divider *= 10;
	}
	return (result);
}
