/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrsjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:47:28 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/07 14:58:20 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Joins n wide character strings together.
*/

wchar_t	*ft_wstrsjoin(size_t n, ...)
{
	size_t	i;
	size_t	length;
	va_list	ap;
	va_list	cp;
	wchar_t	*result;

	va_start(ap, n);
	va_copy(cp, ap);
	i = -1;
	length = 0;
	while (++i < n)
		length += ft_wstrlen(va_arg(cp, wchar_t *));
	if (!(result = ft_wstrnew(length)))
		return (NULL);
	i = -1;
	while (++i < n)
		result = ft_wstrappend(result, va_arg(ap, wchar_t *), length);
	va_end(ap);
	va_end(cp);
	return (result);
}
