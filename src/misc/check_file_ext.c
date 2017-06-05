/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:15:14 by tgros             #+#    #+#             */
/*   Updated: 2017/06/05 11:54:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

/*
** Make checks the extention ext with the extension in file_name.
*/

int		check_file_ext(char *file_name, char *ext)
{
	char	*ret;

	ft_strtoupper(file_name);
	if (!(ret = ft_strrchr(file_name, '.')) ||
		ft_strcmp(ret + 1, ext) != 0)
	{
		ft_strtolower(file_name);
		return (0);
	}
	ft_strtolower(file_name);
	return (1);
}
