/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 15:39:05 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/07 14:11:19 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parse_user_input(t_data *d, char **input);
static int	get_code_values(char *c);

/*
** Gets the ANSI code for { types.
** All argument options are ignored but for the contents of the curly brackets.
**
** Format options handled: eoc/"", bold/"b", dim/"d", italics/"i",
** underline/"i", red, green, blue, magenta, cyan, yellow, pink, orange and
** black. Color codes can be modified in ft_printf.h.
*/

int			get_format(t_data *d, t_arg *arg)
{
	char	*code;

	init_arg(arg);
	parse_user_input(d, &code);
	get_code_values(code);
	arg->result = (UC *)ft_strjoinfree((char *)arg->result, code, 'o');
	return (1);
}

/*
** Parses the user input for the format type.
*/

static int	parse_user_input(t_data *d, char **input)
{
	int		i;

	i = 0;
	while (d->f[i] && d->f[i] != '}')
		++i;
	if (!(*input = ft_strnew(i)))
		return (0);
	*input = ft_strncpy(*input, d->f, i);
	while (*d->f && *d->f != '}')
		++d->f;
	++d->f;
	i = -1;
	while (input && input[++i])
		((*input)[i] == ' ') ? (*input)[i] = ',' : 0;
	i = -1;
	ft_strtolower(*input);
	return (1);
}

/*
** Reads user input and replaces string with ANSI codes.
*/

static int	get_code_values(char *c)
{
	int		i;

	i = -1;
	!ft_strcmp(c, "eoc") || !ft_strcmp(c, "")
		? c = ft_strdupfree(c, "\e[0m") : 0;
	!ft_strcmp(c, "bold") || !ft_strcmp(c, "b") ?
		c = ft_strdupfree(c, "\e[1m") : 0;
	!ft_strcmp(c, "dim") || !ft_strcmp(c, "d") ?
		c = ft_strdupfree(c, "\e[2m") : 0;
	!ft_strcmp(c, "italics") || !ft_strcmp(c, "i") ?
		c = ft_strdupfree(c, "\e[3m") : 0;
	!ft_strcmp(c, "underline") || !ft_strcmp(c, "u")
		? c = ft_strdupfree(c, "\e[4m") : 0;
	!ft_strcmp(c, "red") ? c = ft_strdupfree(c, ANSI_RED) : 0;
	!ft_strcmp(c, "green") ? c = ft_strdupfree(c, ANSI_GREEN) : 0;
	!ft_strcmp(c, "blue") ? c = ft_strdupfree(c, ANSI_BLUE) : 0;
	!ft_strcmp(c, "magenta") ? c = ft_strdupfree(c, ANSI_MAGENTA) : 0;
	!ft_strcmp(c, "cyan") ? c = ft_strdupfree(c, ANSI_CYAN) : 0;
	!ft_strcmp(c, "yellow") ? c = ft_strdupfree(c, ANSI_YELLOW) : 0;
	!ft_strcmp(c, "pink") ? c = ft_strdupfree(c, ANSI_PINK) : 0;
	!ft_strcmp(c, "orange") ? c = ft_strdupfree(c, ANSI_ORANGE) : 0;
	!ft_strcmp(c, "black") ? c = ft_strdupfree(c, ANSI_BLACK) : 0;
	c && c[0] != '\e' ? c = ft_strdupfree(c, "") : 0;
	return (1);
}
