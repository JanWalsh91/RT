/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 14:04:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:54:51 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Computes and returns the length of unsigned char string s.
** Excludes the null terminating character.
** Unlike the standard library's strlen, it returns 0 if thr string is NULL;
*/

#include "libft.h"

size_t	ft_ustrlen(const unsigned char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		++i;
	return (i);
}
