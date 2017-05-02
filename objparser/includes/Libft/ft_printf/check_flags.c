/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:44:59 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/15 19:09:36 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_prefix(t_arg *arg, UC **prefix);
static int	get_padding(t_arg *arg, UC **padding, size_t prefix_len);
static int	add_commas(t_arg *arg);

/*
** Checks for flags given to this argument, and applies the changes to
** the arg->result string.
*/

int			check_flags(t_arg *arg)
{
	UC	*prefix;
	UC	*padding;

	if (arg->width && arg->type == 'n')
		return (0);
	arg->flags.single_quote ? add_commas(arg) : 0;
	get_prefix(arg, &prefix);
	get_padding(arg, &padding, prefix ? ft_ustrlen(prefix) : 0);
	if (arg->flags.minus)
		arg->result = ft_ustrsjoinfree(3, prefix, arg->result, padding);
	else if (arg->flags.zero)
		arg->result = ft_ustrsjoinfree(3, prefix, padding, arg->result);
	else if (!arg->flags.zero)
		arg->result = ft_ustrsjoinfree(3, padding, prefix, arg->result);
	return (1);
}

/*
** get_prefix combines alternate form (flag #) handling for unsigned
** conversions and sign handling (flags -, +, and 'space') for signed
** conversions.
** Modifies the prefix string.
*/

static int	get_prefix(t_arg *arg, UC **prefix)
{
	*prefix = NULL;
	if (arg->type && arg->flags.hashtag)
	{
		(arg->type == 'o' && ft_strcmp((char *)arg->result, "0")) ?
			*prefix = ft_ustrdup((UC *)"0") : 0;
		(arg->type == 'x') ? *prefix = ft_ustrdup((UC *)"0x") : 0;
		(arg->type == 'X') ? *prefix = ft_ustrdup((UC *)"0X") : 0;
		(arg->type == 'b') ? *prefix = ft_ustrdup((UC *)"0b") : 0;
	}
	if (arg->type && ft_strchr("adefgi", arg->type))
	{
		arg->neg_int ? *prefix = ft_ustrdup((UC *)"-") : 0;
		arg->flags.plus && !arg->neg_int ? *prefix = ft_ustrdup((UC *)"+") : 0;
		arg->flags.space && !arg->neg_int ? *prefix = ft_ustrdup((UC *)" ") : 0;
	}
	return (1);
}

/*
** Modifies the padding string with the padding if neccessary, handling
** field width and flag 0.
*/

static int	get_padding(t_arg *arg, UC **padding, size_t prefix_len)
{
	int	length;

	arg->result_len = (arg->result) ? ft_ustrlen(arg->result) : 0;
	*padding = NULL;
	length = arg->width - arg->result_len - prefix_len;
	if (length > 0)
	{
		*padding = ft_ustrnew(length);
		*padding = ft_memset(*padding, arg->flags.zero ? '0' : ' ', length);
	}
	return (1);
}

/*
** Groups and separates decimal conversion (d, i, and u) result digits by
** thousands.
*/

static int	add_commas(t_arg *arg)
{
	int	i;
	int	y;
	int	comma_count;
	UC	*result;

	if (!ft_strchr("diu", arg->type))
		return (0);
	i = 0;
	while (arg->result && arg->result[i])
		++i;
	if (!(comma_count = (i - 1) / 3))
		return (1);
	if (!(result = ft_ustrnew(i + comma_count)))
		return (0);
	y = 0;
	while (--i + comma_count >= 0)
	{
		if (y == 3 && !(y = 0))
			result[i + comma_count--] = ',';
		result[i + comma_count] = arg->result[i];
		++y;
	}
	free(arg->result);
	arg->result = result;
	return (1);
}
