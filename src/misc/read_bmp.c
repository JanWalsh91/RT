/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:46:09 by tgros             #+#    #+#             */
/*   Updated: 2017/05/15 10:16:40 by tgros            ###   ########.fr       */
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
	int				ret;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (NULL);

	// verify each read, if not size of word or DWORD
	// check the signature. Need to be the default value for a bmp file. If not, STOP.
	// check width and height: if 1231354564647684364136846741684768741647 then that file sucks
	if ((ret = read(fd, &header.signature, sizeof(WORD))) != sizeof(WORD) ||
		(ret = read(fd, &header.file_size, sizeof(DWORD)) != sizeof(DWORD)) ||
		(ret = read(fd, &header.reserv_1, sizeof(WORD))!= sizeof(WORD)) ||
		(ret = read(fd, &header.reserv_2, sizeof(WORD))!= sizeof(WORD)) ||
		(ret = read(fd, &header.offset, sizeof(DWORD))!= sizeof(DWORD)) ||
		(ret = read(fd, &header.chunk, sizeof(DWORD))!= sizeof(DWORD)) ||
		(ret = read(fd, &header.width, sizeof(DWORD))!= sizeof(DWORD)) ||
		(ret = read(fd, &header.height, sizeof(DWORD))!= sizeof(DWORD)))
	{
		errno = EIO;
		return (NULL);
	}
	if (header.signature != 0x4D42 ||
		header.file_size > 10485760)
	{
		errno = EILSEQ;
		return (NULL);
	}
	if ((int)header.height < 0)
		header.height = -header.height;
	printf("Signature : %x\n", header.signature);
	printf("Decalage : %d\n",  header.offset);
	printf("Largeur : %d\n", header.width);
	printf("Hauteur : %d\n", header.height);
	printf("file_size: %d\n", header.file_size);
	close(fd);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (NULL);
	if (dim)
	{
		dim->x = header.width;
		dim->y = header.height;
	}
	if ((ret = read(fd, &ignore, header.offset)) != header.offset)
		return (NULL);
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
		// if read error, then quit properly
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
	close(fd);
	if (on_gpu)
		cudaMemcpy(texture_d, texture_h, header.width * header.height * sizeof(t_color), 1);
	else
		return (texture_h);
	return (texture_d);
}
