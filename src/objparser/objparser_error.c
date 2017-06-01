/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 11:38:37 by talemari          #+#    #+#             */
/*   Updated: 2017/05/31 11:30:13 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

char		*objparser_error(char *err, int l)
{
	char	*res;
	char	*line;
	char	*errline;
	char	*ponct;

	line = ft_itoa(l);
	errline = "!!Error in Objectfile, line ";
	ponct = " : ";
	res = (char *)malloc(sizeof(char) * (ft_strlen(errline) + ft_strlen(line) +
				ft_strlen(ponct) + ft_strlen(err) + 1));
	res = ft_strcpy(res, errline);
	res = ft_strcat(res, line);
	res = ft_strcat(res, ponct);
	res = ft_strcat(res, err);
	return (res);
}
