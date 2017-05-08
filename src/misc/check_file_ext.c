/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:15:14 by tgros             #+#    #+#             */
/*   Updated: 2017/05/08 17:24:16 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

int		check_file_ext(char *file_name, char *ext)
{
	char	*ret;

	ft_strtoupper(file_name);
	if (!(ret = ft_strrchr(file_name, '.')))
		return (0);
	if (ft_strcmp(ret + 1, ext) != 0)
		return (0);
	return (1);
}