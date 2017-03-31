/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrncat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:53:52 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/06 16:56:49 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Same at ft_strncat, but with unsigned chars.
** Appends a copy of the null-terminated string s2 to the end of the
** null-terminated string s1, then adds a terminating'\0'.
** Will not append more than n characters from s2, and then adds '\0'.
** s1 and s2 should not overlap, as behavior is undefined.
*/

#include "libft.h"

unsigned char	*ft_ustrncat(unsigned char *s1, unsigned char *s2, int nb)
{
	int	i;
	int	j;

	i = ft_strlen((char *)s1);
	j = 0;
	while (s2[j] && j < nb)
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}
