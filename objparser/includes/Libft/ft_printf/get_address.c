/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_address.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 19:07:14 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 17:56:20 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Gets the address for p conversions.
** p conversion results are always displayed in alternate form (# flag).
*/

int	get_address(t_data *d, t_arg *arg)
{
	arg->flags.hashtag = 1;
	arg->length = l;
	if (!get_unsigned_int(d, arg))
		return (0);
	return (1);
}
