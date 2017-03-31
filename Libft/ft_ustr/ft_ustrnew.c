/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:17:40 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/16 12:49:16 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates memory for and returns a unsigned char string of size size,
** with all characters initilized at \0.
** Returns NULL if allocation fails.
*/

#include "libft.h"

unsigned char	*ft_ustrnew(size_t size)
{
	unsigned char	*str;

	if (!(str = ft_memalloc(size + 1)))
		return (NULL);
	return (str);
}
