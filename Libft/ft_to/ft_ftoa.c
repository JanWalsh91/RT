/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:30:21 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/26 11:55:08 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** UNFINISHED
** work in progress...
*/

char	*ft_ftoa(float n)
{
	char	*str;
	float	nb;
	int		count;
	int		i;
	char	*integral;

	integral = ft_itoa((int)n);
	n < 0 ? n = -n : 0;
	nb = n - (int)n;
	count = 1;
	while (n && ++count)
	{
		n = (n * 10) - (float)(int)(n * 10);
	}
	if (!(str = ft_strnew(count)))
		return (NULL);
	i = 1;
	i != count ? str[0] = '.' : 0;
	while (i != count)
		str[i++] = (int)(nb *= 10) + '0';
	return (ft_strjoinfree(integral, str, 'b'));
}
