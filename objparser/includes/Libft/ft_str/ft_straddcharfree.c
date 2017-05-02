/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddcharfree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 11:07:36 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/03 11:16:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** UNTESTED
** Allocated memory for a new string to which a char was added.
** Frees string s.
** Returns that string.
*/

#include "libft.h"

char	*ft_straddcharfree(char const *s, char c)
{
	char	*newstr;
	size_t	length;
	size_t	i;

	if (!c || !ft_isprint(c))
		return ((char *)s);
	length = (s) ? ft_strlen((char *)s) + 2 : 2;
	if (!(newstr = ft_memalloc(sizeof(char) * length)))
		return (NULL);
	i = 0;
	while (i < length && s && s[i])
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	free((void *)s);
	return (newstr);
}
