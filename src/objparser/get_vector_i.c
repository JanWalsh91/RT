/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:26:28 by talemari          #+#    #+#             */
/*   Updated: 2017/05/10 14:15:55 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/inc/libft.h"
#include "../../inc/objparser.h"

char		*get_vector_i(char *l, t_vec3i *v, int s)
{
	char		*err;

	if (((err = get_number(l, &v->x, s)) != NULL) ||
			((err = get_number(l, &v->y, s + 1)) != NULL) ||
			((err = get_number(l, &v->z, s + 2)) != NULL))
		return (err);
	return (NULL);
}
