/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_byte_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 16:00:08 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 18:04:55 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Sets the variable passed as parameter to byte_count.
*/

int	set_byte_count(t_data *d, t_arg *arg)
{
	d->byte_count = (d->tmp ? ft_ustrlen(d->tmp) : 0) +
		(d->s ? ft_strlen((char *)d->s) : 0);
	if (arg->length == hh)
		*va_arg(d->ap, signed char *) = (signed char)d->byte_count;
	if (arg->length == h)
		*va_arg(d->ap, short *) = (short)d->byte_count;
	if (arg->length == none)
		*va_arg(d->ap, int *) = (int)d->byte_count;
	if (arg->length == l)
		*va_arg(d->ap, long *) = (long)d->byte_count;
	if (arg->length == ll)
		*va_arg(d->ap, long long *) = (long long)d->byte_count;
	if (arg->length == j)
		*va_arg(d->ap, intmax_t *) = (intmax_t)d->byte_count;
	return (1);
}
