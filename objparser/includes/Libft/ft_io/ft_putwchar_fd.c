/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:23:50 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:41:14 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Writes the wide character c to the file descriptor fd.
** Returns 0 if the character is invalid.
*/

#include "libft.h"

static int write_1_byte(wchar_t c, int fd);
static int write_2_bytes(wchar_t c, int fd);
static int write_3_bytes(wchar_t c, int fd);
static int write_4_bytes(wchar_t c, int fd);

int			ft_putwchar_fd(wchar_t c, int fd)
{
	if (0 <= c && c <= 0x7F)
		return (write_1_byte(c, fd));
	else if (0x7F < c && c <= 0x7FF)
		return (write_2_bytes(c, fd));
	else if ((0x7FF <= c && c <= 0xD7FF) || (0xE000 <= c && c <= 0xFFFF))
		return (write_3_bytes(c, fd));
	else if (0xFFFF < c && c <= 0x10FFFF)
		return (write_4_bytes(c, fd));
	return (0);
}

static int	write_1_byte(wchar_t c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

static int	write_2_bytes(wchar_t c, int fd)
{
	unsigned char s[2];

	s[0] = ((c >> 6) & 0x1F) + 0x80;
	s[1] = (c & 0xBF);
	write(fd, &c, 2);
	return (1);
}

static int	write_3_bytes(wchar_t c, int fd)
{
	unsigned char s[3];

	s[0] = ((c >> 12) & 0xF) + 0xE0;
	s[1] = ((c >> 6) & 0x3F) + 0x80;
	s[2] = (c & 0x3F) + 0x80;
	if (0x800 <= c && c <= 0xFFF)
		if (!(0xA0 <= s[1] && s[1] <= 0xBF))
			return (0);
	write(fd, &c, 3);
	return (1);
}

static int	write_4_bytes(wchar_t c, int fd)
{
	unsigned char s[4];

	s[0] = ((c >> 18) & 0x7) + 0xF0;
	s[1] = ((c >> 12) & 0x3F) + 0x80;
	s[2] = ((c >> 6) & 0x3F) + 0x80;
	s[3] = (c & 0x3F) + 0x80;
	if (0x10000 <= c && c <= 0x3FFFF)
		if (!(0x90 <= s[1] && s[1] <= 0xBF))
			return (0);
	if (0x100000 <= c && c <= 0x10FFFF)
		if (!(0x80 <= s[1] && s[1] <= 0x8F))
			return (0);
	write(fd, &c, 4);
	return (1);
}
