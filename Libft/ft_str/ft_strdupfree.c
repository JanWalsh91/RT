/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:24:49 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/14 18:32:05 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Frees a char pointer and creates a new string from src with ft_strdup
** and assignes dst to the result.
*/

char	*ft_strdupfree(char *dst, char *src)
{
	dst ? free(dst) : 0;
	dst = ft_strdup(src);
	return (dst);
}
