/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 14:17:37 by talemari          #+#    #+#             */
/*   Updated: 2017/05/04 14:27:39 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/*
** Get the n number from the string str
*/

int		get_number(char *str, int n)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1 && n == 0)
		{
			return (ft_atoi(&str[i]));
		}
		else if (ft_isdigit(str[i]) == 1 && n > 0)
		{
			while (ft_isdigit(str[i]) == 1 && str[i])
				i++;
			n--;
		}
		i++;
	}
	return (-1);
}
