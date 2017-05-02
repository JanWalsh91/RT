/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 12:21:50 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/20 17:43:36 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Parses the argument, and updates the final result with the tmp string and
** the conversion of the argyment.
*/

static int	merge(t_data *d, t_arg *arg);

int			parse_arg(t_data *d)
{
	t_arg	arg;

	arg.result = NULL;
	if (*d->f == 0)
		return (merge(d, &arg));
	else if (!init_arg(&arg) ||
		!parse_flags(d, &arg) ||
		!parse_width(d, &arg) ||
		!parse_precision(d, &arg) ||
		!parse_length(d, &arg) ||
		!parse_type(d, &arg) ||
		!check_type(d, &arg) ||
		!check_precision(&arg) ||
		!check_flags(&arg))
		return (0);
	return (merge(d, &arg));
}

static int	merge(t_data *d, t_arg *arg)
{
	d->s = ft_ustrsjoinfree(3, d->s, d->tmp, arg->result);
	return (1);
}
