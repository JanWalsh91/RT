/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 18:52:52 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/16 13:11:13 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Gets the string for s conversions.
** Null pointers add "(null)" to the result string.
*/

int		get_string(t_data *d, t_arg *arg)
{
	wchar_t	*tmp;

	if (arg->length == none)
	{
		if (!(arg->result = (UC *)ft_ustrdup((UC *)va_arg(d->ap, char *))))
		{
			free(arg->result);
			arg->result = ft_ustrdup((UC *)"(null)");
		}
	}
	else if (arg->length == l)
	{
		tmp = va_arg(d->ap, wchar_t *);
		if (!tmp)
			arg->result = (UC *)ft_strdup("(null)");
		while (tmp && *tmp)
			arg->result = ft_ustrjoinfree(arg->result,
					ft_wctostr(*(tmp++)), 'b');
	}
	return ((arg->length == none || arg->length == l) ? 1 : 0);
}
