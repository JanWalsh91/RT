/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 16:04:26 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/16 12:04:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Gets the int/wint_t argument converted to unsigned char/wchar_t for c and C
** conversions.
*/

int		get_char(t_data *d, t_arg *arg)
{
	if (arg->length == l)
	{
		if (!(arg->result = ft_wctostr((wchar_t)va_arg(d->ap, wint_t))))
			return (0);
	}
	else if (arg->length == none)
	{
		if (!(arg->result = (UC *)malloc(2)))
			return (0);
		arg->result[0] = (UC)va_arg(d->ap, int);
		arg->result[1] = '\0';
	}
	else
		return (0);
	if (!arg->result[0])
	{
		++d->null_char;
		++arg->null_char;
		arg->result[0] = 255;
	}
	return (1);
}
