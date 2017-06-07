/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:16:54 by talemari          #+#    #+#             */
/*   Updated: 2017/05/10 16:12:29 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/inc/libft.h"

/*
** Get the n float from the string str
*/

static char		*check_number(char c, char c2)
{
	if ((c == '.' || c == '-') && ft_isdigit(c2) != 1)
		return ("Corrupted data");
	return (NULL);
}

char			*get_float(char *str, float *f, int n)
{
	int		i;
	char	*err;

	i = 0;
	while (str[i])
	{
		if ((ft_isdigit(str[i]) == 1 || str[i] == '.' || str[i] == '-')
				&& n == 0)
		{
			if ((err = check_number(str[i], str[i + 1])) != NULL)
				return (err);
			*f = ft_atof(&str[i]);
			return (NULL);
		}
		else if ((ft_isdigit(str[i]) == 1 || str[i] == '.' || str[i] == '-')
				&& n > 0)
		{
			while ((ft_isdigit(str[i]) == 1 || str[i] == '.' || str[i] == '-')
					&& str[i])
				i++;
			n--;
		}
		i++;
	}
	return ("NUMBER NOT FOUND");
}
