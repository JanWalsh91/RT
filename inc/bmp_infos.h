/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_infos.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:54:39 by tgros             #+#    #+#             */
/*   Updated: 2017/05/08 16:36:06 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_INFOS_H
# define BMP_INFOS_H

# include <stdlib.h>

# define WORD uint16_t
# define DWORD uint32_t
# define LONG int32_t
# define BYTE uint8_t

typedef struct	s_bmp_header
{
	WORD	dummy;
	WORD	signature;
	DWORD	file_size;
	WORD	reserv_1;
	WORD	reserv_2;
	DWORD	offset;
	DWORD	chunk;
	DWORD	width;
	DWORD	height;
	WORD	plans;
	WORD	nb_bits;
	DWORD	compression;
	DWORD	x_size;
	DWORD	xpm;
	DWORD	ypm;
	DWORD	clr_nbr;
	DWORD	clr_imprt;
}				t_bmp_header;

typedef struct	s_rgb
{
	BYTE r;
	BYTE g;
	BYTE b;
}				t_rgb;

#endif
