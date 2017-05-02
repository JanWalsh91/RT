/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_until_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 12:42:24 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 18:02:25 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Parses the format string until a percentage character is found or the end of
** the string is reached.
** Copies the string in a temporary string which is joined to the result in
** parse_arg.
*/

int		parse_until_arg(t_data *d)
{
	int	i;

	i = 0;
	while (*d->f && *d->f != '%')
	{
		++d->f;
		++i;
	}
	if (!(d->tmp = (UC *)ft_ustrnew(i)))
		return (0);
	ft_ustrncpy((UC *)d->tmp, (UC *)(d->f - i), i);
	*d->f ? ++d->f : 0;
	return (1);
}
