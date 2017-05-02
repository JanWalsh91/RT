/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrtostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 17:02:51 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/06 17:11:26 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts wide character string  to a character string
** (to be used by write (2)).
** Returns 0 if an invalid character is detected
*/

#include "libft.h"

unsigned char			*ft_wstrtostr(unsigned char *s)
{
	unsigned char	*result;
	unsigned char	*tmp;
	int				i;

	i = -1;
	while (s[++i])
	{
		if (!(tmp = ft_wctostr(s[i])))
			return (0);
		result = ft_ustrjoinfree(result, tmp, 'b');
	}
	return (result);
}
