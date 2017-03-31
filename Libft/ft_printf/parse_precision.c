/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 13:14:24 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 18:03:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Precision is by default set to -1.
** If a period is found, the precision is set to the following number.
** If there is no number, the precision is set to 0.
** Handles wildcards.
** Returns 0 if precision is followed by a '\0'.
*/

int	parse_precision(t_data *d, t_arg *arg)
{
	if (!(*d->f == '.'))
		return (1);
	++d->f;
	if (!*d->f)
		return (0);
	if (*d->f == '*')
	{
		if ((arg->precision = va_arg(d->ap, int)) < 0)
			arg->precision = (arg->precision == -2147483648) ? 2147483647 : -1;
		++d->f;
	}
	else
	{
		arg->precision = ft_isdigit(*d->f) ? ft_atoi(d->f) : 0;
		while (*d->f && ft_isdigit(*d->f))
			++d->f;
	}
	return (1);
}
