/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unsigned_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 18:20:44 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/16 13:11:57 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Gets the conversion for ouxXpb types.
*/

static int	get_result(t_arg *arg, uintmax_t tmp);

int			get_unsigned_int(t_data *d, t_arg *arg)
{
	uintmax_t	tmp;

	if (arg->length == hh)
		tmp = (UC)va_arg(d->ap, unsigned int);
	else if (arg->length == h)
		tmp = (unsigned short)va_arg(d->ap, unsigned int);
	else if (arg->length == none)
		tmp = (unsigned int)va_arg(d->ap, unsigned int);
	else if (arg->length == l || arg->length == z)
		tmp = (unsigned long)va_arg(d->ap, unsigned long);
	else if (arg->length == ll)
		tmp = (unsigned long long)va_arg(d->ap, unsigned long long);
	else if (arg->length == j)
		tmp = (uintmax_t)va_arg(d->ap, uintmax_t);
	else
		return (0);
	get_result(arg, tmp);
	return (1);
}

static int	get_result(t_arg *arg, uintmax_t tmp)
{
	int	base;

	arg->type == 'b' ? base = 2 : 0;
	arg->type == 'u' ? base = 10 : 0;
	(ft_strchr("xXp", arg->type)) ? base = 16 : 0;
	arg->type == 'o' ? base = 8 : 0;
	arg->result = (UC *)ft_uitoa_base(tmp, base);
	ft_strchr("xp", arg->type) ? ft_strtolower((char *)arg->result) : 0;
	arg->type != 'p' && arg->result[0] == '0' && arg->type != 'o' ?
		arg->flags.hashtag = 0 : 0;
	arg->type == 'p' ? arg->type = 'x' : 0;
	return (1);
}
