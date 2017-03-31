/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clampd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:13:21 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/18 15:52:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Changes the value of int i to max if i > max, or to min if i < min.
*/

#include "libft.h"

double	ft_clampd(double i, double min, double max)
{
	i < min ? i = min : 0;
	i > max ? i = max : 0;
	return (i);
}
