/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:03:49 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/06 15:05:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Counts and returns the number of occurrences of character c in string s.
*/

int	ft_charcount(char *s, char c)
{
	int	count;

	count = 0;
	while (s && *s)
	{
		if (*s == c)
			++count;
		++s;
	}
	return (count);
}
