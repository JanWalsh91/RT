/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:57:12 by tgros             #+#    #+#             */
/*   Updated: 2017/05/30 12:16:11 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include <cuda_runtime.h>

void	free_object(t_object *to_delete)
{
	struct cudaPointerAttributes	attributes;
	
	if (to_delete->name)
		free(to_delete->name);
	if (to_delete->texture)
	{
		if (cudaPointerGetAttributes(&attributes, to_delete->texture))
			ft_error_exit("Invalid device");
		printf("Memory type: %d\n", attributes.memoryType);
		if (attributes.memoryType == cudaMemoryTypeHost)
			cudaFreeHost(to_delete->texture);
		else
			cudaFree(to_delete->texture);
		if (to_delete->texture_name)
		{
			printf("Texture name: %s\n", to_delete->texture_name);
			free(to_delete->texture_name);
		}
	}
	if (to_delete->normal_map)
	{
		if (cudaPointerGetAttributes(&attributes, to_delete->normal_map))
			ft_error_exit("Invalid device");
		printf("Memory type: %d\n", attributes.memoryType);
		if (attributes.memoryType == cudaMemoryTypeHost)
			cudaFreeHost(to_delete->normal_map);
		else
			cudaFree(to_delete->normal_map);
		if (to_delete->normal_map_name)
			free(to_delete->normal_map_name);
	}
	
	free(to_delete);
}

void	remove_object(t_object **head, t_object *to_delete)
{
	t_object	*prev;
	t_object	*tmp;

	if (!head || !*head)
		return ;
	prev = *head;
	if (prev == to_delete)
	{
		*head = prev->next;
		free_object(to_delete);
		return ;
	}
	if (prev->next)
	{
		tmp = prev->next;
		while (tmp && tmp != to_delete)
		{
			prev = prev->next;
			tmp = tmp->next;
		}
		if (tmp == to_delete)
		{
			prev->next = tmp->next;
			free_object(to_delete);
		}
	}
	else
	{
		free_object(to_delete);
		*head = NULL;
	}
}
