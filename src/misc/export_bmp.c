/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 11:08:45 by tgros             #+#    #+#             */
/*   Updated: 2017/05/08 16:39:43 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "gui.h"
#include "bmp_infos.h"

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

void		*export_image(void *data)
{
	int		fd;
	int		i;
	int		r;
	int		g;
	int		b;
	t_th_export *th_export = (t_th_export*)data;

	if (!(fd = open(th_export->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600)))
		return (NULL);

	write_header(fd, th_export->g->r->scene->res.x, th_export->g->r->scene->res.y);
	i = -1;
	while (++i < th_export->g->r->scene->res.x * th_export->g->r->scene->res.y)
	{
		r = th_export->g->r->d_pixel_map[i].r;
		g = th_export->g->r->d_pixel_map[i].g;
		b = th_export->g->r->d_pixel_map[i].b;
		write(fd, &b, sizeof(BYTE));
		write(fd, &g, sizeof(BYTE));
		write(fd, &r, sizeof(BYTE));
		if (i % th_export->g->r->scene->res.x == 0)
		{
			th_export->progress = (double)i / (th_export->g->r->scene->res.x * th_export->g->r->scene->res.y) + 0.1;
		}	
	}
	close(fd);
	return (NULL);
}