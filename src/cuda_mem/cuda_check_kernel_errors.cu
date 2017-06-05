/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_check_kernel_errors.cu                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:13:47 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 10:34:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "../inc/cuda_call.h"

void	cuda_check_kernel_errors(void)
{
	cudaError_t	errSync;
	cudaError_t	errAsync;

	errSync = cudaGetLastError();
	errAsync = cudaDeviceSynchronize();
	if (errSync != cudaSuccess)
		printf("1 Sync kernel error: %s\n", cudaGetErrorString(errSync));
	if (errAsync != cudaSuccess)
		printf("1 Async kernel error: %s\n", cudaGetErrorString(errAsync));
	if (errSync != cudaSuccess || errAsync != cudaSuccess)
		exit(-1);
}
