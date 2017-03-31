/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 11:23:49 by tgros             #+#    #+#             */
/*   Updated: 2017/01/23 12:02:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Compare src and cmp. If the difference between src and cmp is less than
**	percent, the function returns 1. Otherwise, it returns 0.
**	@percent: float between 0 and 1
*/

int		ft_strcmp_percent(char *src, char *cmp, float percent)
{
	int	cmp_len;
	int	res;

	res = 0;
	if (!src || !cmp || percent < 0.0 || percent > 1.0)
		return (-1);
	cmp_len = ft_strlen(cmp);
	while (*src == *cmp && *cmp++ && *src++)
		res++;
	return (res >= (int)(percent * cmp_len));
}
