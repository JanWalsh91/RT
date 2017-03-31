/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoinfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:52:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:51:03 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Joins n strings together. Frees the strings. Returns the new string.
*/

char	*ft_strsjoinfree(size_t n, ...)
{
	size_t	i;
	size_t	length;
	va_list	ap;
	va_list	cp;
	char	*result;

	va_start(ap, n);
	va_copy(cp, ap);
	i = -1;
	length = 0;
	while (++i < n)
		length += ft_strlen(va_arg(cp, char *));
	if (!(result = ft_strnew(length)))
		return (NULL);
	i = -1;
	while (++i < n)
		result = ft_strappendfree(result, va_arg(ap, char *), length);
	return (result);
}
