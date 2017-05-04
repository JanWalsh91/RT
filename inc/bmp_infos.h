/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_infos.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:54:39 by tgros             #+#    #+#             */
/*   Updated: 2017/04/29 16:03:44 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_INFOS_H
# define BMP_INFOS_H

#include <stdlib.h>

# define WORD uint16_t
# define DWORD uint32_t
# define LONG int32_t
# define BYTE uint8_t

typedef struct	s_bmp_header
{
	// WORD	dummy;
	WORD	signature; // const = 0x4D42
	DWORD	file_size;
	WORD	reserv_1; // = 0
	WORD	reserv_2; // = 0
	DWORD	offset; // Size before the pixel infos
	DWORD	chunk; // size of image description (=40)
	DWORD	width;
	DWORD	height; // If positive, the picture will be upside-down. Set it to -height
	WORD	plans;
	WORD	nb_bits; // because 8 bit is for your grand ma
	DWORD	compression; // No compression (=0)
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