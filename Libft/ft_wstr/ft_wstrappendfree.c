/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrappendfree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:10:35 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/10 14:23:48 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Appends wide character string src to string dst until dst reaches size
** number of chars, excluding the \0.
** Null-terminates the result.
** Frees each string.
*/

#include "libft.h"

wchar_t	*ft_wstrappendfree(wchar_t *dst, wchar_t *src, size_t size)
{
	size_t	length;
	int		i;

	length = (dst && *dst) ? ft_wstrlen(dst) : 0;
	if (length >= size)
		return (dst);
	i = 0;
	while (length <= size && dst && src && src[i])
		dst[length++] = src[i++];
	dst[length] = '\0';
	src ? free(src) : 0;
	return (dst);
}
