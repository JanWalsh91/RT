/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrncpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 12:11:44 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:55:26 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Same as ft_strncpy, but with unsigned char strings.
** Copies at most len characters from unsigned char string src into dst.
** If src is less than len characters long, the remainder of dst is filled
** with \0. Otherwise, dst is not terminated.
*/

#include "libft.h"

unsigned char	*ft_ustrncpy(unsigned char *dst, const unsigned char *src,
		size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] && (i < len))
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
		dst[i++] = '\0';
	return (dst);
}
