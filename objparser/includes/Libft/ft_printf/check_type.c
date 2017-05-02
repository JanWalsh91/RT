/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:59:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 19:08:34 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Based on the type provided, calls on the appropiate function to get the
** conversion.
*/

int	check_type(t_data *d, t_arg *arg)
{
	if (arg->type == 'd' || arg->type == 'i')
		get_int(d, arg);
	else if (arg->type && ft_strchr("bouxX", arg->type))
		get_unsigned_int(d, arg);
	else if (arg->type == 'c' && !get_char(d, arg))
		return (0);
	else if (arg->type == 's' && !get_string(d, arg))
		return (0);
	else if (arg->type == 'p' && !get_address(d, arg))
		return (0);
	else if (arg->type == 'n' && !set_byte_count(d, arg))
		return (0);
	else if (arg->type == '%' && !get_percent(arg))
		return (0);
	else if (arg->type == '{' && !get_format(d, arg))
		return (0);
	return (1);
}
