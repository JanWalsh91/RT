/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrjoinfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:37:21 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/16 12:37:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Like ft_strjoinfree, but with unsigned chars to save wide chars
** in unsigned char strings.
** Concatenates s1 and s2 in a new string which was allocated enough memory
** with malloc. Returns a pointer to that new string.
** Frees s1 if c = l, s2 if c = r, and both if c = b or neither is c equals
** anything else.
*/

#include "libft.h"

unsigned char	*ft_ustrjoinfree(unsigned char const *s1,
		unsigned char const *s2, char c)
{
	unsigned char	*newstr;

	newstr = ft_ustrjoin(s1, s2);
	if (c == 'l' || c == 'b')
		s1 ? free((unsigned char *)s1) : 0;
	if (c == 'r' || c == 'b')
		s2 ? free((unsigned char *)s2) : 0;
	return (newstr);
}
