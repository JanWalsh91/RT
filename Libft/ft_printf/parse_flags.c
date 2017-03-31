/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 13:12:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 17:57:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Parses for flags in the format string.
** If at least one flags is found, sets them in arg.
*/

int	parse_flags(t_data *d, t_arg *arg)
{
	while (*d->f && ft_strchr("#0-+ 'I", *d->f))
	{
		*d->f == '#' ? arg->flags.hashtag = 1 : 0;
		*d->f == '\'' ? arg->flags.single_quote = 1 : 0;
		*d->f == '0' && arg->flags.minus == 0 ? arg->flags.zero = 1 : 0;
		*d->f == '-' ? arg->flags.minus = 1 : 0;
		*d->f == '-' ? arg->flags.zero = 0 : 0;
		*d->f == '+' ? arg->flags.plus = 1 : 0;
		*d->f == '+' ? arg->flags.space = 0 : 0;
		*d->f == ' ' && arg->flags.plus == 0 ? arg->flags.space = 1 : 0;
		++d->f;
	}
	if (*d->f)
		return (1);
	return (0);
}
