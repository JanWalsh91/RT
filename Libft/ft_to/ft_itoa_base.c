/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:59:29 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 14:42:35 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Converts long integer value into an array in base base.
*/

char	*ft_itoa_base(long value, int base)
{
	char	*result;
	int		i;
	int		sign;
	long	n;

	if (base < 2)
		return (0);
	if (value == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	n = (value < 0) ? -value : value;
	sign = (value < 0) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		i++;
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	result[i] = '\0';
	n = (value < 0) ? -value : value;
	while (i-- + sign)
	{
		result[i] = (n % base) < 10 ? n % base + '0' : n % base + 'A' - 10;
		n /= base;
	}
	(i == 0) ? result[i] = '-' : 0;
	return (result);
}
