/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:46:09 by tgros             #+#    #+#             */
/*   Updated: 2017/06/03 10:57:49 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "bmp_infos.h"
#include <cuda_runtime.h>

int			check_file(char *file_name, t_bmp_header *header)
{
	int	fd;
	int ret;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (-1);
	if ((ret = read(fd, &header->signature, sizeof(WORD))) != sizeof(WORD) ||
		(ret = read(fd, &header->file_size, sizeof(DWORD)) != sizeof(DWORD)) ||
		(ret = read(fd, &header->reserv_1, sizeof(WORD)) != sizeof(WORD)) ||
		(ret = read(fd, &header->reserv_2, sizeof(WORD)) != sizeof(WORD)) ||
		(ret = read(fd, &header->offset, sizeof(DWORD)) != sizeof(DWORD)) ||
		(ret = read(fd, &header->chunk, sizeof(DWORD)) != sizeof(DWORD)) ||
		(ret = read(fd, &header->width, sizeof(DWORD)) != sizeof(DWORD)) ||
		(ret = read(fd, &header->height, sizeof(DWORD)) != sizeof(DWORD)))
	{
		errno = EIO;
		return (-1);
	}
	if (header->signature != 0x4D42 ||
		header->file_size > 10485760)
	{
		errno = EILSEQ;
		return (-1);
	}
	return (fd);
}

int			check_file2(char *file, t_bmp_header *header, int fd, t_vec3 *dim)
{
	char	ignore[256];
	int		ret;

	if ((int)header->height < 0)
		header->height = -header->height;
	close(fd);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	if (dim)
	{
		dim->x = header->width;
		dim->y = header->height;
	}
	if ((ret = read(fd, &ignore, header->offset)) != (int)header->offset)
		return (-1);
	return (0);
}

int			read_bitmap_color(t_bmp_header *header, t_color *texture_h, int fd)
{
	t_pt2	i;
	char	ignore[256];

	i.x = -1;
	while (++i.x < (int)header->height)
	{
		read(fd, &texture_h[i.x * header->width],
			sizeof(t_color) * header->width);
		read(fd, &ignore, header->width % 4);
		i.y = -1;
		while (++i.y < (int)header->width)
		{
			ignore[0] = texture_h[i.x * header->width + i.y].r;
			texture_h[i.x * header->width + i.y].r =
				texture_h[i.x * header->width + i.y].b;
			texture_h[i.x * header->width + i.y].b = ignore[0];
		}
	}
	return (0);
}

int			alloc_memory(t_color **d_tex, t_color **h_tex, t_bmp_header *head)
{
	int	ret;

	if (cudaMalloc((void **)&(*d_tex), head->width * head->height * 3) != 0)
	{
		ret = 0;
		if (cudaMallocHost((void **)&(*h_tex),
				head->width * head->height * 3) != 0)
			return (-1);
	}
	else
	{
		ret = 1;
		if (!(*h_tex = (t_color *)malloc(head->width * head->height *
											sizeof(t_color))))
			return (-1);
	}
	return (ret);
}

/*
** Opens, allocates memory and reads the content of a bmp file.
** If available GPU memory > size of the file, malloc on the GPU.
** Otherwise, malloc on the pinned memory.
** @param file_name: 	absolute or relative path to the file
** @param dim: 			the dimension of the pixelmap (set in the function)
*/

t_color		*read_bmp(char *file_name, t_vec3 *dim)
{
	int				fd;
	t_color			*texture_d;
	t_color			*texture_h;
	t_bmp_header	header;
	int				on_gpu;

	texture_d = NULL;
	texture_h = NULL;
	if ((fd = check_file(file_name, &header)) == -1)
		return (NULL);
	if (check_file2(file_name, &header, fd, dim) == -1)
		return (NULL);
	on_gpu = alloc_memory(&texture_d, &texture_h, &header);
	if (on_gpu == -1)
		return (NULL);
	read_bitmap_color(&header, texture_h, fd);
	close(fd);
	if (on_gpu)
		cudaMemcpy(texture_d, texture_h, header.width * header.height *
											sizeof(t_color), 1);
	else
		return (texture_h);
	return (texture_d);
}
