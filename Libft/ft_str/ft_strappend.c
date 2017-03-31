/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:16:59 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/07 15:25:55 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Appends string src to string dst until dst reaches size number of chars,
** excluding the \0.
** Null-terminates the result.
*/

#include "libft.h"

char	*ft_strappend(char *dst, char *src, size_t size)
{
	size_t	length;

	length = (dst && *dst) ? ft_strlen(dst) : 0;
	if (length >= size)
		return (dst);
	while (length <= size && src && dst && *src)
		dst[length++] = *(src++);
	dst[length] = '\0';
	return (dst);
}
