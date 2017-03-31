/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 15:56:30 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:56:34 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates memory for and returns a wide character string of size size,
** with all characters initilized at \0.
** Returns NULL if allocation fails.
*/

#include "libft.h"

wchar_t	*ft_wstrnew(size_t size)
{
	wchar_t	*str;

	if (!(str = ft_memalloc(size + 1)))
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
