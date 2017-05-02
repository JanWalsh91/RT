/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:52:07 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/21 15:50:00 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** Creates and returns an array of int starting at start and ending with end.
*/

int	*ft_range(int start, int end)
{
	int		*array;
	int		length;
	int		i;

	length = end - start;
	if (length > 0)
	{
		if (!(array = (int *)malloc(sizeof(char) * (length + 1))))
			return (0);
		i = 0;
		while (i <= length)
			array[i++] = start++;
	}
	else
	{
		length = start - end;
		if (!(array = (int *)malloc(sizeof(char) * (length + 1))))
			return (0);
		i = 0;
		while (i <= length)
			array[i++] = start--;
	}
	return (array);
}
