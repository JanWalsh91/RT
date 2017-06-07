/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cuda_malloc.cu                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:56:48 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 11:00:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include <stdlib.h>

/*
** Tries to call cudaMalloc until success. Displays popup after 5 tries.
*/

bool	test_cuda_malloc(void **to_malloc, size_t size)
{
	int i;
	const char *s;
	char cuda[1];
	int code;

	i = 0;

	while (i < CUDA_TEST)
	{
		if ((code = cudaMalloc(to_malloc, size)) == 0)
			return (true);
		i++;
	}
	s = cudaGetErrorString((cudaError_t)code);
	cuda[0] = CUDA_TEST + 48;
	if (code != cudaSuccess)
	{
		write(2, "\e[1;93mcudaMalloc fail after ", 17);
		write(2, cuda, 1);
		write(2, " attempts\n", 9);
		write(2, "GPUassert : ", 12);
		write(2, s, strlen(s));
		write(2, "\e[0m\n", 5);
		exit(code);
	}
	return (false);
}
