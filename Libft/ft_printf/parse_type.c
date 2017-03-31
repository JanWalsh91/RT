/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 13:15:39 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 18:01:36 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Parses for a conversion type in the format string.
** If a type is found, sets it in arg.
** Updates the lenght modifier for uppercase conversion types.
** Disables the '0' flag if a precision is found with d, i, o, u, x, X and b
** types.
*/

int	parse_type(t_data *d, t_arg *arg)
{
	if (*d->f && ft_strchr("bdiuoxXcspn%{", *d->f))
		arg->type = *d->f;
	else if (*d->f && ft_strchr("BDOUSC", *d->f))
	{
		arg->length == hh ? arg->length = h : 0;
		arg->length == h ? arg->length = none : 0;
		arg->length == none ? arg->length = l : 0;
		arg->length == l ? arg->length = ll : 0;
		arg->length == ll ? arg->length = ll : 0;
		ft_strchr("CS", *d->f) ? arg->length = l : 0;
		arg->type = (ft_tolower(*d->f));
	}
	else
	{
		arg->result = ft_ustrnew(2);
		arg->result[0] = *d->f;
		arg->type = 0;
	}
	if ((ft_strchr("diouxXb", arg->type) && arg->precision >= 0))
		arg->flags.zero = 0;
	++d->f;
	return (1);
}
