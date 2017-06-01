/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:37:26 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/22 11:33:11 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocated memory for and returns a new link with the content and
** content size passed as parameters.
*/

#include "libft.h"
#include <cuda.h>
#include <cuda_runtime.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
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
		ft_memcpy(new_content, content, content_size);
	if (cudaMallocHost((void **)&list, sizeof(t_list)) != 0)
		return (NULL);
	list->content = new_content;
	list->content_size = content_size;
	list->next = NULL;
	return (list);
}
