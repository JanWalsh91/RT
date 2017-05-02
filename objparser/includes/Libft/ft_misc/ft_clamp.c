/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:37:27 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/22 14:14:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Changes the value of int i to max if i > max, or to min if i < min.
*/

#include "libft.h"

int	ft_clamp(int i, int min, int max)
{
	if (i < min)
		i = min;
	if (i > max)
		i = max;
	return (i);
}
