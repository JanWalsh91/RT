/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 12:23:52 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/07 14:31:27 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define UI unsigned int
# define UC unsigned char
# define LL long long

# define ANSI_RED "\e[38;5;160m"
# define ANSI_GREEN "\e[32m"
# define ANSI_BLUE "\e[38;5;20m"
# define ANSI_MAGENTA "\e[35m"
# define ANSI_CYAN "\e[38;5;51m"
# define ANSI_YELLOW "\e[38;5;226m"
# define ANSI_PINK "\e[38;5;13m"
# define ANSI_ORANGE "\e[38;5;202m"
# define ANSI_BLACK "\e[38;5;0m"

# include "libft.h"
# include <wchar.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

/*
** usage: %[flags][width][.precision][length]type
*/

typedef enum	e_length
{
	none, hh, h, l, ll, j, z
}				t_length;

typedef struct	s_flags
{
	int				hashtag;
	int				zero;
	int				minus;
	int				plus;
	int				space;
	int				single_quote;
}				t_flags;

typedef struct	s_arg
{
	unsigned char	*result;
	int				result_len;
	t_flags			flags;
	int				width;
	int				precision;
	t_length		length;
	char			type;
	int				neg_int;
	int				null_char;
}				t_arg;

typedef	struct	s_data
{
	char			*f;
	va_list			ap;
	unsigned char	*tmp;
	unsigned char	*s;
	int				byte_count;
	int				null_char;

}				t_data;

int				ft_printf(const char *format, ...);

void			init_data(t_data *d, char *format);
int				parse_until_arg(t_data *d);
int				parse_arg(t_data *d);
int				init_arg(t_arg *arg);

int				parse_flags(t_data *d, t_arg *arg);
int				parse_width(t_data *d, t_arg *arg);
int				parse_precision(t_data *d, t_arg *arg);
int				parse_length(t_data *d, t_arg *arg);
int				parse_type(t_data *d, t_arg *arg);

int				check_type(t_data *d, t_arg *arg);
int				check_precision(t_arg *arg);
int				check_flags(t_arg *arg);

int				get_char(t_data *d, t_arg *arg);
int				get_string(t_data *d, t_arg *arg);
int				get_int(t_data *d, t_arg *arg);
int				get_unsigned_int(t_data *d, t_arg *arg);
int				get_address(t_data *d, t_arg *arg);
int				get_percent(t_arg *arg);
int				get_format(t_data *d, t_arg *arg);
int				set_byte_count(t_data *data, t_arg *arg);

#endif
