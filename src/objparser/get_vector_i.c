/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:28:47 by talemari          #+#    #+#             */
/*   Updated: 2017/05/30 14:05:29 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/inc/libft.h"
#include "../../inc/objparser.h"

char		*get_vector_i(char *l, t_vec3i *v, int start, int s)
{
	char		*err;

	if (((err = get_number(l, &v->x, start)) != NULL) ||
			((err = get_number(l, &v->y, start + s)) != NULL) ||
			((err = get_number(l, &v->z, start + s * 2)) != NULL))
		return (err);
	return (NULL);
}
