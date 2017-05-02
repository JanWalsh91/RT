/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 14:51:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:41:34 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Writes the wide char string s to the file descriptor fd.
** Returns 0 if an invalid wide char is detected.
*/

#include "libft.h"

int		ft_putwstr_fd(wchar_t const *s, int fd)
{
	while (s && *s)
		if (!(ft_putwchar_fd(*s, fd)))
			return (0);
	return (1);
}
