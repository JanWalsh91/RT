/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:49:55 by tgros             #+#    #+#             */
/*   Updated: 2017/03/31 14:52:16 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts the initial portion of the string pointed to by str to long int
** representation. Ignores ht, nl, vt, np (new page), cr (carriage return)
** and space.
*/

#include "libft.h"
#include <limits.h>

long long	ft_atol(const char *str)
{
	unsigned int	i;
	long long		result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	if (ft_strcmp("-9223372036854775808", str) == 0)
		return (LONG_MIN);
	while (str[i] == 9 || str[i] == 10 ||
			str[i] == 11 || str[i] == 12 ||
			str[i] == 13 || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return ((long long)(sign * result));
}
