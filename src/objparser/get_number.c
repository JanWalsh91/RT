/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 14:17:37 by talemari          #+#    #+#             */
/*   Updated: 2017/05/10 14:17:46 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../Libft/inc/libft.h"

/*
** Get the n number from the string str
*/

char		*get_number(char *str, int *res, int n)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) && n == 0)
		{
			*res = ft_atoi(&str[i]);
			return (NULL);
		}
		else if (ft_isdigit(str[i]) == 1 && n > 0)
		{
			while (ft_isdigit(str[i]) == 1 && str[i])
				i++;
			n--;
		}
		i++;
	}
	return ("NUMBER NOT FOUND");
}
