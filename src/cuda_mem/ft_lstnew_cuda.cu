/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_cuda.cu                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:37:26 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 10:59:07 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocated memory for and returns a new link with the content and
** content size passed as parameters. Cuda version
*/

#include "../../inc/rt.cuh"
#include <cuda.h>
#include <cuda_runtime.h>

t_list		*ft_lstnew_cuda(void const *content, size_t content_size)
{
	t_list	*list;
	void	*new_content;

	if (cudaMallocHost((void **)&new_content, content_size) != 0)
		return (NULL);
	if (!content)
	{
		new_content = NULL;
		content_size = 0;
	}
	else
		memcpy(new_content, content, content_size);
	if (cudaMallocHost((void **)&list, sizeof(t_list)) != 0)
		return (NULL);
	list->content = new_content;
	list->content_size = content_size;
	list->next = NULL;
	return (list);
}
