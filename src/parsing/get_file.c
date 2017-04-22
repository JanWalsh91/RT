/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:16:50 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/22 13:37:41 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Takes a file name, reads the file and copies each line to a new link of
** type t_input which is added to the end of the list.
*/

char	*get_file(char *file_name, t_parse_tools *t)
{
	char		*next_line;
	int			fd;
	int			ret;

	printf("get_file\n");
	next_line = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (strerror(errno));
	while ((ret = get_next_line(fd, &next_line) > 0))
	{
		input_pushback(&t->input, get_new_input(next_line, file_name, fd, t));
		if (next_line)
			free(next_line);
		next_line = NULL;
	}
	if (ret != 0)
		return (strerror(errno));
	close(fd);
	return (NULL);
}
