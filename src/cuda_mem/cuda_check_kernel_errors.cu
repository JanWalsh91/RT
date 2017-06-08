/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_check_kernel_errors.cu                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:13:47 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 14:14:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.cuh"

/*
** An error checking function to be used agfter every kernel launch.
*/

void	cuda_check_kernel_errors(void)
{
	cudaError_t	errSync;
	cudaError_t	errAsync;
	const char	*s;
	int			l;

	errSync = cudaGetLastError();
	errAsync = cudaDeviceSynchronize();
	if (errSync != cudaSuccess)
	{
		write(2, "\e[1;93mSync kernel error: ", 16);
		s =  cudaGetErrorString(errSync);
		l = strlen(s);
		write(2, s, l);
		write(2, "\e[0m\n", 5);
	}
	if (errAsync != cudaSuccess)
	{
		write(2, "\e[1;93mAsync kernel error: ", 17);
		s =  cudaGetErrorString(errAsync);
		l = strlen(s);
		write(2, s, l);
		write(2, "\e[0m\n", 5);
	}
	if (errSync != cudaSuccess || errAsync != cudaSuccess)
		exit(-1);
}
