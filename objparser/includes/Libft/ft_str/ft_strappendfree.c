/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappendfree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:07:09 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 14:43:27 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Appends string src to string dst until dst reaches size number of chars,
** excluding the \0.
** Null-terminates the result.
** Frees the src.
*/

#include "libft.h"

char	*ft_strappendfree(char *dst, char *src, size_t size)
{
	size_t	length;
	int		i;

	length = (dst && *dst) ? ft_strlen(dst) : 0;
	if (length >= size)
		return (dst);
	i = 0;
	while (length <= size && dst && src && src[i])
		dst[length++] = src[i++];
	dst[length] = '\0';
	src ? free(src) : 0;
	return (dst);
}
