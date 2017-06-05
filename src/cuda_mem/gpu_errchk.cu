/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_errchk.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 15:30:53 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 10:27:33 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cuda_runtime.h>
#include <stdlib.h>
#include "rt.cuh"

/*
** Checks a cuda function return value for errors and exits with an error 
** message.
*/

__host__
void gpu_errchk(int code)
{
	int l;
	const char *s;

	s = cudaGetErrorString((cudaError_t)code);
	l = strlen(s);
	if (code != cudaSuccess)
	{
		write(2, "GPUassert: ", 11);
		write(2, s, l);
		write(2, "\n", 1);
		exit(code);
	}
}
