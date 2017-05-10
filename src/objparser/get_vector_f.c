/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:48:56 by talemari          #+#    #+#             */
/*   Updated: 2017/05/10 14:17:30 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/inc/libft.h"
#include "../../inc/objparser.h"

char		*get_vector_f(char *l, t_vec3f *v)
{
	char		*err;

	if (((err = get_float(l, &v->x, 0)) != NULL) ||
			((err = get_float(l, &v->y, 1)) != NULL) ||
			((err = get_float(l, &v->z, 2)) != NULL))
		return (err);
	return (NULL);
}
