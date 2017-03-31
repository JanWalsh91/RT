/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:25:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/02 11:46:32 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Adds an elements to the end of a list.
*/

void	ft_lstadd_end(t_list **alist, t_list *n)
{
	t_list	*l_ptr;

	l_ptr = *alist;
	if (n)
	{
		if (!*alist)
			*alist = n;
		else
		{
			while (l_ptr->next)
				l_ptr = l_ptr->next;
			l_ptr->next = n;
		}
	}
}
