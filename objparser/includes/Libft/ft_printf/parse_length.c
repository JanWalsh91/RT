/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 13:14:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 17:59:40 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Parses for a length modifier in the format string.
** If a length modifier is found, sets it in arg.
** Returns 0 if the length modifier is followed by a '\0'.
*/

int	parse_length(t_data *d, t_arg *arg)
{
	if (!*d->f)
		return (0);
	(*d->f == 'h') ? arg->length = 2 : 0;
	(*d->f == 'l') ? arg->length = 3 : 0;
	(*d->f == 'j') ? arg->length = 5 : 0;
	(*d->f == 'z') ? arg->length = 6 : 0;
	if (!arg->length)
		return (1);
	++d->f;
	if (!*d->f)
		return (0);
	(*(d->f - 1) == 'h') && (*d->f == 'h') ? arg->length = 1 : 0;
	(*(d->f - 1) == 'l') && (*d->f == 'l') ? arg->length = 4 : 0;
	if (arg->length == 1 || arg->length == 4)
		++d->f;
	if (!*d->f)
		return (0);
	return (1);
}
