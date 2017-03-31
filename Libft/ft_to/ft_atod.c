/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 11:17:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 14:58:02 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Converts an array into a double. To be improvd.
*/

double	ft_atod(const char *str)
{
	double	result;
	int		i;
	double	divider;
	double	sign;

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
