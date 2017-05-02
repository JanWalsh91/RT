/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrdupfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:59:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:54:14 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Frees a unsigned char string and creates a new unsigned char string from src
** with ft_ustrdup, assigning dst to the result.
*/

unsigned char	*ft_ustrdupfree(unsigned char *dst, unsigned char *src)
{
	dst ? free(dst) : 0;
	dst = ft_ustrdup(src);
	return (dst);
}
