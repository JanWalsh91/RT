/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 13:02:01 by tgros             #+#    #+#             */
/*   Updated: 2017/05/05 13:02:06 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

char	*get_file_name(char *absolute_path)
{
	char	*ptr;
	char	*file_name;

	ptr = absolute_path;
	while (*ptr)
	{
		if (*ptr == '/')
			file_name = ptr + 1;
		ptr++;
	}
	return (file_name);
}