/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:19:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/01 15:22:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Compares string s1 with all the strings in the NULL-terminated array of
** strings. Returns 0 if a match is found, of returns the result of strcmp
** with the different string.
*/

#include "libft.h"

int	ft_strscmp(const char *s1, const char **s)
{
	int	i;
	int	ret;

	i = -1;
	while (s[++i])
	{
		if ((ret = ft_strcmp(s1, s[i])))
			return (ret);
	}
	return (0);
}
