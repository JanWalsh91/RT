/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 18:39:37 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:51:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Puts the lowercase chars in a char string to uppercase.
*/

void	ft_strtoupper(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
		ft_islower(s[i]) ? s[i] = ft_toupper(s[i]) : 0;
}
