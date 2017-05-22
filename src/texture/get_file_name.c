/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 13:02:01 by tgros             #+#    #+#             */
/*   Updated: 2017/05/21 11:43:03 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

char	*get_file_name(char *absolute_path)
{
	char	*ptr;
	char	*file_name;

	ptr = absolute_path;
	file_name = NULL;
	while (*ptr)
	{
		if (*ptr == '/')
			file_name = ptr + 1;
		ptr++;
	}
	if (!file_name)
		file_name = absolute_path;
	return (file_name);
}
