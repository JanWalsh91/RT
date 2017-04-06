/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 15:31:34 by tgros             #+#    #+#             */
/*   Updated: 2017/04/06 11:23:19 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

#define WORD uint16_t
#define DWORD uint32_t
#define LONG int32_t
#define BYTE uint8_t

typedef struct	s_bmp_header
{
	WORD	dummy;
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

/*
**	Writes the header at the very beginning of the file
**	Needs the structure t_bmp_header, which contains all the file informations
**	@param fd: The file descriptor of the opened file
**	@param width, height: The pixelmap dimensions
*/

void	write_header(int fd, int width, int height)
{
	t_bmp_header	*header;

	header = (t_bmp_header *)malloc(sizeof(t_bmp_header));
	header->signature = 0x4D42;
	header->file_size = width * height * sizeof(t_rgb) * sizeof(header);
	header->reserv_1 = 0;
	header->reserv_2 = 0;
	header->offset = 54;
	header->chunk = 40;
	header->width = width;
	header->height = -height;
	header->plans = 1;
	header->nb_bits = 24;
	header->compression = 0;
	header->x_size = 0;
	header->xpm = 0;
	header->ypm = 0;
	header->clr_nbr = 0;
	header->clr_imprt = 0;
	write(fd, ((BYTE *)header) + 2, 54);
	free(header);
}

/*
**	Exports a pixelmap to a bmp file
**	@param pixelmap: The pixelmap
**	@param width, height: The pixelmap dimensions
**	@param file_name: The name of the bmp file (Needs the .bmp expention,
**	TODO: auto add .bmp)
*/

int		export_image(t_color *pixelmap, int width, int height, char *file_name)
{
	int		fd;
	int		i;
	int		r;
	int		g;
	int		b;

	if (!(fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600)))
		return (0);
	write_header(fd, width, height);
	i = -1;
	while (++i < width * height)
	{
		r = pixelmap[i].x;
		g = pixelmap[i].y;
		b = pixelmap[i].z;
		write(fd, &b, sizeof(BYTE));
		write(fd, &g, sizeof(BYTE));
		write(fd, &r, sizeof(BYTE));
	}
	close(fd);
	return (1);
}
