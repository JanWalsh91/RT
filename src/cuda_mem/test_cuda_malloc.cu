/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cuda_malloc.cu                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:56:48 by tgros             #+#    #+#             */
/*   Updated: 2017/06/07 14:57:03 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include <stdlib.h>

/*
** Tries to call cudaMalloc until success. Displays popup after 5 tries.
*/

void	malloc_error(char *cuda, const char *s)
{
	write(2, "\e[1;93mcudaMalloc fail after ", 17);
	write(2, cuda, 1);
	write(2, " attempts\n", 9);
	write(2, "GPUassert : ", 12);
	write(2, s, strlen(s));
	write(2, "\e[0m\n", 5);
}

bool	test_cuda_malloc(void **to_malloc, size_t size)
{
	int i;
	const char *s;
	char cuda[1];
	int code;
	int test_cuda;

	i = 0;
	test_cuda = CUDA_TEST;
	if (test_cuda < 1 && test_cuda > 9)
		test_cuda = 5;
	while (i < test_cuda)
	{
		if ((code = cudaMalloc(to_malloc, size)) == 0)
			return (true);
		i++;
	}
	s = cudaGetErrorString((cudaError_t)code);
	cuda[0] = test_cuda + 48;
	if (code != cudaSuccess)
		malloc_error(cuda, s);
	return (false);
}
