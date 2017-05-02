/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 17:40:14 by talemari          #+#    #+#             */
/*   Updated: 2017/04/28 09:50:29 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/Libft/inc/libft.h"

void		ft_freetab(char **tab)
{
	int		y;

	y = 0;
	while (tab[y])
	{
		ft_strdel(&tab[y]);
		y++;
	}
	free(tab);
}
