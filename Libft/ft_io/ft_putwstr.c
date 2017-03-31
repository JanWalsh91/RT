/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:01:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/06 15:00:38 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Writes the wide character string s to the standard output.
** Returns 0 if an invalid wide character is detected.
*/

#include "libft.h"

int		ft_putwstr(wchar_t const *s)
{
	while (s && *s)
		if (!(ft_putwchar(*s)))
			return (0);
	return (1);
}
