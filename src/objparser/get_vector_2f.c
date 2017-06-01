/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector_2f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 11:48:01 by talemari          #+#    #+#             */
/*   Updated: 2017/05/30 11:48:33 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/inc/libft.h"
#include "../../inc/objparser.h"

char		*get_vector_2f(char *l, t_vec2f *v)
{
	char		*err;

	if (((err = get_float(l, &v->x, 0)) != NULL) ||
			((err = get_float(l, &v->y, 1)) != NULL))
		return (err);
	return (NULL);
}
