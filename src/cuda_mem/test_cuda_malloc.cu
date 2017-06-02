/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_free.cu                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:56:48 by tgros             #+#    #+#             */
/*   Updated: 2017/05/26 21:42:07 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

bool	test_malloc(void *to_malloc, size_t size, t_gtk_tools *g)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (cudaMalloc(&to_malloc, sizeof(size)))
			return(true);
		i++;
	}
	display_error_popup(NULL, g, "cudaMalloc Fail.");
	return(false);
}