/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:22:02 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Splits and trims lines from the input file.
** Puts the first string in lowercase.
*/

char	**split_trim(char *s, char c)
{
	char	**result;
	char	*tmp;
	int		i;

	i = 0;
	result = NULL;
	result = ft_strsplit(s, c);
	while (result && result[i])
	{
		tmp = ft_strtrim(result[i]);
		if (result[i])
			free(result[i]);
		result[i] = tmp;
		++i;
	}
	if (result)
		ft_strtolower(result[0]);
	return (result);
}
