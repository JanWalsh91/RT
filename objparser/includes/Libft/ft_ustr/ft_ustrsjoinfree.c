/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrsjoinfree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 11:48:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 19:04:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Joins n unsigned char strings together. Frees the stirngs.
** Returns the new string.
*/

unsigned char	*ft_ustrsjoinfree(size_t n, ...)
{
	size_t			i;
	size_t			length;
	va_list			ap;
	va_list			cp;
	unsigned char	*result;

	va_start(ap, n);
	va_copy(cp, ap);
	i = -1;
	length = 0;
	while (++i < n)
		length += ft_strlen((char *)va_arg(cp, unsigned char *));
	if (!(result = ft_ustrnew(length)))
		return (NULL);
	i = -1;
	while (++i < n)
		result = ft_ustrappendfree(result, va_arg(ap, unsigned char *),
				length);
	va_end(ap);
	va_end(cp);
	return (result);
}
