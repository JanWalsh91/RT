/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:55:31 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:52:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copies the unsigned char string src to dst, including the null-terminating
** character.
** src and dst should not overlap, as behavior is undefined.
*/

#include "libft.h"

unsigned char	*ft_ustrcpy(unsigned char *dst, const unsigned char *src)
{
	int				i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
	return (dst);
}
