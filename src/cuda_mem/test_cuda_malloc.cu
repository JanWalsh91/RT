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

/*
** Tries to call cudaMalloc until success. Displays popup after 5 tries.
*/

bool	test_malloc(void *to_malloc, size_t size, t_gtk_tools *g)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (cudaMalloc(&to_malloc, sizeof(size)))
			return (true);
		i++;
	}
	display_error_popup(NULL, g, "cudaMalloc Fail.");
	return (false);
}
