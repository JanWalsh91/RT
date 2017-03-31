/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:09:26 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 14:57:04 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts wide character to a character string (to be used by write (2)).
** Returns 0 if the character is invalid.
*/

#include "libft.h"

static unsigned char	*get_1_byte(wchar_t c);
static unsigned char	*get_2_bytes(wchar_t c);
static unsigned char	*get_3_bytes(wchar_t c);
static unsigned char	*get_4_bytes(wchar_t c);

unsigned char			*ft_wctostr(wchar_t c)
{
	if (0 <= c && c <= 0x7F)
		return (get_1_byte(c));
	else if (0x7F < c && c <= 0x7FF)
		return (get_2_bytes(c));
	else if ((0x7FF < c && c <= 0xD7FF) || (0xE000 <= c && c <= 0xFFFF))
		return (get_3_bytes(c));
	else if (0xFFFF < c && c <= 0x10FFFF)
		return (get_4_bytes(c));
	return (0);
}

static unsigned char	*get_1_byte(wchar_t c)
{
	unsigned char	*s;

	if (!(s = ft_ustrnew(1)))
		return (NULL);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

static unsigned char	*get_2_bytes(wchar_t c)
{
	unsigned char	*s;

	if (!(s = ft_ustrnew(2)))
		return (NULL);
	s[0] = ((c >> 6) & 0x1F) + 0xC0;
	s[1] = (c & 0x3F) + 0x80;
	s[2] = '\0';
	return (s);
}

static unsigned char	*get_3_bytes(wchar_t c)
{
	unsigned char	*s;

	if (!(s = ft_ustrnew(3)))
		return (NULL);
	s[0] = ((c >> 12) & 0xF) + 0xE0;
	s[1] = ((c >> 6) & 0x3F) + 0x80;
	s[2] = (c & 0x3F) + 0x80;
	s[3] = '\0';
	if (0x800 <= c && c <= 0xFFF)
		if (!(0xA0 <= s[1] && s[1] <= 0xBF))
		{
			free(s);
			return (NULL);
		}
	return (s);
}

static unsigned char	*get_4_bytes(wchar_t c)
{
	unsigned char	*s;

	if (!(s = ft_ustrnew(4)))
		return (NULL);
	s[0] = ((c >> 18) & 0x7) + 0xF0;
	s[1] = ((c >> 12) & 0x3F) + 0x80;
	s[2] = ((c >> 6) & 0x3F) + 0x80;
	s[3] = (c & 0x3F) + 0x80;
	s[4] = '\0';
	if (0x10000 <= c && c <= 0x3FFFF)
		if (!(0x90 <= s[1] && s[1] <= 0xBF))
		{
			free(s);
			return (NULL);
		}
	if (0x100000 <= c && c <= 0x10FFFF)
		if (!(0x80 <= s[1] && s[1] <= 0x8F))
		{
			free(s);
			return (NULL);
		}
	return (s);
}
