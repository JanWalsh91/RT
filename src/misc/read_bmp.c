/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:46:09 by tgros             #+#    #+#             */
/*   Updated: 2017/05/06 15:11:12 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "bmp_infos.h"
#include <cuda_runtime.h>

/*
** Opens, allocates memory and reads the content of a bmp file.
** If available GPU memory > size of the file, malloc on the GPU.
** Otherwise, malloc on the pinned memory.
** @param file_name: 	absolute or relative path to the file
** @param dim: 			the dimension of the pixelmap (set in the function)
*/

t_color		*read_bmp(char *file_name, t_pt2 *dim)
{
	int				fd;
	t_color			*texture_d;
	t_color			*texture_h;
	t_bmp_header	header;
	char			ignore[256];
	t_pt2			i;
	bool			on_gpu;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{	
		printf("%s\n", strerror(errno));
		// No valid file / no texture provided. Test if file != bmp or whatever
	}

	read(fd, &header.signature, sizeof(WORD));
	read(fd, &header.file_size, sizeof(DWORD));
	read(fd, &header.reserv_1, sizeof(WORD));
	read(fd, &header.reserv_2, sizeof(WORD));
	read(fd, &header.offset, sizeof(DWORD));
	read(fd, &header.chunk, sizeof(DWORD));
	read(fd, &header.width, sizeof(DWORD));
	read(fd, &header.height, sizeof(DWORD));
	if ((int)header.height < 0)
		header.height = -header.height;
	printf("Signature : %x\n", header.signature);
	printf("Decalage : %d\n",  header.offset);
	printf("Largeur : %d\n", header.width);
	printf("Hauteur : %d\n", header.height);
	printf("file_size: %d\n", header.file_size);
	close(fd);
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		return (NULL);
		// No valid file / no texture provided. Test if file != bmp or whatever
	}
	dim->x = header.width;
	dim->y = header.height;
	read(fd, &ignore, header.offset);

	if (cudaMalloc((void **)&texture_d, header.width * header.height * 3) != 0)
	{
		on_gpu = false;
		if (cudaMallocHost((void **)&texture_h, header.width * header.height * 3) != 0)
			return (NULL);
	}
	else
	{
		on_gpu = true;
		if (!(texture_h = (t_color *)malloc(header.width * header.height * sizeof(t_color))))
			return (NULL);
	}
	i.x = -1;
	while (++i.x < header.height)
	{
		read(fd, &texture_h[i.x * header.width], sizeof(t_color) * header.width);
		read(fd, &ignore, header.width % 4);
		i.y = -1;
		while (++i.y < header.width)
		{
			ignore[0] = texture_h[i.x * header.width + i.y].r;
			texture_h[i.x * header.width + i.y].r = texture_h[i.x * header.width + i.y].b;
			texture_h[i.x * header.width + i.y].b = ignore[0];
		}
	}
	// printf("========================\n");
	// printf("Je suis sur le %s\n", on_gpu ? " GPU !" : " CPU !");
	// printf("========================\n");
	if (on_gpu)
		cudaMemcpy(texture_d, texture_h, header.width * header.height * sizeof(t_color), 1);
	else
		return (texture_h);
	return (texture_d);
}
